#include "ui/MapWidget.h"
#include "utils/CoordinateUtils.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtMath>
#include <cmath>

namespace CounterUAS {

MapWidget::MapWidget(QWidget* parent) : QWidget(parent) {
    setMinimumSize(400, 300);
    setMouseTracking(true);
    
    m_center.latitude = 34.0522;
    m_center.longitude = -118.2437;
    m_center.altitude = 0;
    
    // Initialize view range from default zoom
    m_viewRangeM = zoomToRangeScale(m_zoom);
}

void MapWidget::setCenter(const GeoPosition& pos) {
    m_center = pos;
    emit centerChanged(m_center);
    update();
}

void MapWidget::setCenterSilent(const GeoPosition& pos) {
    m_center = pos;
    update();
}

void MapWidget::setZoom(double zoom) {
    m_zoom = qBound(1.0, zoom, 20.0);
    m_viewRangeM = zoomToRangeScale(m_zoom);
    emit zoomChanged(m_zoom);
    update();
}

void MapWidget::setZoomSilent(double zoom) {
    m_zoom = qBound(1.0, zoom, 20.0);
    m_viewRangeM = zoomToRangeScale(m_zoom);
    update();
}

// Convert map zoom level (1-20) to range scale in meters
// Higher zoom = smaller range (more zoomed in)
// Zoom 20 ~ 100m range, Zoom 1 ~ 50000m range
double MapWidget::zoomToRangeScale(double zoom) {
    // Logarithmic conversion: rangeScale = baseRange / 2^(zoom - minZoom)
    // At zoom 1: ~50000m, at zoom 20: ~100m
    double rangeScale = 50000.0 / pow(2.0, (zoom - 1.0) / 2.5);
    return qBound(100.0, rangeScale, 50000.0);
}

// Convert range scale in meters to map zoom level
double MapWidget::rangeScaleToZoom(double rangeM) {
    // Inverse of the above: zoom = minZoom + log2(baseRange / rangeScale) * 2.5
    double zoom = 1.0 + log2(50000.0 / rangeM) * 2.5;
    return qBound(1.0, zoom, 20.0);
}

void MapWidget::pan(const QPointF& delta) {
    // Convert pixel delta to meters using the same scale as geoToScreen
    double scale = mapRadius() / m_viewRangeM;  // pixels per meter
    double distanceX = -delta.x() / scale;  // meters (negative: drag right = move view left = center moves right in world)
    double distanceY = delta.y() / scale;   // meters (positive: drag down = move view up = center moves down in world)
    
    // Convert meter offset to lat/lon using proper geographic conversion
    double dLat = distanceY / CoordinateUtils::DEG_TO_M_LAT;
    double dLon = distanceX / CoordinateUtils::degToMeterLon(m_center.latitude);
    
    m_center.latitude += dLat;
    m_center.longitude += dLon;
    emit centerChanged(m_center);
    update();
}

void MapWidget::selectTrack(const QString& trackId) {
    m_selectedTrackId = trackId;
    update();
}

void MapWidget::addTrack(const QString& trackId) {
    Q_UNUSED(trackId)
    update();
}

void MapWidget::updateTrack(const QString& trackId) {
    Q_UNUSED(trackId)
    update();
}

void MapWidget::removeTrack(const QString& trackId) {
    m_tracks.remove(trackId);
    if (m_selectedTrackId == trackId) {
        m_selectedTrackId.clear();
    }
    update();
}

void MapWidget::clearTracks() {
    m_tracks.clear();
    m_selectedTrackId.clear();
    update();
}

void MapWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Background
    painter.fillRect(rect(), QColor(30, 40, 50));
    
    // Draw grid
    drawGrid(painter);
    
    // Draw defended area
    drawDefendedArea(painter);
    
    // Draw tracks
    drawTracks(painter);
    
    // Draw center crosshair
    painter.setPen(QPen(Qt::white, 1));
    int cx = width() / 2;
    int cy = height() / 2;
    painter.drawLine(cx - 10, cy, cx + 10, cy);
    painter.drawLine(cx, cy - 10, cx, cy + 10);
    
    // Draw scale and info
    painter.setPen(Qt::white);
    QString rangeStr;
    if (m_viewRangeM >= 1000) {
        rangeStr = QString("Range: %1 km").arg(m_viewRangeM / 1000.0, 0, 'f', 1);
    } else {
        rangeStr = QString("Range: %1 m").arg(m_viewRangeM, 0, 'f', 0);
    }
    painter.drawText(10, height() - 10, 
                    QString("Lat: %1  Lon: %2  %3")
                        .arg(m_center.latitude, 0, 'f', 4)
                        .arg(m_center.longitude, 0, 'f', 4)
                        .arg(rangeStr));
}

void MapWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && m_panEnabled) {
        m_panning = true;
        m_lastPanPos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    
    if (event->button() == Qt::RightButton) {
        GeoPosition clickPos = screenToGeo(event->pos());
        emit mapClicked(clickPos);
    }
}

void MapWidget::mouseMoveEvent(QMouseEvent* event) {
    if (m_panning) {
        QPointF delta = event->pos() - m_lastPanPos;
        m_lastPanPos = event->pos();
        pan(delta);
        event->accept();
        return;
    }
    QWidget::mouseMoveEvent(event);
}

void MapWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (m_panning && event->button() == Qt::LeftButton) {
        m_panning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    QWidget::mouseReleaseEvent(event);
}

void MapWidget::wheelEvent(QWheelEvent* event) {
    double delta = event->angleDelta().y() / 120.0;
    setZoom(m_zoom + delta * 0.5);
}

void MapWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
}

double MapWidget::mapRadius() const {
    // Use the smaller dimension to define the "view radius" (half the visible range)
    return qMin(width(), height()) / 2.0 - 20;  // Leave margin for labels
}

QPointF MapWidget::geoToScreen(const GeoPosition& pos) const {
    // Convert geographic position to local meters from center
    QPointF localMeters = CoordinateUtils::geoToLocal(pos, m_center);
    
    // Scale: pixels per meter based on view range
    double scale = mapRadius() / m_viewRangeM;
    
    // Convert meters to screen pixels (Y is inverted in screen coordinates)
    double dx = localMeters.x() * scale;
    double dy = -localMeters.y() * scale;
    
    return QPointF(width() / 2.0 + dx, height() / 2.0 + dy);
}

GeoPosition MapWidget::screenToGeo(const QPointF& screen) const {
    // Scale: pixels per meter based on view range
    double scale = mapRadius() / m_viewRangeM;
    
    // Convert screen pixels to local meters (Y is inverted)
    double localX = (screen.x() - width() / 2.0) / scale;
    double localY = -(screen.y() - height() / 2.0) / scale;
    
    // Convert local meters to geographic position
    return CoordinateUtils::localToGeo(QPointF(localX, localY), m_center);
}

void MapWidget::drawGrid(QPainter& painter) {
    painter.setPen(QPen(QColor(60, 70, 80), 1));
    
    // Calculate grid spacing in degrees based on view range
    // We want roughly 5-10 grid lines across the view
    double viewRangeDegLat = m_viewRangeM / CoordinateUtils::DEG_TO_M_LAT;
    double gridSpacing = viewRangeDegLat / 5.0;
    
    // Round to a nice value
    double magnitude = std::pow(10.0, std::floor(std::log10(gridSpacing)));
    gridSpacing = std::ceil(gridSpacing / magnitude) * magnitude;
    
    double startLat = std::floor(m_center.latitude / gridSpacing) * gridSpacing - gridSpacing * 5;
    double startLon = std::floor(m_center.longitude / gridSpacing) * gridSpacing - gridSpacing * 5;
    
    for (int i = 0; i < 12; ++i) {
        GeoPosition p1, p2;
        p1.latitude = startLat + i * gridSpacing;
        p1.longitude = startLon;
        p2.latitude = startLat + i * gridSpacing;
        p2.longitude = startLon + gridSpacing * 12;
        
        QPointF s1 = geoToScreen(p1);
        QPointF s2 = geoToScreen(p2);
        painter.drawLine(s1, s2);
    }
    
    for (int i = 0; i < 12; ++i) {
        GeoPosition p1, p2;
        p1.latitude = startLat;
        p1.longitude = startLon + i * gridSpacing;
        p2.latitude = startLat + gridSpacing * 12;
        p2.longitude = startLon + i * gridSpacing;
        
        QPointF s1 = geoToScreen(p1);
        QPointF s2 = geoToScreen(p2);
        painter.drawLine(s1, s2);
    }
}

void MapWidget::drawDefendedArea(QPainter& painter) {
    // Draw defended area circles using proper pixel-per-meter scale
    QPointF centerPt = geoToScreen(m_center);
    double scale = mapRadius() / m_viewRangeM;  // pixels per meter
    
    // Critical zone (red) - 500m radius
    painter.setPen(QPen(QColor(255, 0, 0, 100), 2));
    painter.setBrush(QColor(255, 0, 0, 30));
    double criticalRadius = 500.0 * scale;
    painter.drawEllipse(centerPt, criticalRadius, criticalRadius);
    
    // Warning zone (yellow) - 1500m radius
    painter.setPen(QPen(QColor(255, 255, 0, 100), 2));
    painter.setBrush(QColor(255, 255, 0, 20));
    double warningRadius = 1500.0 * scale;
    painter.drawEllipse(centerPt, warningRadius, warningRadius);
}

void MapWidget::drawTracks(QPainter& painter) {
    for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        Track* track = it.value();
        if (!track || track->state() == TrackState::Dropped) continue;
        
        QPointF pos = geoToScreen(track->position());
        QColor color = colorForClassification(track->classification());
        
        // Draw track symbol
        bool selected = (it.key() == m_selectedTrackId);
        int size = selected ? 12 : 8;
        
        painter.setPen(QPen(color, selected ? 3 : 2));
        painter.setBrush(Qt::NoBrush);
        
        // Draw diamond shape for track
        QPolygonF diamond;
        diamond << QPointF(pos.x(), pos.y() - size)
                << QPointF(pos.x() + size, pos.y())
                << QPointF(pos.x(), pos.y() + size)
                << QPointF(pos.x() - size, pos.y());
        painter.drawPolygon(diamond);
        
        // Draw velocity vector
        VelocityVector vel = track->velocity();
        double speed = vel.speed();
        if (speed > 1.0) {
            double heading = vel.heading();
            double vx = std::sin(qDegreesToRadians(heading)) * speed * 0.5;
            double vy = -std::cos(qDegreesToRadians(heading)) * speed * 0.5;
            painter.drawLine(pos, QPointF(pos.x() + vx, pos.y() + vy));
        }
        
        // Draw label
        painter.setPen(Qt::white);
        painter.drawText(pos.x() + size + 5, pos.y() + 4, track->trackId());
    }
}

QColor MapWidget::colorForClassification(TrackClassification cls) const {
    switch (cls) {
        case TrackClassification::Hostile: return Qt::red;
        case TrackClassification::Friendly: return Qt::cyan;
        case TrackClassification::Pending: return Qt::yellow;
        case TrackClassification::Neutral: return Qt::gray;
        default: return Qt::green;
    }
}

} // namespace CounterUAS
