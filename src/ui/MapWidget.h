#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QHash>
#include <QPainter>
#include "core/Track.h"

namespace CounterUAS {

class MapWidget : public QWidget {
    Q_OBJECT
    
public:
    explicit MapWidget(QWidget* parent = nullptr);
    
    void setCenter(const GeoPosition& pos);
    void setCenterSilent(const GeoPosition& pos);  // Set center without emitting signal
    GeoPosition center() const { return m_center; }
    
    void setZoom(double zoom);
    void setZoomSilent(double zoom);  // Set zoom without emitting signal
    double zoom() const { return m_zoom; }
    
    // Convert between zoom level and range scale (meters)
    static double zoomToRangeScale(double zoom);
    static double rangeScaleToZoom(double rangeM);
    
    void selectTrack(const QString& trackId);
    QString selectedTrack() const { return m_selectedTrackId; }
    
    // Pan controls
    void pan(const QPointF& delta);
    void setPanEnabled(bool enabled) { m_panEnabled = enabled; }
    bool isPanEnabled() const { return m_panEnabled; }
    
public slots:
    void addTrack(const QString& trackId);
    void updateTrack(const QString& trackId);
    void removeTrack(const QString& trackId);
    void clearTracks();
    
signals:
    void trackSelected(const QString& trackId);
    void mapClicked(const GeoPosition& pos);
    void zoomChanged(double zoom);
    void centerChanged(const GeoPosition& pos);
    
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    
private:
    QPointF geoToScreen(const GeoPosition& pos) const;
    GeoPosition screenToGeo(const QPointF& screen) const;
    void drawGrid(QPainter& painter);
    void drawTracks(QPainter& painter);
    void drawDefendedArea(QPainter& painter);
    QColor colorForClassification(TrackClassification cls) const;
    
    GeoPosition m_center;
    double m_zoom = 15.0;
    QString m_selectedTrackId;
    QHash<QString, Track*> m_tracks;
    
    // Pan state
    bool m_panEnabled = true;
    bool m_panning = false;
    QPointF m_lastPanPos;
};

} // namespace CounterUAS

#endif // MAPWIDGET_H
