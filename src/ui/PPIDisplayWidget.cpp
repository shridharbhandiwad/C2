#include "ui/PPIDisplayWidget.h"
#include "core/TrackManager.h"
#include "core/EngagementManager.h"
#include "effectors/EffectorInterface.h"
#include "utils/CoordinateUtils.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QContextMenuEvent>
#include <QToolTip>
#include <QtMath>
#include <QDateTime>
#include <QUrlQuery>
#include <QImageReader>
#include <QMenu>
#include <QAction>
#include <cmath>

namespace CounterUAS {

PPIDisplayWidget::PPIDisplayWidget(QWidget* parent)
    : QWidget(parent)
    , m_sweepTimer(new QTimer(this))
    , m_historyTimer(new QTimer(this))
    , m_networkManager(new QNetworkAccessManager(this))
    , m_tileCache(100)  // Cache up to 100 tiles
{
    setMinimumSize(400, 400);
    setMouseTracking(true);
    
    // Default center (Los Angeles area)
    m_center.latitude = 34.0522;
    m_center.longitude = -118.2437;
    m_center.altitude = 0;
    
    // Initialize sweep trail
    m_sweepTrail.fill(0.0, SWEEP_TRAIL_LENGTH);
    
    // Sweep timer - update at 60 FPS
    connect(m_sweepTimer, &QTimer::timeout, this, &PPIDisplayWidget::updateSweep);
    m_sweepTimer->setInterval(16);  // ~60 FPS
    
    // History update timer
    connect(m_historyTimer, &QTimer::timeout, this, &PPIDisplayWidget::updateTrackHistory);
    m_historyTimer->setInterval(100);  // 10 Hz
    m_historyTimer->start();
    
    // Network manager for map tiles
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &PPIDisplayWidget::onMapTileReceived);
    
    // Default map tile URL (OpenStreetMap)
    m_mapTileUrlTemplate = "https://tile.openstreetmap.org/{z}/{x}/{y}.png";
}

PPIDisplayWidget::~PPIDisplayWidget() {
    stopSweep();
}

void PPIDisplayWidget::setCenter(const GeoPosition& pos) {
    m_center = pos;
    m_backgroundDirty = true;
    updateVisibleTiles();
    emit centerChanged(m_center);
    update();
}

void PPIDisplayWidget::setCenterSilent(const GeoPosition& pos) {
    m_center = pos;
    m_backgroundDirty = true;
    updateVisibleTiles();
    update();
}

void PPIDisplayWidget::setRangeScale(double rangeM) {
    m_rangeScaleM = qBound(100.0, rangeM, 50000.0);
    m_backgroundDirty = true;
    emit rangeScaleChanged(m_rangeScaleM);
    updateVisibleTiles();
    update();
}

void PPIDisplayWidget::setRangeScaleSilent(double rangeM) {
    m_rangeScaleM = qBound(100.0, rangeM, 50000.0);
    m_backgroundDirty = true;
    updateVisibleTiles();
    update();
}

// Convert range scale (meters) to map zoom level (1-20)
// Higher zoom = more zoomed in = smaller range
double PPIDisplayWidget::rangeScaleToMapZoom(double rangeM) {
    // Logarithmic conversion: zoom = minZoom + log2(baseRange / rangeScale) * 2.5
    // At rangeM 50000m -> zoom 1, at rangeM 100m -> zoom 20
    double zoom = 1.0 + log2(50000.0 / rangeM) * 2.5;
    return qBound(1.0, zoom, 20.0);
}

// Convert map zoom level (1-20) to range scale in meters
double PPIDisplayWidget::mapZoomToRangeScale(double zoom) {
    // Inverse: rangeScale = baseRange / 2^((zoom - minZoom) / 2.5)
    double rangeScale = 50000.0 / pow(2.0, (zoom - 1.0) / 2.5);
    return qBound(100.0, rangeScale, 50000.0);
}

void PPIDisplayWidget::panView(const QPointF& deltaPixels) {
    if (qFuzzyIsNull(deltaPixels.x()) && qFuzzyIsNull(deltaPixels.y())) {
        return;
    }
    
    // Convert pixel delta to geo delta
    double scale = ppiRadius() / m_rangeScaleM;
    double distanceX = -deltaPixels.x() / scale;  // meters
    double distanceY = deltaPixels.y() / scale;   // meters (y is inverted)
    
    // Convert meter offset to lat/lon
    double dLat = distanceY / CoordinateUtils::DEG_TO_M_LAT;
    double dLon = distanceX / CoordinateUtils::degToMeterLon(m_center.latitude);
    
    m_center.latitude += dLat;
    m_center.longitude += dLon;
    
    m_backgroundDirty = true;
    updateVisibleTiles();
    emit centerChanged(m_center);
    update();
}

void PPIDisplayWidget::setDisplayMode(PPIDisplayMode mode) {
    if (m_displayMode != mode) {
        m_displayMode = mode;
        m_backgroundDirty = true;
        
        // Adjust colors based on mode
        switch (mode) {
            case PPIDisplayMode::RadarOnly:
                m_backgroundColor = QColor(10, 20, 10);
                m_sweepColor = QColor(0, 255, 0, 200);
                m_rangeRingColor = QColor(0, 180, 0, 150);
                break;
            case PPIDisplayMode::MapOverlay:
                m_backgroundColor = QColor(30, 30, 30);
                m_sweepColor = QColor(0, 255, 0, 150);
                m_rangeRingColor = QColor(255, 255, 255, 150);
                break;
            case PPIDisplayMode::MapOnly:
                m_backgroundColor = QColor(240, 240, 240);
                m_sweepColor = QColor(0, 0, 0, 0);  // Hidden
                m_rangeRingColor = QColor(100, 100, 100, 100);
                break;
            case PPIDisplayMode::NightVision:
                m_backgroundColor = QColor(0, 10, 0);
                m_sweepColor = QColor(0, 200, 0, 220);
                m_rangeRingColor = QColor(0, 150, 0, 180);
                break;
        }
        
        emit displayModeChanged(mode);
        update();
    }
}

void PPIDisplayWidget::setSweepMode(PPISweepMode mode) {
    m_sweepMode = mode;
    if (mode == PPISweepMode::None) {
        stopSweep();
    }
    update();
}

void PPIDisplayWidget::setSweepSpeed(double degreesPerSecond) {
    m_sweepSpeed = qBound(1.0, degreesPerSecond, 180.0);
}

void PPIDisplayWidget::setSectorLimits(double startDeg, double endDeg) {
    m_sectorStart = fmod(startDeg + 360.0, 360.0);
    m_sectorEnd = fmod(endDeg + 360.0, 360.0);
}

void PPIDisplayWidget::setRangeRingCount(int count) {
    m_rangeRingCount = qBound(1, count, 20);
    m_backgroundDirty = true;
    update();
}

void PPIDisplayWidget::setShowRangeLabels(bool show) {
    m_showRangeLabels = show;
    update();
}

void PPIDisplayWidget::setAzimuthDivisions(int divisions) {
    m_azimuthDivisions = qBound(4, divisions, 36);
    m_backgroundDirty = true;
    update();
}

void PPIDisplayWidget::setShowAzimuthLabels(bool show) {
    m_showAzimuthLabels = show;
    update();
}

void PPIDisplayWidget::setTrackManager(TrackManager* manager) {
    if (m_trackManager) {
        disconnect(m_trackManager, nullptr, this, nullptr);
    }
    
    m_trackManager = manager;
    
    if (m_trackManager) {
        connect(m_trackManager, &TrackManager::trackCreated,
                this, &PPIDisplayWidget::addTrack);
        connect(m_trackManager, &TrackManager::trackUpdated,
                this, &PPIDisplayWidget::updateTrack);
        connect(m_trackManager, &TrackManager::trackDropped,
                this, &PPIDisplayWidget::removeTrack);
    }
}

void PPIDisplayWidget::setEngagementManager(EngagementManager* manager) {
    m_engagementManager = manager;
}

void PPIDisplayWidget::selectTrack(const QString& trackId) {
    m_selectedTrackId = trackId;
    update();
}

void PPIDisplayWidget::setShowTrackHistory(bool show) {
    m_showTrackHistory = show;
    update();
}

void PPIDisplayWidget::setTrackDisplayFilter(TrackDisplayFilter filter) {
    if (m_trackDisplayFilter != filter) {
        m_trackDisplayFilter = filter;
        update();
    }
}

void PPIDisplayWidget::setTrackHistoryLength(int seconds) {
    m_trackHistorySeconds = qBound(5, seconds, 300);
}

void PPIDisplayWidget::setTrackHistoryPoints(const QString& trackId, int points) {
    m_trackHistoryPoints[trackId] = points;
    emit trackHistoryPointsChanged(trackId, points);
    update();
}

int PPIDisplayWidget::trackHistoryPoints(const QString& trackId) const {
    return m_trackHistoryPoints.value(trackId, -1);  // -1 means use default
}

void PPIDisplayWidget::focusTrack(const QString& trackId) {
    if (m_tracks.contains(trackId)) {
        m_focusedTrackId = trackId;
        
        // Center view on focused track
        Track* track = m_tracks[trackId];
        if (track) {
            setCenter(track->position());
            // Zoom in for better focus
            setRangeScale(m_rangeScaleM / m_focusZoomFactor);
        }
        
        emit trackFocused(trackId);
        update();
    }
}

void PPIDisplayWidget::clearFocus() {
    m_focusedTrackId.clear();
    update();
}

void PPIDisplayWidget::setDefendedAreaVisible(bool visible) {
    m_showDefendedArea = visible;
    update();
}

void PPIDisplayWidget::setDefendedAreaRadii(double criticalM, double warningM, double detectionM) {
    m_criticalRadiusM = criticalM;
    m_warningRadiusM = warningM;
    m_detectionRadiusM = detectionM;
    update();
}

void PPIDisplayWidget::setMapTileUrl(const QString& urlTemplate) {
    m_mapTileUrlTemplate = urlTemplate;
    m_tileCache.clear();
    updateVisibleTiles();
}

void PPIDisplayWidget::setMapZoomLevel(int zoom) {
    m_mapZoomLevel = qBound(1, zoom, 19);
    m_tileCache.clear();
    updateVisibleTiles();
}

void PPIDisplayWidget::setMapOpacity(double opacity) {
    m_mapOpacity = qBound(0.0, opacity, 1.0);
    update();
}

bool PPIDisplayWidget::loadLocalMap(const QString& filePath) {
    QImageReader reader(filePath);
    reader.setAutoTransform(true);
    QImage image = reader.read();
    if (image.isNull()) {
        return false;
    }

    // Check for valid image dimensions before proceeding
    if (image.width() <= 0 || image.height() <= 0) {
        return false;
    }

    m_localMap = QPixmap::fromImage(image);
    
    // Verify pixmap conversion succeeded and has valid dimensions
    if (m_localMap.isNull() || m_localMap.width() <= 0 || m_localMap.height() <= 0) {
        m_localMap = QPixmap();  // Clear any partially created pixmap
        return false;
    }

    m_localMapOffset = QPointF(0.0, 0.0);
    updateLocalMapBaseScale();
    
    // Validate that the base scale is finite and positive before using it
    if (!std::isfinite(m_localMapBaseScale) || m_localMapBaseScale <= 0.0) {
        m_localMapBaseScale = 1.0;
    }
    m_localMapScale = m_localMapBaseScale;
    
    m_mapPanning = false;
    if (m_mapPanEnabled) {
        setCursor(Qt::OpenHandCursor);
    }
    m_tileCache.clear();
    m_pendingTiles.clear();
    update();
    return true;
}

void PPIDisplayWidget::clearLocalMap() {
    m_localMap = QPixmap();
    m_localMapOffset = QPointF(0.0, 0.0);
    m_localMapScale = 1.0;
    m_localMapBaseScale = 1.0;
    m_mapPanning = false;
    unsetCursor();
    updateVisibleTiles();
    update();
}

void PPIDisplayWidget::zoomLocalMap(double factor) {
    zoomLocalMap(factor, screenCenter());
}

void PPIDisplayWidget::zoomLocalMap(double factor, const QPointF& anchor) {
    if (m_localMap.isNull()) {
        return;
    }

    // Guard against invalid factor
    if (!std::isfinite(factor) || factor <= 0.0) {
        return;
    }

    // Guard against invalid scale values
    if (m_localMapScale <= 0.0 || !std::isfinite(m_localMapScale)) {
        m_localMapScale = 1.0;
    }

    double newScale = m_localMapScale * factor;
    if (!std::isfinite(newScale)) {
        return;
    }
    newScale = qBound(0.05, newScale, 20.0);
    if (qFuzzyCompare(newScale, m_localMapScale)) {
        return;
    }

    // Guard against invalid image dimensions
    if (m_localMap.width() <= 0 || m_localMap.height() <= 0) {
        return;
    }

    // Guard against invalid anchor point
    if (!std::isfinite(anchor.x()) || !std::isfinite(anchor.y())) {
        return;
    }

    QPointF imageCenter(m_localMap.width() / 2.0, m_localMap.height() / 2.0);
    QPointF mapCenter = screenCenter() + m_localMapOffset;
    QPointF imagePos = (anchor - mapCenter) / m_localMapScale + imageCenter;
    QPointF newMapCenter = anchor - (imagePos - imageCenter) * newScale;

    // Validate computed values before applying
    if (!std::isfinite(newMapCenter.x()) || !std::isfinite(newMapCenter.y())) {
        return;
    }

    QPointF newOffset = newMapCenter - screenCenter();
    
    // Bound the offset to reasonable values to prevent floating-point overflow
    const double maxOffset = 100000.0;
    if (qAbs(newOffset.x()) > maxOffset || qAbs(newOffset.y()) > maxOffset) {
        return;
    }

    m_localMapScale = newScale;
    m_localMapOffset = newOffset;
    update();
}

void PPIDisplayWidget::panLocalMap(const QPointF& delta) {
    if (m_localMap.isNull()) {
        return;
    }
    
    // Guard against invalid delta
    if (!std::isfinite(delta.x()) || !std::isfinite(delta.y())) {
        return;
    }
    
    QPointF newOffset = m_localMapOffset + delta;
    
    // Bound the offset to reasonable values
    const double maxOffset = 100000.0;
    newOffset.setX(qBound(-maxOffset, newOffset.x(), maxOffset));
    newOffset.setY(qBound(-maxOffset, newOffset.y(), maxOffset));
    
    m_localMapOffset = newOffset;
    update();
}

void PPIDisplayWidget::resetLocalMapView() {
    if (m_localMap.isNull()) {
        return;
    }
    updateLocalMapBaseScale();
    
    // Validate base scale before using it
    if (!std::isfinite(m_localMapBaseScale) || m_localMapBaseScale <= 0.0) {
        m_localMapBaseScale = 1.0;
    }
    
    m_localMapScale = m_localMapBaseScale;
    m_localMapOffset = QPointF(0.0, 0.0);
    update();
}

void PPIDisplayWidget::setMapPanEnabled(bool enabled) {
    m_mapPanEnabled = enabled;
    if (!m_localMap.isNull() && m_mapPanEnabled && !m_mapPanning) {
        setCursor(Qt::OpenHandCursor);
    } else if (!m_mapPanning) {
        unsetCursor();
    }
}

void PPIDisplayWidget::setBackgroundColor(const QColor& color) {
    m_backgroundColor = color;
    m_backgroundDirty = true;
    update();
}

void PPIDisplayWidget::setSweepColor(const QColor& color) {
    m_sweepColor = color;
    update();
}

void PPIDisplayWidget::setRangeRingColor(const QColor& color) {
    m_rangeRingColor = color;
    m_backgroundDirty = true;
    update();
}

void PPIDisplayWidget::setTrackColors(const QColor& hostile, const QColor& friendly,
                                       const QColor& unknown, const QColor& neutral) {
    m_hostileColor = hostile;
    m_friendlyColor = friendly;
    m_unknownColor = unknown;
    m_neutralColor = neutral;
    update();
}

void PPIDisplayWidget::setNorthUp(bool northUp) {
    m_northUp = northUp;
    update();
}

void PPIDisplayWidget::setHeading(double headingDeg) {
    m_heading = fmod(headingDeg + 360.0, 360.0);
    if (!m_northUp) {
        update();
    }
}

void PPIDisplayWidget::addTrack(const QString& trackId) {
    if (m_trackManager) {
        Track* track = m_trackManager->track(trackId);
        if (track) {
            m_tracks[trackId] = track;
            m_trackHistory[trackId] = QList<TrackHistoryPoint>();
        }
    }
    update();
}

void PPIDisplayWidget::updateTrack(const QString& trackId) {
    if (m_trackManager && m_tracks.contains(trackId)) {
        Track* track = m_tracks[trackId];
        if (track) {
            // Add to history
            QPointF ppiPos = geoToPPI(track->position());
            TrackHistoryPoint histPt;
            histPt.position = ppiPos;
            histPt.timestamp = QDateTime::currentMSecsSinceEpoch();
            histPt.intensity = 1.0;
            m_trackHistory[trackId].append(histPt);
            
            // Trim old history
            qint64 cutoffTime = histPt.timestamp - (m_trackHistorySeconds * 1000);
            while (!m_trackHistory[trackId].isEmpty() && 
                   m_trackHistory[trackId].first().timestamp < cutoffTime) {
                m_trackHistory[trackId].removeFirst();
            }
        }
    }
    update();
}

void PPIDisplayWidget::removeTrack(const QString& trackId) {
    m_tracks.remove(trackId);
    m_trackHistory.remove(trackId);
    if (m_selectedTrackId == trackId) {
        m_selectedTrackId.clear();
    }
    update();
}

void PPIDisplayWidget::clearTracks() {
    m_tracks.clear();
    m_trackHistory.clear();
    m_selectedTrackId.clear();
    update();
}

void PPIDisplayWidget::startSweep() {
    if (!m_sweepRunning && m_sweepMode != PPISweepMode::None) {
        m_sweepRunning = true;
        m_sweepTimer->start();
    }
}

void PPIDisplayWidget::stopSweep() {
    m_sweepRunning = false;
    m_sweepTimer->stop();
}

void PPIDisplayWidget::resetSweep() {
    m_sweepAngle = 0.0;
    m_sweepTrail.fill(0.0);
    update();
}

void PPIDisplayWidget::refresh() {
    m_backgroundDirty = true;
    update();
}

void PPIDisplayWidget::updateSweep() {
    // Calculate angle increment based on timer interval and sweep speed
    double angleIncrement = m_sweepSpeed * (m_sweepTimer->interval() / 1000.0);
    
    if (m_sweepMode == PPISweepMode::Rotating) {
        m_sweepAngle = fmod(m_sweepAngle + angleIncrement, 360.0);
    } else if (m_sweepMode == PPISweepMode::Sector) {
        m_sweepAngle += angleIncrement;
        if (m_sweepAngle >= m_sectorEnd) {
            m_sweepAngle = m_sectorStart;
        }
    }
    
    // Update sweep trail (persistence effect)
    for (int i = SWEEP_TRAIL_LENGTH - 1; i > 0; --i) {
        m_sweepTrail[i] = m_sweepTrail[i - 1] * 0.95;  // Decay
    }
    m_sweepTrail[0] = m_sweepAngle;
    
    emit sweepAngleChanged(m_sweepAngle);
    update();
}

void PPIDisplayWidget::updateTrackHistory() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 cutoffTime = currentTime - (m_trackHistorySeconds * 1000);
    
    // Update intensity for fading effect
    for (auto it = m_trackHistory.begin(); it != m_trackHistory.end(); ++it) {
        QList<TrackHistoryPoint>& history = it.value();
        for (TrackHistoryPoint& pt : history) {
            double age = (currentTime - pt.timestamp) / 1000.0;
            pt.intensity = qMax(0.0, 1.0 - (age / m_trackHistorySeconds));
        }
        
        // Remove old points
        while (!history.isEmpty() && history.first().timestamp < cutoffTime) {
            history.removeFirst();
        }
    }
}

void PPIDisplayWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Draw layers in order
    drawBackground(painter);
    
    if (m_displayMode == PPIDisplayMode::MapOverlay || 
        m_displayMode == PPIDisplayMode::MapOnly) {
        drawMapTiles(painter);
    }
    
    drawRangeRings(painter);
    drawAzimuthLines(painter);
    drawDefendedArea(painter);
    
    if (m_sweepMode != PPISweepMode::None && m_displayMode != PPIDisplayMode::MapOnly) {
        drawSweepTrail(painter);
        drawSweep(painter);
    }
    
    drawTracks(painter);
    drawNorthIndicator(painter);
    drawCompassRose(painter);
    drawScaleInfo(painter);
    drawFilterIndicator(painter);
}

void PPIDisplayWidget::mousePressEvent(QMouseEvent* event) {
    // Right-click: check if on track for context menu, otherwise start panning
    if (event->button() == Qt::RightButton) {
        QString trackId = findTrackAtPoint(event->pos());
        if (!trackId.isEmpty()) {
            // Don't start panning - context menu will be shown
            event->accept();
            return;
        }
        // Not on track - start view panning
        m_mapPanning = true;
        m_lastPanPos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    
    // Middle-click always starts view panning
    if (event->button() == Qt::MiddleButton) {
        m_mapPanning = true;
        m_lastPanPos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    
    // Local map pan with left click when enabled
    if (!m_localMap.isNull() && m_mapPanEnabled && event->button() == Qt::LeftButton) {
        m_mapPanning = true;
        m_lastPanPos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }

    if (event->button() == Qt::LeftButton) {
        QString trackId = findTrackAtPoint(event->pos());
        if (!trackId.isEmpty()) {
            m_selectedTrackId = trackId;
            emit trackSelected(trackId);
            update();
        } else {
            // Convert to geo position
            QPointF ppiPos = event->pos() - screenCenter();
            GeoPosition clickPos = ppiToGeo(ppiPos);
            emit mapClicked(clickPos);
        }
    }
}

void PPIDisplayWidget::mouseDoubleClickEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        QString trackId = findTrackAtPoint(event->pos());
        if (!trackId.isEmpty()) {
            emit trackDoubleClicked(trackId);
        }
    }
}

void PPIDisplayWidget::wheelEvent(QWheelEvent* event) {
    double delta = event->angleDelta().y() / 120.0;
    if (!m_localMap.isNull() && (event->modifiers() & Qt::ControlModifier)) {
        double mapFactor = (delta > 0) ? 1.1 : (1.0 / 1.1);
        zoomLocalMap(mapFactor, event->posF());
        event->accept();
        return;
    }

    double scaleFactor = (delta > 0) ? 0.8 : 1.25;
    setRangeScale(m_rangeScaleM * scaleFactor);
}

void PPIDisplayWidget::mouseMoveEvent(QMouseEvent* event) {
    if (m_mapPanning) {
        QPointF delta = event->pos() - m_lastPanPos;
        m_lastPanPos = event->pos();
        
        // If we have a local map and pan mode is enabled, pan the local map overlay
        if (!m_localMap.isNull() && m_mapPanEnabled) {
            panLocalMap(delta);
        } else {
            // Otherwise, pan the view (center position)
            panView(delta);
        }
        event->accept();
        return;
    }
    QWidget::mouseMoveEvent(event);
}

void PPIDisplayWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (m_mapPanning &&
        (event->button() == Qt::LeftButton || event->button() == Qt::RightButton || 
         event->button() == Qt::MiddleButton)) {
        m_mapPanning = false;
        if (!m_localMap.isNull() && m_mapPanEnabled) {
            setCursor(Qt::OpenHandCursor);
        } else {
            unsetCursor();
        }
        event->accept();
        return;
    }
    QWidget::mouseReleaseEvent(event);
}

void PPIDisplayWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    m_backgroundDirty = true;
    if (!m_localMap.isNull()) {
        double previousBase = m_localMapBaseScale;
        updateLocalMapBaseScale();
        
        // Validate the new base scale
        if (!std::isfinite(m_localMapBaseScale) || m_localMapBaseScale <= 0.0) {
            m_localMapBaseScale = 1.0;
        }
        
        // Check if user was at base scale (not manually zoomed) - use absolute comparison
        // for small values since qFuzzyCompare doesn't work well near zero
        bool wasAtBaseScale = (previousBase > 0.0) && 
                              (qAbs(m_localMapScale - previousBase) < 0.001 ||
                               qFuzzyCompare(m_localMapScale + 1.0, previousBase + 1.0));
        if (wasAtBaseScale) {
            m_localMapScale = m_localMapBaseScale;
        }
        
        // Ensure current scale is always valid
        if (!std::isfinite(m_localMapScale) || m_localMapScale <= 0.0) {
            m_localMapScale = m_localMapBaseScale;
        }
    }
    updateVisibleTiles();
}

void PPIDisplayWidget::drawBackground(QPainter& painter) {
    // Fill with background color
    painter.fillRect(rect(), m_backgroundColor);
    
    // Draw circular display area mask
    QPointF center = screenCenter();
    double radius = ppiRadius();
    
    // Create gradient for radar glow effect
    if (m_displayMode == PPIDisplayMode::RadarOnly || 
        m_displayMode == PPIDisplayMode::NightVision) {
        QRadialGradient gradient(center, radius);
        gradient.setColorAt(0.0, m_backgroundColor.lighter(120));
        gradient.setColorAt(0.7, m_backgroundColor);
        gradient.setColorAt(1.0, m_backgroundColor.darker(120));
        painter.setBrush(gradient);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(center, radius, radius);
    }
    
    // Draw circular border
    painter.setPen(QPen(m_rangeRingColor.lighter(150), 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(center, radius, radius);
}

void PPIDisplayWidget::drawMapTiles(QPainter& painter) {
    painter.setOpacity(m_mapOpacity);

    if (!m_localMap.isNull()) {
        drawLocalMap(painter);
        painter.setOpacity(1.0);
        return;
    }

    if (m_mapTileUrlTemplate.isEmpty()) {
        painter.setOpacity(1.0);
        return;
    }

    // Calculate visible tile range
    QPointF center = screenCenter();
    double radius = ppiRadius();
    
    // Get corner positions
    double mPerPixel = m_rangeScaleM / radius;
    
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            GeoPosition tileCenter;
            tileCenter.latitude = m_center.latitude + (dy * 256 * mPerPixel / CoordinateUtils::DEG_TO_M_LAT);
            tileCenter.longitude = m_center.longitude + (dx * 256 * mPerPixel / CoordinateUtils::degToMeterLon(m_center.latitude));
            
            MapTileKey key = geoToTile(tileCenter, m_mapZoomLevel);
            
            QPixmap* tile = m_tileCache.object(key);
            if (tile) {
                // Calculate tile screen position
                double tileN = pow(2.0, m_mapZoomLevel);
                double tileLatRad = atan(sinh(M_PI * (1 - 2 * key.y / tileN)));
                double tileLat = qRadiansToDegrees(tileLatRad);
                double tileLon = key.x / tileN * 360.0 - 180.0;
                
                GeoPosition tilePos;
                tilePos.latitude = tileLat;
                tilePos.longitude = tileLon;
                tilePos.altitude = 0;
                
                QPointF screenPos = center + geoToPPI(tilePos);
                
                // Scale tile to match current view
                double tileSize = 256.0 / mPerPixel * (CoordinateUtils::DEG_TO_M_LAT / pow(2.0, m_mapZoomLevel) * 360.0 / 256.0);
                
                painter.drawPixmap(QRectF(screenPos.x(), screenPos.y(), tileSize, tileSize), *tile, tile->rect());
            } else if (!m_pendingTiles.contains(key)) {
                requestMapTile(key.x, key.y, m_mapZoomLevel);
            }
        }
    }
    
    painter.setOpacity(1.0);
}

void PPIDisplayWidget::drawLocalMap(QPainter& painter) {
    if (m_localMap.isNull()) {
        return;
    }

    // Guard against invalid image dimensions or scale
    if (m_localMap.width() <= 0 || m_localMap.height() <= 0 || 
        m_localMapScale <= 0.0 || !std::isfinite(m_localMapScale)) {
        return;
    }

    QPointF center = screenCenter();
    QPointF mapCenter = center + m_localMapOffset;
    
    // Calculate scaled dimensions
    double scaledWidth = m_localMap.width() * m_localMapScale;
    double scaledHeight = m_localMap.height() * m_localMapScale;
    
    // Guard against invalid scaled dimensions (too small, too large, or non-finite)
    if (!std::isfinite(scaledWidth) || !std::isfinite(scaledHeight) ||
        scaledWidth < 1.0 || scaledHeight < 1.0 ||
        scaledWidth > 100000.0 || scaledHeight > 100000.0) {
        return;
    }
    
    QSizeF scaledSize(scaledWidth, scaledHeight);
    QPointF topLeft = mapCenter - QPointF(scaledSize.width() / 2.0, scaledSize.height() / 2.0);
    
    // Guard against non-finite coordinates
    if (!std::isfinite(topLeft.x()) || !std::isfinite(topLeft.y())) {
        return;
    }

    painter.drawPixmap(QRectF(topLeft, scaledSize), m_localMap, m_localMap.rect());
}

void PPIDisplayWidget::drawRangeRings(QPainter& painter) {
    QPointF center = screenCenter();
    double radius = ppiRadius();
    double ringSpacing = radius / m_rangeRingCount;
    double rangePerRing = m_rangeScaleM / m_rangeRingCount;
    
    painter.setPen(QPen(m_rangeRingColor, 1, Qt::DashLine));
    
    QFont labelFont = painter.font();
    labelFont.setPointSize(9);
    painter.setFont(labelFont);
    
    for (int i = 1; i <= m_rangeRingCount; ++i) {
        double ringRadius = ringSpacing * i;
        painter.drawEllipse(center, ringRadius, ringRadius);
        
        if (m_showRangeLabels) {
            double rangeKm = (rangePerRing * i) / 1000.0;
            QString label;
            if (rangeKm >= 1.0) {
                label = QString("%1 km").arg(rangeKm, 0, 'f', 1);
            } else {
                label = QString("%1 m").arg(rangePerRing * i, 0, 'f', 0);
            }
            
            painter.setPen(m_rangeRingColor.lighter(150));
            painter.drawText(QPointF(center.x() + 5, center.y() - ringRadius + 12), label);
            painter.setPen(QPen(m_rangeRingColor, 1, Qt::DashLine));
        }
    }
}

void PPIDisplayWidget::drawAzimuthLines(QPainter& painter) {
    QPointF center = screenCenter();
    double radius = ppiRadius();
    double angleStep = 360.0 / m_azimuthDivisions;
    
    painter.setPen(QPen(m_azimuthLineColor, 1));
    
    QFont labelFont = painter.font();
    labelFont.setPointSize(9);
    painter.setFont(labelFont);
    
    double rotationOffset = m_northUp ? 0.0 : -m_heading;
    
    for (int i = 0; i < m_azimuthDivisions; ++i) {
        double angle = i * angleStep + rotationOffset;
        double angleRad = qDegreesToRadians(angle - 90.0);  // -90 to make 0 deg at top
        
        double x1 = center.x() + cos(angleRad) * 20;
        double y1 = center.y() + sin(angleRad) * 20;
        double x2 = center.x() + cos(angleRad) * radius;
        double y2 = center.y() + sin(angleRad) * radius;
        
        painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        
        if (m_showAzimuthLabels) {
            double labelAngle = i * angleStep;
            QString label = QString("%1°").arg(static_cast<int>(labelAngle));
            
            double labelX = center.x() + cos(angleRad) * (radius + 15);
            double labelY = center.y() + sin(angleRad) * (radius + 15);
            
            painter.setPen(m_rangeRingColor.lighter(150));
            QFontMetrics fm(labelFont);
            QRect textRect = fm.boundingRect(label);
            painter.drawText(QPointF(labelX - textRect.width() / 2, labelY + textRect.height() / 4), label);
            painter.setPen(QPen(m_azimuthLineColor, 1));
        }
    }
}

void PPIDisplayWidget::drawSweep(QPainter& painter) {
    QPointF center = screenCenter();
    double radius = ppiRadius();
    
    double rotationOffset = m_northUp ? 0.0 : -m_heading;
    double angleRad = qDegreesToRadians(m_sweepAngle + rotationOffset - 90.0);
    
    double x = center.x() + cos(angleRad) * radius;
    double y = center.y() + sin(angleRad) * radius;
    
    // Draw sweep line
    painter.setPen(QPen(m_sweepColor, 2));
    painter.drawLine(center, QPointF(x, y));
    
    // Draw bright tip
    painter.setPen(QPen(m_sweepColor.lighter(150), 4));
    painter.drawPoint(QPointF(x, y));
}

void PPIDisplayWidget::drawSweepTrail(QPainter& painter) {
    QPointF center = screenCenter();
    double radius = ppiRadius();
    double rotationOffset = m_northUp ? 0.0 : -m_heading;
    
    // Draw fade trail behind sweep
    for (int i = 1; i < SWEEP_TRAIL_LENGTH; ++i) {
        double trailAngle = m_sweepAngle - (i * 0.5);  // Trail behind sweep
        double angleRad = qDegreesToRadians(trailAngle + rotationOffset - 90.0);
        
        double intensity = 1.0 - (static_cast<double>(i) / SWEEP_TRAIL_LENGTH);
        QColor trailColor = m_sweepColor;
        trailColor.setAlphaF(intensity * 0.3);
        
        double x = center.x() + cos(angleRad) * radius;
        double y = center.y() + sin(angleRad) * radius;
        
        painter.setPen(QPen(trailColor, 1));
        painter.drawLine(center, QPointF(x, y));
    }
}

void PPIDisplayWidget::drawDefendedArea(QPainter& painter) {
    if (!m_showDefendedArea) return;
    
    QPointF center = screenCenter();
    double scale = ppiRadius() / m_rangeScaleM;
    
    // Critical zone (red)
    double criticalRadius = m_criticalRadiusM * scale;
    painter.setPen(QPen(QColor(255, 0, 0, 150), 2));
    painter.setBrush(QColor(255, 0, 0, 40));
    painter.drawEllipse(center, criticalRadius, criticalRadius);
    
    // Warning zone (yellow)
    double warningRadius = m_warningRadiusM * scale;
    painter.setPen(QPen(QColor(255, 200, 0, 120), 2, Qt::DashLine));
    painter.setBrush(QColor(255, 200, 0, 20));
    painter.drawEllipse(center, warningRadius, warningRadius);
    
    // Detection zone (outer boundary)
    double detectionRadius = qMin(m_detectionRadiusM * scale, ppiRadius() * 0.95);
    painter.setPen(QPen(QColor(100, 200, 255, 100), 1, Qt::DotLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(center, detectionRadius, detectionRadius);
}

void PPIDisplayWidget::drawTracks(QPainter& painter) {
    QPointF center = screenCenter();
    
    for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        Track* track = it.value();
        if (!track || track->state() == TrackState::Dropped) continue;
        if (!trackMatchesFilter(track)) continue;

        QPointF ppiPos = geoToPPI(track->position());
        QPointF screenPos = center + ppiPos;
        
        // Check if track is within display range
        double distance = QLineF(center, screenPos).length();
        if (distance > ppiRadius()) continue;
        
        bool selected = (it.key() == m_selectedTrackId);
        
        // Draw track history trail
        if (m_showTrackHistory) {
            drawTrackHistory(painter, track);
        }
        
        // Draw velocity vector
        drawVelocityVector(painter, track, screenPos);
        
        // Draw track symbol
        drawTrackSymbol(painter, track, screenPos, selected);
        
        // Draw label
        drawTrackLabel(painter, track, screenPos);
    }
}

void PPIDisplayWidget::drawTrackSymbol(QPainter& painter, Track* track, const QPointF& pos, bool selected) {
    QColor color = colorForClassification(track->classification());
    
    // Threat level affects intensity
    if (track->threatLevel() >= 4) {
        color = color.lighter(130);
    }
    
    // Check if this track is focused
    bool isFocused = (track->trackId() == m_focusedTrackId);
    
    int size = (selected || isFocused) ? 14 : 10;
    int penWidth = (selected || isFocused) ? 3 : 2;
    
    painter.setPen(QPen(color, penWidth));
    painter.setBrush(Qt::NoBrush);
    
    // Draw symbol based on classification
    switch (track->classification()) {
        case TrackClassification::Hostile:
            // Filled diamond for hostile
            {
                QPolygonF diamond;
                diamond << QPointF(pos.x(), pos.y() - size)
                       << QPointF(pos.x() + size, pos.y())
                       << QPointF(pos.x(), pos.y() + size)
                       << QPointF(pos.x() - size, pos.y());
                painter.setBrush(QColor(color.red(), color.green(), color.blue(), 100));
                painter.drawPolygon(diamond);
            }
            break;
            
        case TrackClassification::Friendly:
            // Circle for friendly
            painter.drawEllipse(pos, size, size);
            break;
            
        case TrackClassification::Pending:
            // Question mark shape (circle with ?)
            painter.drawEllipse(pos, size, size);
            painter.setPen(color);
            painter.drawText(QRectF(pos.x() - size, pos.y() - size, size * 2, size * 2),
                            Qt::AlignCenter, "?");
            break;
            
        default:
            // Square for unknown/neutral
            painter.drawRect(QRectF(pos.x() - size, pos.y() - size, size * 2, size * 2));
            break;
    }
    
    // Selection highlight
    if (selected) {
        painter.setPen(QPen(Qt::white, 1, Qt::DashLine));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(pos, size + 5, size + 5);
    }
    
    // Focus indicator (magnifier effect)
    if (isFocused) {
        painter.setPen(QPen(QColor(0, 200, 255), 2, Qt::DotLine));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(pos, size + 12, size + 12);
        
        // Draw small magnifier icon
        painter.setPen(QPen(QColor(0, 200, 255), 2));
        QPointF iconPos(pos.x() + size + 8, pos.y() - size - 8);
        painter.drawEllipse(iconPos, 6, 6);
        painter.drawLine(iconPos + QPointF(4, 4), iconPos + QPointF(8, 8));
    }
    
    // Engagement indicator
    if (track->isEngaged()) {
        painter.setPen(QPen(Qt::red, 2));
        painter.drawEllipse(pos, size + 8, size + 8);
    }
}

void PPIDisplayWidget::drawTrackHistory(QPainter& painter, Track* track) {
    QString trackId = track->trackId();
    if (!m_trackHistory.contains(trackId)) return;
    
    const QList<TrackHistoryPoint>& fullHistory = m_trackHistory[trackId];
    if (fullHistory.size() < 2) return;
    
    // Get per-track history points limit, or use full history if not set
    int maxPoints = m_trackHistoryPoints.value(trackId, -1);
    int startIdx = 0;
    if (maxPoints > 0 && fullHistory.size() > maxPoints) {
        startIdx = fullHistory.size() - maxPoints;
    }
    
    QColor color = colorForClassification(track->classification());
    QPointF center = screenCenter();
    
    // Highlight focused track with brighter history
    bool isFocused = (trackId == m_focusedTrackId);
    
    for (int i = qMax(1, startIdx); i < fullHistory.size(); ++i) {
        const TrackHistoryPoint& pt1 = fullHistory[i - 1];
        const TrackHistoryPoint& pt2 = fullHistory[i];
        
        QColor lineColor = color;
        double alpha = pt1.intensity * (isFocused ? 0.8 : 0.5);
        lineColor.setAlphaF(alpha);
        
        painter.setPen(QPen(lineColor, isFocused ? 2 : 1));
        painter.drawLine(center + pt1.position, center + pt2.position);
    }
    
    // Draw dots at history points
    int pointsDrawn = 0;
    for (int i = fullHistory.size() - 1; i >= startIdx && (maxPoints < 0 || pointsDrawn < maxPoints); --i) {
        const TrackHistoryPoint& pt = fullHistory[i];
        QColor dotColor = color;
        double alpha = pt.intensity * (isFocused ? 0.9 : 0.7);
        dotColor.setAlphaF(alpha);
        painter.setPen(Qt::NoPen);
        painter.setBrush(dotColor);
        painter.drawEllipse(center + pt.position, isFocused ? 3 : 2, isFocused ? 3 : 2);
        pointsDrawn++;
    }
}

void PPIDisplayWidget::drawTrackLabel(QPainter& painter, Track* track, const QPointF& pos) {
    QColor color = colorForClassification(track->classification());

    QString trackId = track->trackId();
    QString label = trackId;
    
    painter.setPen(color.lighter(120));
    QFont font = painter.font();
    font.setPointSize(8);
    font.setBold(track->trackId() == m_focusedTrackId);  // Bold if focused
    painter.setFont(font);
    
    painter.drawText(QPointF(pos.x() + 15, pos.y() + 5), label);
}

void PPIDisplayWidget::drawVelocityVector(QPainter& painter, Track* track, const QPointF& pos) {
    VelocityVector vel = track->velocity();
    double speed = vel.speed();
    
    if (speed < 1.0) return;
    
    double heading = vel.heading();
    double rotationOffset = m_northUp ? 0.0 : -m_heading;
    double angleRad = qDegreesToRadians(heading + rotationOffset - 90.0);
    
    // Scale velocity vector (max 30 pixels)
    double vectorLength = qMin(speed * 0.5, 30.0);
    
    double vx = cos(angleRad) * vectorLength;
    double vy = sin(angleRad) * vectorLength;
    
    QColor color = colorForClassification(track->classification());
    painter.setPen(QPen(color, 2));
    painter.drawLine(pos, QPointF(pos.x() + vx, pos.y() + vy));
    
    // Draw arrowhead
    double arrowSize = 6;
    double arrowAngle = M_PI / 6;
    
    double ax1 = pos.x() + vx - arrowSize * cos(angleRad - arrowAngle);
    double ay1 = pos.y() + vy - arrowSize * sin(angleRad - arrowAngle);
    double ax2 = pos.x() + vx - arrowSize * cos(angleRad + arrowAngle);
    double ay2 = pos.y() + vy - arrowSize * sin(angleRad + arrowAngle);
    
    QPolygonF arrow;
    arrow << QPointF(pos.x() + vx, pos.y() + vy)
          << QPointF(ax1, ay1)
          << QPointF(ax2, ay2);
    painter.setBrush(color);
    painter.drawPolygon(arrow);
}

void PPIDisplayWidget::drawNorthIndicator(QPainter& painter) {
    double rotationOffset = m_northUp ? 0.0 : -m_heading;
    double angleRad = qDegreesToRadians(rotationOffset - 90.0);  // North at top
    
    QPointF center = screenCenter();
    double indicatorRadius = ppiRadius() + 25;
    
    double nx = center.x() + cos(angleRad) * indicatorRadius;
    double ny = center.y() + sin(angleRad) * indicatorRadius;
    
    // Draw N indicator
    painter.setPen(QPen(Qt::white, 2));
    painter.setBrush(Qt::NoBrush);
    
    QFont font = painter.font();
    font.setPointSize(14);
    font.setBold(true);
    painter.setFont(font);
    
    painter.drawText(QPointF(nx - 6, ny + 5), "N");
    
    // Draw small triangle pointing north
    QPolygonF arrow;
    arrow << QPointF(nx, ny + 10)
          << QPointF(nx - 5, ny + 18)
          << QPointF(nx + 5, ny + 18);
    painter.setBrush(Qt::white);
    painter.drawPolygon(arrow);
}

void PPIDisplayWidget::drawCompassRose(QPainter& painter) {
    // Draw small compass rose in corner
    QPointF roseCenter(width() - 50, height() - 50);
    double roseRadius = 30;
    
    double rotationOffset = m_northUp ? 0.0 : -m_heading;
    
    painter.setPen(QPen(Qt::white, 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(roseCenter, roseRadius, roseRadius);
    
    // Cardinal directions
    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);
    
    QString dirs[] = {"N", "E", "S", "W"};
    for (int i = 0; i < 4; ++i) {
        double angle = i * 90.0 + rotationOffset;
        double angleRad = qDegreesToRadians(angle - 90.0);
        
        double x = roseCenter.x() + cos(angleRad) * (roseRadius - 10);
        double y = roseCenter.y() + sin(angleRad) * (roseRadius - 10);
        
        painter.drawText(QPointF(x - 4, y + 4), dirs[i]);
        
        // Draw tick marks
        double tx1 = roseCenter.x() + cos(angleRad) * (roseRadius - 5);
        double ty1 = roseCenter.y() + sin(angleRad) * (roseRadius - 5);
        double tx2 = roseCenter.x() + cos(angleRad) * roseRadius;
        double ty2 = roseCenter.y() + sin(angleRad) * roseRadius;
        painter.drawLine(QPointF(tx1, ty1), QPointF(tx2, ty2));
    }
    
    // Draw heading if not north-up
    if (!m_northUp) {
        painter.setPen(Qt::yellow);
        painter.drawText(QPointF(roseCenter.x() - 15, roseCenter.y() + roseRadius + 15),
                        QString("HDG: %1°").arg(static_cast<int>(m_heading)));
    }
}

void PPIDisplayWidget::drawScaleInfo(QPainter& painter) {
    // Draw info panel in bottom-left corner
    int padding = 10;
    int lineHeight = 16;
    
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPointSize(9);
    painter.setFont(font);
    
    QString rangeStr;
    if (m_rangeScaleM >= 1000) {
        rangeStr = QString("Range: %1 km").arg(m_rangeScaleM / 1000.0, 0, 'f', 1);
    } else {
        rangeStr = QString("Range: %1 m").arg(m_rangeScaleM, 0, 'f', 0);
    }
    
    QString posStr = QString("Lat: %1  Lon: %2")
                         .arg(m_center.latitude, 0, 'f', 4)
                         .arg(m_center.longitude, 0, 'f', 4);
    
    QString modeStr;
    switch (m_displayMode) {
        case PPIDisplayMode::RadarOnly: modeStr = "Mode: Radar"; break;
        case PPIDisplayMode::MapOverlay: modeStr = "Mode: Map+Radar"; break;
        case PPIDisplayMode::MapOnly: modeStr = "Mode: Map"; break;
        case PPIDisplayMode::NightVision: modeStr = "Mode: Night Vision"; break;
    }
    
    QString sweepStr = QString("Sweep: %1°").arg(static_cast<int>(m_sweepAngle));
    
    int trackCount = 0;
    for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        if (it.value() && it.value()->state() != TrackState::Dropped) {
            ++trackCount;
        }
    }
    QString trackStr = QString("Tracks: %1").arg(trackCount);
    
    // Background for readability
    QRect infoBg(padding, height() - padding - lineHeight * 5, 180, lineHeight * 5);
    painter.fillRect(infoBg, QColor(0, 0, 0, 150));
    
    int y = height() - padding - lineHeight * 4;
    painter.drawText(padding + 5, y, rangeStr);
    painter.drawText(padding + 5, y + lineHeight, posStr);
    painter.drawText(padding + 5, y + lineHeight * 2, modeStr);
    painter.drawText(padding + 5, y + lineHeight * 3, sweepStr);
    painter.drawText(padding + 5, y + lineHeight * 4, trackStr);
}

bool PPIDisplayWidget::trackMatchesFilter(Track* track) const {
    if (m_trackDisplayFilter == TrackDisplayFilter::AllTracks) return true;

    bool hasRadar    = track->hasSource(DetectionSource::Radar);
    bool hasCamera   = track->hasSource(DetectionSource::Camera);
    bool hasRF       = track->hasSource(DetectionSource::RFDetector);
    bool hasCombined = track->hasSource(DetectionSource::Combined);

    switch (m_trackDisplayFilter) {
        case TrackDisplayFilter::RadarOnly:
            // Exclusively radar — no camera, no RF, and not sensor-fused
            return hasRadar && !hasCamera && !hasRF && !hasCombined;
        case TrackDisplayFilter::VideoOnly:
            // Exclusively camera/video — no radar, no RF, and not sensor-fused
            return hasCamera && !hasRadar && !hasRF && !hasCombined;
        case TrackDisplayFilter::RFOnly:
            // Exclusively RF — no radar, no camera, and not sensor-fused
            return hasRF && !hasRadar && !hasCamera && !hasCombined;
        case TrackDisplayFilter::FusedOnly:
            // Sensor-fused: explicitly marked Combined or carries multiple primary sources
            return hasCombined || ((hasRadar + hasCamera + hasRF) > 1);
        default:
            return true;
    }
}

void PPIDisplayWidget::drawFilterIndicator(QPainter& painter) {
    if (m_trackDisplayFilter == TrackDisplayFilter::AllTracks) return;

    QString filterLabel;
    QColor  filterColor;
    switch (m_trackDisplayFilter) {
        case TrackDisplayFilter::RadarOnly:
            filterLabel = "FILTER: RADAR ONLY";
            filterColor = QColor(0, 200, 255);   // cyan-blue
            break;
        case TrackDisplayFilter::VideoOnly:
            filterLabel = "FILTER: VIDEO ONLY";
            filterColor = QColor(255, 165, 0);   // orange
            break;
        case TrackDisplayFilter::RFOnly:
            filterLabel = "FILTER: RF ONLY";
            filterColor = QColor(180, 0, 255);   // purple
            break;
        case TrackDisplayFilter::FusedOnly:
            filterLabel = "FILTER: FUSED TRACKS";
            filterColor = QColor(0, 230, 100);   // green
            break;
        default:
            return;
    }

    QFont font = painter.font();
    font.setPointSize(9);
    font.setBold(true);
    painter.setFont(font);

    QFontMetrics fm(font);
    int textW = fm.horizontalAdvance(filterLabel);
    int textH = fm.height();
    int padding = 6;
    int x = (width() - textW) / 2 - padding;
    int y = 10;

    // Badge background
    QRect badge(x, y, textW + padding * 2, textH + padding);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 180));
    painter.drawRoundedRect(badge, 4, 4);

    // Coloured left accent bar
    painter.setBrush(filterColor);
    painter.drawRoundedRect(QRect(x, y, 4, badge.height()), 2, 2);

    // Label text
    painter.setPen(filterColor);
    painter.drawText(badge.adjusted(padding + 2, 0, 0, 0), Qt::AlignVCenter, filterLabel);
}

void PPIDisplayWidget::requestMapTile(int x, int y, int zoom) {
    MapTileKey key{x, y, zoom};
    if (m_pendingTiles.contains(key)) return;
    
    m_pendingTiles.insert(key);
    
    QString url = getTileUrl(x, y, zoom);
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::User, QVariant::fromValue(key));
    request.setHeader(QNetworkRequest::UserAgentHeader, "CounterUAS-C2/1.0");
    
    m_networkManager->get(request);
}

QString PPIDisplayWidget::getTileUrl(int x, int y, int zoom) const {
    QString url = m_mapTileUrlTemplate;
    url.replace("{x}", QString::number(x));
    url.replace("{y}", QString::number(y));
    url.replace("{z}", QString::number(zoom));
    return url;
}

MapTileKey PPIDisplayWidget::geoToTile(const GeoPosition& pos, int zoom) const {
    double n = pow(2.0, zoom);
    double latRad = qDegreesToRadians(pos.latitude);
    
    int x = static_cast<int>((pos.longitude + 180.0) / 360.0 * n);
    int y = static_cast<int>((1.0 - asinh(tan(latRad)) / M_PI) / 2.0 * n);
    
    return {x, y, zoom};
}

void PPIDisplayWidget::onMapTileReceived(QNetworkReply* reply) {
    reply->deleteLater();
    
    QVariant keyVar = reply->request().attribute(QNetworkRequest::User);
    MapTileKey key = keyVar.value<MapTileKey>();
    m_pendingTiles.remove(key);
    
    if (reply->error() != QNetworkReply::NoError) {
        return;
    }
    
    QByteArray data = reply->readAll();
    QPixmap* tile = new QPixmap();
    if (tile->loadFromData(data)) {
        m_tileCache.insert(key, tile);
        update();
    } else {
        delete tile;
    }
}

void PPIDisplayWidget::updateVisibleTiles() {
    if (m_displayMode != PPIDisplayMode::MapOverlay && 
        m_displayMode != PPIDisplayMode::MapOnly) {
        return;
    }

    if (!m_localMap.isNull()) {
        return;
    }
    
    // Pre-fetch visible tiles
    for (int dx = -2; dx <= 2; ++dx) {
        for (int dy = -2; dy <= 2; ++dy) {
            MapTileKey key = geoToTile(m_center, m_mapZoomLevel);
            key.x += dx;
            key.y += dy;
            
            if (!m_tileCache.contains(key) && !m_pendingTiles.contains(key)) {
                requestMapTile(key.x, key.y, key.zoom);
            }
        }
    }
}

void PPIDisplayWidget::updateLocalMapBaseScale() {
    if (m_localMap.isNull()) {
        return;
    }

    // Guard against division by zero with invalid image dimensions
    int mapWidth = m_localMap.width();
    int mapHeight = m_localMap.height();
    if (mapWidth <= 0 || mapHeight <= 0) {
        m_localMapBaseScale = 1.0;
        return;
    }

    double radius = ppiRadius();
    // Additional guard: ensure radius is valid
    if (!std::isfinite(radius) || radius <= 0.0) {
        m_localMapBaseScale = 1.0;
        return;
    }
    
    double diameter = qMax(1.0, radius * 2.0);
    double scaleX = diameter / static_cast<double>(mapWidth);
    double scaleY = diameter / static_cast<double>(mapHeight);
    
    // Ensure scale values are finite before using them
    if (!std::isfinite(scaleX) || !std::isfinite(scaleY)) {
        m_localMapBaseScale = 1.0;
        return;
    }
    
    m_localMapBaseScale = qBound(0.02, qMin(scaleX, scaleY), 20.0);
    
    // Final validation
    if (!std::isfinite(m_localMapBaseScale) || m_localMapBaseScale <= 0.0) {
        m_localMapBaseScale = 1.0;
    }
}

QPointF PPIDisplayWidget::screenCenter() const {
    return QPointF(width() / 2.0, height() / 2.0);
}

double PPIDisplayWidget::ppiRadius() const {
    // Leave margin for labels, but ensure a minimum positive radius
    double radius = qMin(width(), height()) / 2.0 - 40;
    return qMax(1.0, radius);  // Ensure minimum radius of 1 to prevent division by zero
}

QPointF PPIDisplayWidget::geoToPPI(const GeoPosition& pos) const {
    // Calculate distance and bearing from center
    double distance = CoordinateUtils::haversineDistance(m_center, pos);
    double bearing = CoordinateUtils::bearing(m_center, pos);
    
    // Convert to PPI coordinates (polar to cartesian)
    double scale = ppiRadius() / m_rangeScaleM;
    double ppiRange = distance * scale;
    
    double rotationOffset = m_northUp ? 0.0 : -m_heading;
    double angleRad = qDegreesToRadians(bearing + rotationOffset - 90.0);  // -90 for top=north
    
    double x = ppiRange * cos(angleRad);
    double y = ppiRange * sin(angleRad);
    
    return QPointF(x, y);
}

GeoPosition PPIDisplayWidget::ppiToGeo(const QPointF& ppiPos) const {
    double ppiRange = sqrt(ppiPos.x() * ppiPos.x() + ppiPos.y() * ppiPos.y());
    double angleRad = atan2(ppiPos.y(), ppiPos.x());
    
    double rotationOffset = m_northUp ? 0.0 : -m_heading;
    double bearing = qRadiansToDegrees(angleRad) + 90.0 - rotationOffset;  // +90 to convert back
    
    double scale = ppiRadius() / m_rangeScaleM;
    double distance = ppiRange / scale;
    
    return CoordinateUtils::positionFromBearingDistance(m_center, bearing, distance);
}

QPointF PPIDisplayWidget::polarToScreen(double rangeM, double azimuthDeg) const {
    double scale = ppiRadius() / m_rangeScaleM;
    double ppiRange = rangeM * scale;
    
    double rotationOffset = m_northUp ? 0.0 : -m_heading;
    double angleRad = qDegreesToRadians(azimuthDeg + rotationOffset - 90.0);
    
    QPointF center = screenCenter();
    double x = center.x() + ppiRange * cos(angleRad);
    double y = center.y() + ppiRange * sin(angleRad);
    
    return QPointF(x, y);
}

QColor PPIDisplayWidget::colorForClassification(TrackClassification cls) const {
    switch (cls) {
        case TrackClassification::Hostile: return m_hostileColor;
        case TrackClassification::Friendly: return m_friendlyColor;
        case TrackClassification::Pending: return m_unknownColor;
        case TrackClassification::Neutral: return m_neutralColor;
        default: return m_unknownColor;
    }
}

QColor PPIDisplayWidget::colorForThreatLevel(int level) const {
    switch (level) {
        case 5: return Qt::red;
        case 4: return QColor(255, 128, 0);  // Orange
        case 3: return Qt::yellow;
        case 2: return QColor(144, 238, 144);  // Light green
        default: return Qt::green;
    }
}

QString PPIDisplayWidget::findTrackAtPoint(const QPointF& point) const {
    QPointF center = screenCenter();
    
    for (auto it = m_tracks.begin(); it != m_tracks.end(); ++it) {
        Track* track = it.value();
        if (!track || track->state() == TrackState::Dropped) continue;
        
        QPointF ppiPos = geoToPPI(track->position());
        QPointF screenPos = center + ppiPos;
        
        double distance = QLineF(point, screenPos).length();
        if (distance < 15) {  // 15 pixel hit radius
            return it.key();
        }
    }
    
    return QString();
}

QString PPIDisplayWidget::buildTrackTooltip(Track* track) const {
    if (!track) return QString();
    
    QString tooltip;
    tooltip += QString("<b>Track %1</b><br>").arg(track->trackId());
    tooltip += QString("<hr>");
    
    // Classification
    tooltip += QString("<b>Classification:</b> %1<br>").arg(track->classificationString());
    
    // Threat level
    tooltip += QString("<b>Threat Level:</b> %1/5<br>").arg(track->threatLevel());
    
    // State
    tooltip += QString("<b>State:</b> %1<br>").arg(track->stateString());
    
    // Position
    GeoPosition pos = track->position();
    tooltip += QString("<b>Position:</b><br>");
    tooltip += QString("  Lat: %1°<br>").arg(pos.latitude, 0, 'f', 5);
    tooltip += QString("  Lon: %1°<br>").arg(pos.longitude, 0, 'f', 5);
    tooltip += QString("  Alt: %1 m<br>").arg(pos.altitude, 0, 'f', 1);
    
    // Velocity
    VelocityVector vel = track->velocity();
    double speed = vel.speed();
    double heading = vel.heading();
    if (speed > 0.5) {
        tooltip += QString("<b>Velocity:</b><br>");
        tooltip += QString("  Speed: %1 m/s<br>").arg(speed, 0, 'f', 1);
        tooltip += QString("  Heading: %1°<br>").arg(heading, 0, 'f', 1);
        double climbRate = vel.climbRate();
        if (qAbs(climbRate) > 0.5) {
            tooltip += QString("  Climb: %1 m/s<br>").arg(climbRate, 0, 'f', 1);
        }
    }
    
    // Distance from center
    double distance = CoordinateUtils::haversineDistance(m_center, pos);
    double bearing = CoordinateUtils::bearing(m_center, pos);
    tooltip += QString("<b>Range:</b> %1 m<br>").arg(distance, 0, 'f', 0);
    tooltip += QString("<b>Bearing:</b> %1°<br>").arg(bearing, 0, 'f', 1);
    
    // Engaged status
    if (track->isEngaged()) {
        tooltip += QString("<b style='color:red;'>ENGAGED</b><br>");
    }
    
    // Track age
    qint64 ageMs = track->trackAge();
    int ageSec = ageMs / 1000;
    tooltip += QString("<b>Track Age:</b> %1s").arg(ageSec);
    
    return tooltip;
}

void PPIDisplayWidget::showTrackContextMenu(const QPoint& globalPos, const QString& trackId) {
    if (trackId.isEmpty() || !m_tracks.contains(trackId)) return;
    
    Track* track = m_tracks[trackId];
    if (!track) return;
    
    QMenu contextMenu(this);
    contextMenu.setStyleSheet(
        "QMenu { background-color: #2d2d2d; color: white; border: 1px solid #555; }"
        "QMenu::item { padding: 5px 20px; }"
        "QMenu::item:selected { background-color: #4a4a4a; }"
        "QMenu::separator { height: 1px; background: #555; margin: 3px 0; }"
    );
    
    // Track info header (non-clickable)
    QAction* headerAction = contextMenu.addAction(QString("Track %1").arg(trackId));
    headerAction->setEnabled(false);
    QFont headerFont = headerAction->font();
    headerFont.setBold(true);
    headerAction->setFont(headerFont);
    
    contextMenu.addSeparator();
    
    // Engage submenu with effector selection
    QMenu* engageMenu = contextMenu.addMenu("Engage");
    engageMenu->setIcon(QIcon(":/icons/engage.svg"));
    
    QString selectedEffectorId;  // Will store the selected effector ID
    
    if (track->isEngaged()) {
        QAction* engagedAction = engageMenu->addAction("Already Engaged");
        engagedAction->setEnabled(false);
    } else if (m_engagementManager) {
        // Get available effectors and add them to submenu
        QList<EffectorInterface*> effectors = m_engagementManager->effectors();
        
        if (effectors.isEmpty()) {
            QAction* noEffAction = engageMenu->addAction("No effectors available");
            noEffAction->setEnabled(false);
        } else {
            // Get recommended effector for this track
            EffectorInterface* recommended = m_engagementManager->recommendedEffector(trackId);
            
            for (EffectorInterface* eff : effectors) {
                QString statusStr;
                bool canEngage = false;
                
                switch (eff->status()) {
                    case EffectorStatus::Ready:
                        statusStr = "Ready";
                        canEngage = true;
                        break;
                    case EffectorStatus::Engaged:
                        statusStr = "Engaged";
                        break;
                    case EffectorStatus::Offline:
                        statusStr = "Offline";
                        break;
                    case EffectorStatus::Initializing:
                        statusStr = "Initializing";
                        break;
                    case EffectorStatus::Cooldown:
                        statusStr = "Cooldown";
                        break;
                    case EffectorStatus::Reloading:
                        statusStr = "Reloading";
                        break;
                    case EffectorStatus::Fault:
                        statusStr = "Fault";
                        break;
                    default:
                        statusStr = "Unknown";
                        break;
                }
                
                QString actionText = QString("%1 [%2] - %3")
                    .arg(eff->displayName())
                    .arg(eff->effectorType())
                    .arg(statusStr);
                
                // Mark recommended effector
                if (recommended && eff == recommended) {
                    actionText += " *";
                }
                
                QAction* effAction = engageMenu->addAction(actionText);
                effAction->setData(eff->effectorId());
                effAction->setEnabled(canEngage);
                
                // Set color based on status
                if (canEngage) {
                    effAction->setIcon(QIcon(":/icons/engage.svg"));
                }
            }
        }
    } else {
        QAction* noMgrAction = engageMenu->addAction("Engagement not available");
        noMgrAction->setEnabled(false);
    }
    
    // Focus action (magnifier)
    QAction* focusAction = contextMenu.addAction("Focus");
    focusAction->setIcon(QIcon(":/icons/zoom.svg"));
    if (m_focusedTrackId == trackId) {
        focusAction->setText("Unfocus");
    }
    
    contextMenu.addSeparator();
    
    // History points submenu
    QMenu* historyMenu = contextMenu.addMenu("Set History Points");
    createHistoryPointsSubMenu(historyMenu, trackId);
    
    contextMenu.addSeparator();
    
    // Delete action
    QAction* deleteAction = contextMenu.addAction("Delete Track");
    deleteAction->setIcon(QIcon(":/icons/delete.svg"));
    
    // Execute menu
    QAction* selectedAction = contextMenu.exec(globalPos);
    
    // Check if an effector was selected from the engage submenu
    if (selectedAction && selectedAction->parent() == engageMenu && !track->isEngaged()) {
        QString effectorId = selectedAction->data().toString();
        if (!effectorId.isEmpty()) {
            emit engageTrackWithEffector(trackId, effectorId);
        }
    } else if (selectedAction == focusAction) {
        if (m_focusedTrackId == trackId) {
            clearFocus();
        } else {
            focusTrack(trackId);
        }
    } else if (selectedAction == deleteAction) {
        emit deleteTrackRequested(trackId);
    }
}

void PPIDisplayWidget::createHistoryPointsSubMenu(QMenu* menu, const QString& trackId) {
    if (!menu) return;
    
    int currentPoints = m_trackHistoryPoints.value(trackId, -1);
    
    // Add "Default" option
    QAction* defaultAction = menu->addAction("Default");
    defaultAction->setCheckable(true);
    defaultAction->setChecked(currentPoints == -1);
    connect(defaultAction, &QAction::triggered, this, [this, trackId]() {
        m_trackHistoryPoints.remove(trackId);
        emit trackHistoryPointsChanged(trackId, -1);
        update();
    });
    
    menu->addSeparator();
    
    // Add fixed point options
    QList<int> pointOptions = {5, 10, 15, 20, 25, 30, 50};
    for (int points : pointOptions) {
        QAction* action = menu->addAction(QString("%1 points").arg(points));
        action->setCheckable(true);
        action->setChecked(currentPoints == points);
        connect(action, &QAction::triggered, this, [this, trackId, points]() {
            setTrackHistoryPoints(trackId, points);
        });
    }
}

void PPIDisplayWidget::contextMenuEvent(QContextMenuEvent* event) {
    QString trackId = findTrackAtPoint(event->pos());
    
    if (!trackId.isEmpty()) {
        showTrackContextMenu(event->globalPos(), trackId);
        event->accept();
    } else {
        // Let parent handle right-click for panning (don't show context menu for empty space)
        event->ignore();
    }
}

bool PPIDisplayWidget::event(QEvent* event) {
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
        QString trackId = findTrackAtPoint(helpEvent->pos());
        
        if (!trackId.isEmpty() && m_tracks.contains(trackId)) {
            Track* track = m_tracks[trackId];
            if (track) {
                QString tooltip = buildTrackTooltip(track);
                QToolTip::showText(helpEvent->globalPos(), tooltip, this);
            }
        } else {
            QToolTip::hideText();
        }
        return true;
    }
    return QWidget::event(event);
}

} // namespace CounterUAS
