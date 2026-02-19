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
        QString("Listening for track updates on UDP port %1 (msg size = %2 bytes)")
            .arg(m_port).arg(sizeof(TrackUpdateMessage)));
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

        if (data.size() < static_cast<int>(sizeof(TrackUpdateMessage))) {
            Logger::instance().warning("UdpTrackReceiver",
                QString("Undersized datagram from %1:%2 (%3 bytes, expected >= %4)")
                    .arg(datagram.senderAddress().toString())
                    .arg(datagram.senderPort())
                    .arg(data.size())
                    .arg(sizeof(TrackUpdateMessage)));
            continue;
        }

        TrackUpdateMessage msg;
        std::memcpy(&msg, data.constData(), sizeof(TrackUpdateMessage));

        if (msg.messageId != 0x0002) {
            Logger::instance().debug("UdpTrackReceiver",
                QString("Ignoring datagram with messageId 0x%1 (expected 0x0002) from %2:%3")
                    .arg(msg.messageId, 4, 16, QChar('0'))
                    .arg(datagram.senderAddress().toString())
                    .arg(datagram.senderPort()));
            continue;
        }

        m_messagesReceived++;
        processMessage(msg);
    }
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

void UdpTrackReceiver::processMessage(const TrackUpdateMessage& msg) {
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
        double azRad = qDegreesToRadians(msg.azimuth);
        double elRad = qDegreesToRadians(msg.elevation);
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

    if (m_messagesReceived <= 1 || (m_messagesReceived % 100) == 0) {
        QString src = (cartesianZero && hasSpherical) ? "spherical" : "cartesian";
        Logger::instance().info("UdpTrackReceiver",
            QString("Track update #%1 (extId=%2, %3): lat=%4 lon=%5 alt=%6")
                .arg(m_messagesReceived).arg(msg.trackId).arg(src)
                .arg(pos.latitude, 0, 'f', 6).arg(pos.longitude, 0, 'f', 6)
                .arg(pos.altitude, 0, 'f', 1));
    }

    m_trackManager->processRadarDetection(pos, vel, quality,
                                          QDateTime::currentMSecsSinceEpoch());

    // After correlation, find the track nearest to this position so we can
    // apply classification and state from the external tracker.
    QList<Track*> nearby = m_trackManager->tracksInRadius(pos, 50.0);
    if (nearby.isEmpty()) {
        nearby = m_trackManager->tracksInRadius(pos, 200.0);
    }

    if (!nearby.isEmpty()) {
        Track* best = nullptr;
        double bestDist = 1e9;
        for (Track* t : nearby) {
            double d = t->distanceTo(pos);
            if (d < bestDist) {
                bestDist = d;
                best = t;
            }
        }

        if (best) {
            TrackClassification cls = mapClassification(msg.classification);
            if (best->classification() != cls) {
                m_trackManager->setTrackClassification(best->trackId(), cls, quality);
            }
            best->setTrackQuality(quality);

            if (msg.status == TrackStatus::Dropped) {
                m_trackManager->dropTrack(best->trackId());
            }
        }
    }

    emit trackReceived(msg.trackId);
}

} // namespace CounterUAS
