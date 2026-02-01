#include "ui/VideoGridWidget.h"
#include <QLabel>

namespace CounterUAS {

VideoGridWidget::VideoGridWidget(QWidget* parent) : QWidget(parent) {
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(4);
    m_layout->setContentsMargins(2, 2, 2, 2);
    
    // Create simplified 2-camera layout (Day and Night)
    setupDayNightLayout();
}

void VideoGridWidget::setupDayNightLayout() {
    // Clear existing layout
    for (auto* w : m_widgets) {
        m_layout->removeWidget(w);
        delete w;
    }
    m_widgets.clear();
    m_cameraWidgetMap.clear();
    
    // Delete old labels if they exist
    if (m_dayLabel) { delete m_dayLabel; m_dayLabel = nullptr; }
    if (m_nightLabel) { delete m_nightLabel; m_nightLabel = nullptr; }
    
    m_rows = 1;
    m_cols = 2;
    
    // Modern camera container style
    QString containerStyle = 
        "background-color: #0d1117;"
        "border: 1px solid #30363d;"
        "border-radius: 6px;";
    
    QString containerHoverStyle = 
        "background-color: #0d1117;"
        "border: 2px solid #1e3a5f;"
        "border-radius: 6px;";
    
    // Create Day Camera container (left side)
    QWidget* dayContainer = new QWidget(this);
    dayContainer->setObjectName("dayContainer");
    dayContainer->setStyleSheet(QString("#dayContainer { %1 }").arg(containerStyle));
    QVBoxLayout* dayLayout = new QVBoxLayout(dayContainer);
    dayLayout->setContentsMargins(4, 4, 4, 4);
    dayLayout->setSpacing(4);
    
    // Day camera header
    QWidget* dayHeader = new QWidget(dayContainer);
    QHBoxLayout* dayHeaderLayout = new QHBoxLayout(dayHeader);
    dayHeaderLayout->setContentsMargins(8, 4, 8, 4);
    
    QLabel* dayIcon = new QLabel(dayHeader);
    dayIcon->setPixmap(QIcon(":/icons/camera.svg").pixmap(12, 12));
    dayHeaderLayout->addWidget(dayIcon);
    
    m_dayLabel = new QLabel("DAY CAMERA", dayHeader);
    m_dayLabel->setStyleSheet(
        "color: #00a8e8;"
        "font-weight: bold;"
        "font-size: 10px;"
        "letter-spacing: 1px;"
    );
    dayHeaderLayout->addWidget(m_dayLabel);
    dayHeaderLayout->addStretch();
    
    dayHeader->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "   stop:0 #1e3a5f, stop:1 #0d2040);"
        "border-radius: 4px;"
    );
    dayLayout->addWidget(dayHeader);
    
    m_dayWidget = new VideoDisplayWidget(dayContainer);
    m_dayWidget->setMinimumSize(240, 160);
    m_dayWidget->setSource("SIM-DAY-001");
    m_dayWidget->setStyleSheet(
        "background-color: #000000;"
        "border-radius: 4px;"
    );
    m_dayWidget->setCursor(Qt::PointingHandCursor);
    connect(m_dayWidget, &VideoDisplayWidget::clicked, this, [this]() {
        emit cameraSelected(m_dayWidget->currentSource());
    });
    dayLayout->addWidget(m_dayWidget, 1);
    
    // Create Night Camera container (right side)
    QWidget* nightContainer = new QWidget(this);
    nightContainer->setObjectName("nightContainer");
    nightContainer->setStyleSheet(QString("#nightContainer { %1 }").arg(containerStyle));
    QVBoxLayout* nightLayout = new QVBoxLayout(nightContainer);
    nightLayout->setContentsMargins(4, 4, 4, 4);
    nightLayout->setSpacing(4);
    
    // Night camera header
    QWidget* nightHeader = new QWidget(nightContainer);
    QHBoxLayout* nightHeaderLayout = new QHBoxLayout(nightHeader);
    nightHeaderLayout->setContentsMargins(8, 4, 8, 4);
    
    QLabel* nightIcon = new QLabel(nightHeader);
    nightIcon->setPixmap(QIcon(":/icons/camera.svg").pixmap(12, 12));
    nightHeaderLayout->addWidget(nightIcon);
    
    m_nightLabel = new QLabel("NIGHT CAMERA", nightHeader);
    m_nightLabel->setStyleSheet(
        "color: #a855f7;"
        "font-weight: bold;"
        "font-size: 10px;"
        "letter-spacing: 1px;"
    );
    nightHeaderLayout->addWidget(m_nightLabel);
    nightHeaderLayout->addStretch();
    
    nightHeader->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "   stop:0 #581c87, stop:1 #3b0764);"
        "border-radius: 4px;"
    );
    nightLayout->addWidget(nightHeader);
    
    m_nightWidget = new VideoDisplayWidget(nightContainer);
    m_nightWidget->setMinimumSize(240, 160);
    m_nightWidget->setSource("SIM-NIGHT-001");
    m_nightWidget->setStyleSheet(
        "background-color: #000000;"
        "border-radius: 4px;"
    );
    m_nightWidget->setCursor(Qt::PointingHandCursor);
    connect(m_nightWidget, &VideoDisplayWidget::clicked, this, [this]() {
        emit cameraSelected(m_nightWidget->currentSource());
    });
    nightLayout->addWidget(m_nightWidget, 1);
    
    // Add containers to main grid
    m_layout->addWidget(dayContainer, 0, 0);
    m_layout->addWidget(nightContainer, 0, 1);
    m_layout->setColumnStretch(0, 1);
    m_layout->setColumnStretch(1, 1);
    
    // Add to widget list for tracking
    m_widgets.append(m_dayWidget);
    m_widgets.append(m_nightWidget);
    
    // Pre-register the camera mappings
    m_cameraWidgetMap["SIM-DAY-001"] = m_dayWidget;
    m_cameraWidgetMap["SIM-NIGHT-001"] = m_nightWidget;
}

void VideoGridWidget::setGridSize(int rows, int cols) {
    m_rows = rows;
    m_cols = cols;
    
    // Clear existing
    for (auto* w : m_widgets) {
        m_layout->removeWidget(w);
        delete w;
    }
    m_widgets.clear();
    m_cameraWidgetMap.clear();
    
    // Create new grid
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            VideoDisplayWidget* widget = new VideoDisplayWidget(this);
            widget->setMinimumSize(160, 120);
            connect(widget, &VideoDisplayWidget::clicked, this, [this, widget]() {
                emit cameraSelected(widget->currentSource());
            });
            m_layout->addWidget(widget, r, c);
            m_widgets.append(widget);
        }
    }
}

void VideoGridWidget::addCamera(const QString& cameraId) {
    // Check if camera already assigned
    if (m_cameraWidgetMap.contains(cameraId)) {
        return;
    }
    
    // Find first available widget
    for (auto* w : m_widgets) {
        if (w->currentSource().isEmpty()) {
            w->setSource(cameraId);
            m_cameraWidgetMap[cameraId] = w;
            return;
        }
    }
}

void VideoGridWidget::removeCamera(const QString& cameraId) {
    if (m_cameraWidgetMap.contains(cameraId)) {
        VideoDisplayWidget* w = m_cameraWidgetMap.take(cameraId);
        if (w) {
            w->setSource(QString());
        }
    }
}

void VideoGridWidget::clearAllCameras() {
    m_cameraWidgetMap.clear();
    for (auto* w : m_widgets) {
        w->setSource(QString());
    }
}

VideoDisplayWidget* VideoGridWidget::widgetForCamera(const QString& cameraId) const {
    return m_cameraWidgetMap.value(cameraId, nullptr);
}

QStringList VideoGridWidget::cameraIds() const {
    return m_cameraWidgetMap.keys();
}

void VideoGridWidget::updateFrame(const QString& cameraId, const QImage& frame) {
    // If camera is not yet assigned, try to add it
    if (!m_cameraWidgetMap.contains(cameraId)) {
        // Find first available widget
        for (auto* w : m_widgets) {
            if (w->currentSource().isEmpty()) {
                w->setSource(cameraId);
                m_cameraWidgetMap[cameraId] = w;
                break;
            }
        }
    }
    
    // Update the frame
    VideoDisplayWidget* widget = m_cameraWidgetMap.value(cameraId, nullptr);
    if (widget) {
        widget->updateFrame(frame);
    }
}

} // namespace CounterUAS
