#include "network/UdpTrackReceiver.h"
#include "core/TrackManager.h"
#include "utils/Logger.h"
#include <QNetworkDatagram>
#include <QtMath>
#include <cstring>

namespace CounterUAS {

UdpTrackReceiver::UdpTrackReceiver(TrackManager* trackManager, QObject* parent)
    : QObject(parent)
    , m_trackManager(trackManager)
    , m_socket(new QUdpSocket(this))
{
    connect(m_socket, &QUdpSocket::readyRead, this, &UdpTrackReceiver::onReadyRead);
}

UdpTrackReceiver::~UdpTrackReceiver() {
    stop();
}

bool UdpTrackReceiver::start(quint16 port) {
    m_port = port;

    if (m_socket->state() == QAbstractSocket::BoundState) {
        m_socket->close();
    }

    if (!m_socket->bind(QHostAddress::AnyIPv4, m_port,
                        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        QString err = QString("Failed to bind UDP socket on port %1: %2")
                          .arg(m_port).arg(m_socket->errorString());
        Logger::instance().error("UdpTrackReceiver", err);
        emit error(err);
        return false;
    }

    Logger::instance().info("UdpTrackReceiver",
        QString("Listening for track updates on UDP port %1 "
                "(single msg=%2 bytes, table header=%3 bytes)")
            .arg(m_port)
            .arg(sizeof(TrackUpdateMessage))
            .arg(sizeof(TrackTableHeader)));
    return true;
}

void UdpTrackReceiver::stop() {
    if (m_socket->state() != QAbstractSocket::UnconnectedState) {
        m_socket->close();
        Logger::instance().info("UdpTrackReceiver", "Stopped listening");
    }
}

bool UdpTrackReceiver::isListening() const {
    return m_socket->state() == QAbstractSocket::BoundState;
}

void UdpTrackReceiver::onReadyRead() {
    while (m_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket->receiveDatagram();
        QByteArray data = datagram.data();

        if (data.size() < static_cast<int>(sizeof(uint32_t))) {
            Logger::instance().warning("UdpTrackReceiver",
                QString("Undersized datagram from %1:%2 (%3 bytes)")
                    .arg(datagram.senderAddress().toString())
                    .arg(datagram.senderPort())
                    .arg(data.size()));
            continue;
        }

        uint32_t messageId = 0;
        std::memcpy(&messageId, data.constData(), sizeof(uint32_t));

        if (messageId == MSG_ID_TRACK_UPDATE) {
            if (data.size() < static_cast<int>(sizeof(TrackUpdateMessage))) {
                Logger::instance().warning("UdpTrackReceiver",
                    QString("Undersized TrackUpdate from %1:%2 (%3 bytes, expected %4)")
                        .arg(datagram.senderAddress().toString())
                        .arg(datagram.senderPort())
                        .arg(data.size())
                        .arg(sizeof(TrackUpdateMessage)));
                continue;
            }

            TrackUpdateMessage msg;
            std::memcpy(&msg, data.constData(), sizeof(TrackUpdateMessage));
            m_messagesReceived++;
            processTrackUpdate(msg);

        } else if (messageId == MSG_ID_TRACK_TABLE) {
            if (data.size() < static_cast<int>(sizeof(TrackTableHeader))) {
                Logger::instance().warning("UdpTrackReceiver",
                    QString("Undersized TrackTable from %1:%2 (%3 bytes, header needs %4)")
                        .arg(datagram.senderAddress().toString())
                        .arg(datagram.senderPort())
                        .arg(data.size())
                        .arg(sizeof(TrackTableHeader)));
                continue;
            }

            m_messagesReceived++;
            processTrackTable(data);

        } else {
            Logger::instance().debug("UdpTrackReceiver",
                QString("Ignoring datagram with messageId 0x%1 from %2:%3")
                    .arg(messageId, 4, 16, QChar('0'))
                    .arg(datagram.senderAddress().toString())
                    .arg(datagram.senderPort()));
        }
    }
}

void UdpTrackReceiver::processTrackTable(const QByteArray& data) {
    TrackTableHeader header;
    std::memcpy(&header, data.constData(), sizeof(TrackTableHeader));

    uint32_t numTracks = header.numTracks;
    int expectedSize = static_cast<int>(sizeof(TrackTableHeader) +
                                        numTracks * sizeof(TrackUpdateMessage));

    if (data.size() < expectedSize) {
        int possibleTracks = (data.size() - static_cast<int>(sizeof(TrackTableHeader)))
                             / static_cast<int>(sizeof(TrackUpdateMessage));
        Logger::instance().warning("UdpTrackReceiver",
            QString("TrackTable claims %1 tracks but datagram too small "
                    "(%2 bytes, expected %3). Processing %4 tracks.")
                .arg(numTracks).arg(data.size()).arg(expectedSize).arg(possibleTracks));
        numTracks = static_cast<uint32_t>(qMax(0, possibleTracks));
    }

    if (numTracks == 0) return;

    const char* trackData = data.constData() + sizeof(TrackTableHeader);

    for (uint32_t i = 0; i < numTracks; ++i) {
        TrackUpdateMessage msg;
        std::memcpy(&msg, trackData + i * sizeof(TrackUpdateMessage),
                    sizeof(TrackUpdateMessage));
        processTrackUpdate(msg);
    }

    if (m_messagesReceived <= 1 || (m_messagesReceived % 100) == 0) {
        Logger::instance().info("UdpTrackReceiver",
            QString("Processed TrackTable #%1: %2 tracks")
                .arg(m_messagesReceived).arg(numTracks));
    }

    emit tracksReceived(numTracks);
}

static TrackClassification mapClassification(UdpTrackClassification cls) {
    switch (cls) {
        case UdpTrackClassification::Friendly: return TrackClassification::Friendly;
        case UdpTrackClassification::Hostile:  return TrackClassification::Hostile;
        case UdpTrackClassification::Pending:  return TrackClassification::Pending;
        case UdpTrackClassification::Neutral:  return TrackClassification::Neutral;
        default:                               return TrackClassification::Unknown;
    }
}

static TrackState mapStatus(TrackStatus status) {
    switch (status) {
        case TrackStatus::Confirmed: return TrackState::Active;
        case TrackStatus::Dropped:   return TrackState::Dropped;
        case TrackStatus::Coasting:  return TrackState::Coasting;
        default:                     return TrackState::Initiated;
    }
}

void UdpTrackReceiver::processTrackUpdate(const TrackUpdateMessage& msg) {
    if (!m_trackManager) return;

    static constexpr double METERS_PER_DEG_LAT = 111000.0;
    static constexpr double BASE_LAT = 34.0522;
    static constexpr double BASE_LON = -118.2437;
    static constexpr double BASE_ALT = 100.0;

    double enu_x = msg.x;
    double enu_y = msg.y;
    double enu_z = msg.z;
    double enu_vx = msg.vx;
    double enu_vy = msg.vy;
    double enu_vz = msg.vz;

    bool cartesianZero = (msg.x == 0.0 && msg.y == 0.0 && msg.z == 0.0);
    bool hasSpherical  = (msg.range != 0.0 || msg.azimuth != 0.0 || msg.elevation != 0.0);

    if (cartesianZero && hasSpherical) {
        // Azimuth and elevation are already in radians per the ICD
        double azRad = msg.azimuth;
        double elRad = msg.elevation;
        enu_x = msg.range * std::cos(elRad) * std::sin(azRad);
        enu_y = msg.range * std::cos(elRad) * std::cos(azRad);
        enu_z = msg.range * std::sin(elRad);

        if (enu_vx == 0.0 && enu_vy == 0.0 && enu_vz == 0.0 && msg.rangeRate != 0.0) {
            enu_vx = msg.rangeRate * std::cos(elRad) * std::sin(azRad);
            enu_vy = msg.rangeRate * std::cos(elRad) * std::cos(azRad);
            enu_vz = msg.rangeRate * std::sin(elRad);
        }
    }

    GeoPosition pos;
    pos.latitude  = BASE_LAT + enu_y / METERS_PER_DEG_LAT;
    pos.longitude = BASE_LON + enu_x / (METERS_PER_DEG_LAT * std::cos(qDegreesToRadians(BASE_LAT)));
    pos.altitude  = BASE_ALT + enu_z;

    VelocityVector vel;
    vel.north = enu_vy;
    vel.east  = enu_vx;
    vel.down  = -enu_vz;

    double quality = qBound(0.0, msg.trackQuality, 1.0);
    TrackClassification cls = mapClassification(msg.classification);

    // For radar-only data the radar's own track number is preserved directly as
    // the track ID (formatted "RAD-NNNN"), removing the need for an
    // external→internal mapping table.
    uint32_t extId = msg.trackId;
    QString trackId = QString("RAD-%1").arg(extId, 4, 10, QChar('0'));

    if (msg.status == TrackStatus::Dropped) {
        m_trackManager->dropTrack(trackId);
        emit trackReceived(extId);
        return;
    }

    Track* t = m_trackManager->track(trackId);
    if (t && t->state() != TrackState::Dropped) {
        // Existing active track: update position, velocity, classification
        m_trackManager->updateTrack(trackId, pos);
        m_trackManager->updateTrackVelocity(trackId, vel);

        if (t->classification() != cls) {
            m_trackManager->setTrackClassification(trackId, cls, quality);
        }
        t->setTrackQuality(quality);

        emit trackReceived(extId);
        return;
    }

    // New (or re-initiated) radar track: create with the radar-assigned ID
    QString createdId = m_trackManager->createTrackWithId(trackId, pos, DetectionSource::Radar);
    if (createdId.isEmpty()) {
        Logger::instance().warning("UdpTrackReceiver",
            QString("Failed to create track for radar ID %1").arg(trackId));
        emit trackReceived(extId);
        return;
    }

    m_trackManager->updateTrackVelocity(createdId, vel);
    m_trackManager->setTrackClassification(createdId, cls, quality);

    Track* newT = m_trackManager->track(createdId);
    if (newT) {
        newT->setTrackQuality(quality);
    }

    if (m_messagesReceived <= 1 || (m_messagesReceived % 100) == 0) {
        QString src = (cartesianZero && hasSpherical) ? "spherical" : "cartesian";
        Logger::instance().info("UdpTrackReceiver",
            QString("New radar track %1 (%2): lat=%3 lon=%4 alt=%5")
                .arg(createdId).arg(src)
                .arg(pos.latitude, 0, 'f', 6).arg(pos.longitude, 0, 'f', 6)
                .arg(pos.altitude, 0, 'f', 1));
    }

    emit trackReceived(extId);
}

} // namespace CounterUAS
