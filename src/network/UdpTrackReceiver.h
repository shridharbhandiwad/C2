#ifndef UDPTRACKRECEIVER_H
#define UDPTRACKRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHash>
#include <cstdint>

namespace CounterUAS {

class TrackManager;

enum class TrackStatus : uint32_t {
    Tentative = 0,
    Confirmed = 1,
    Dropped   = 2,
    Coasting  = 3
};

enum class UdpTrackClassification : uint32_t {
    Unknown   = 0,
    Friendly  = 1,
    Hostile   = 2,
    Pending   = 3,
    Neutral   = 4
};

static constexpr uint32_t MSG_ID_TRACK_UPDATE = 0x0002;
static constexpr uint32_t MSG_ID_TRACK_TABLE  = 0x0003;

#pragma pack(push, 1)
struct TrackUpdateMessage {
    uint32_t            messageId      = MSG_ID_TRACK_UPDATE;
    uint32_t            trackId        = 0;
    uint64_t            timestamp      = 0;     // microseconds since epoch
    TrackStatus         status         = TrackStatus::Tentative;
    UdpTrackClassification classification = UdpTrackClassification::Unknown;
    double              range          = 0.0;   // meters
    double              azimuth        = 0.0;   // radians
    double              elevation      = 0.0;   // radians
    double              rangeRate      = 0.0;   // m/s
    double              x = 0.0, y = 0.0, z = 0.0;   // meters (Cartesian)
    double              vx = 0.0, vy = 0.0, vz = 0.0; // m/s
    double              trackQuality   = 0.0;   // 0.0 - 1.0
    uint32_t            hitCount       = 0;
    uint32_t            missCount      = 0;
    uint32_t            age            = 0;     // dwells since init
};

struct TrackTableHeader {
    uint32_t            messageId      = MSG_ID_TRACK_TABLE;
    uint64_t            timestamp      = 0;     // microseconds since epoch
    uint32_t            numTracks      = 0;
};
#pragma pack(pop)

/**
 * @brief Receives track updates via UDP and feeds them into TrackManager
 *
 * Listens on a configurable UDP port (default 50001) for binary
 * TrackUpdateMessage (single track) or TrackTableMessage (multiple tracks)
 * datagrams from an external tracking system.
 */
class UdpTrackReceiver : public QObject {
    Q_OBJECT

public:
    explicit UdpTrackReceiver(TrackManager* trackManager, QObject* parent = nullptr);
    ~UdpTrackReceiver() override;

    bool start(quint16 port = 50001);
    void stop();
    bool isListening() const;

    quint16 port() const { return m_port; }
    uint64_t messagesReceived() const { return m_messagesReceived; }

signals:
    void trackReceived(uint32_t trackId);
    void tracksReceived(uint32_t count);
    void error(const QString& message);

private slots:
    void onReadyRead();

private:
    void processTrackUpdate(const TrackUpdateMessage& msg);
    void processTrackTable(const QByteArray& data);

    TrackManager* m_trackManager;
    QUdpSocket*   m_socket;
    quint16       m_port = 50001;
    uint64_t      m_messagesReceived = 0;

    // Maps external trackId -> internal TrackManager trackId
    QHash<uint32_t, QString> m_externalToInternalId;
};

} // namespace CounterUAS

#endif // UDPTRACKRECEIVER_H
