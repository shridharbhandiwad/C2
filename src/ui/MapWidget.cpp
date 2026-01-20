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
    emit zoomChanged(m_zoom);
    update();
}

void MapWidget::setZoomSilent(double zoom) {
    m_zoom = qBound(1.0, zoom, 20.0);
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
    double scale = m_zoom * 5000.0;  // Same scale factor as geoToScreen
    double dLon = -delta.x() / scale;
    double dLat = delta.y() / scale;
    
    m_center.longitude += dLon;
    m_center.latitude += dLat;
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
    painter.drawText(10, height() - 10, 
                    QString("Lat: %1  Lon: %2  Zoom: %3")
                        .arg(m_center.latitude, 0, 'f', 4)
                        .arg(m_center.longitude, 0, 'f', 4)
                        .arg(m_zoom, 0, 'f', 1));
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

QPointF MapWidget::geoToScreen(const GeoPosition& pos) const {
    double scale = m_zoom * 5000.0;  // pixels per degree at this zoom
    
    double dx = (pos.longitude - m_center.longitude) * scale;
    double dy = -(pos.latitude - m_center.latitude) * scale;
    
    return QPointF(width() / 2.0 + dx, height() / 2.0 + dy);
}

GeoPosition MapWidget::screenToGeo(const QPointF& screen) const {
    double scale = m_zoom * 5000.0;
    
    double dx = (screen.x() - width() / 2.0) / scale;
    double dy = -(screen.y() - height() / 2.0) / scale;
    
    GeoPosition pos;
    pos.latitude = m_center.latitude + dy;
    pos.longitude = m_center.longitude + dx;
    pos.altitude = m_center.altitude;
    return pos;
}

void MapWidget::drawGrid(QPainter& painter) {
    painter.setPen(QPen(QColor(60, 70, 80), 1));
    
    double gridSpacing = 0.01 / (m_zoom / 10.0);
    
    double startLat = std::floor(m_center.latitude / gridSpacing) * gridSpacing - gridSpacing * 5;
    double startLon = std::floor(m_center.longitude / gridSpacing) * gridSpacing - gridSpacing * 5;
    
    for (int i = 0; i < 10; ++i) {
        GeoPosition p1, p2;
        p1.latitude = startLat + i * gridSpacing;
        p1.longitude = startLon;
        p2.latitude = startLat + i * gridSpacing;
        p2.longitude = startLon + gridSpacing * 10;
        
        QPointF s1 = geoToScreen(p1);
        QPointF s2 = geoToScreen(p2);
        painter.drawLine(s1, s2);
    }
    
    for (int i = 0; i < 10; ++i) {
        GeoPosition p1, p2;
        p1.latitude = startLat;
        p1.longitude = startLon + i * gridSpacing;
        p2.latitude = startLat + gridSpacing * 10;
        p2.longitude = startLon + i * gridSpacing;
        
        QPointF s1 = geoToScreen(p1);
        QPointF s2 = geoToScreen(p2);
        painter.drawLine(s1, s2);
    }
}

void MapWidget::drawDefendedArea(QPainter& painter) {
    // Draw defended area circles
    QPointF centerPt = geoToScreen(m_center);
    
    // Critical zone (red)
    painter.setPen(QPen(QColor(255, 0, 0, 100), 2));
    painter.setBrush(QColor(255, 0, 0, 30));
    double criticalRadius = 500.0 * m_zoom * 0.01;  // Simplified
    painter.drawEllipse(centerPt, criticalRadius, criticalRadius);
    
    // Warning zone (yellow)
    painter.setPen(QPen(QColor(255, 255, 0, 100), 2));
    painter.setBrush(QColor(255, 255, 0, 20));
    double warningRadius = 1500.0 * m_zoom * 0.01;
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
