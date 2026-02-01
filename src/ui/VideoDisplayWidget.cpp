#include "ui/VideoDisplayWidget.h"
#include "video/VideoStreamManager.h"
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QLinearGradient>

namespace CounterUAS {

VideoDisplayWidget::VideoDisplayWidget(QWidget* parent)
    : QWidget(parent)
    , m_updateTimer(new QTimer(this))
{
    setMinimumSize(320, 240);
    setStyleSheet(
        "VideoDisplayWidget {"
        "   background-color: #000000;"
        "   border: 2px solid #30363d;"
        "   border-radius: 6px;"
        "}"
    );
    
    m_updateTimer->setInterval(33);  // ~30 fps
    connect(m_updateTimer, &QTimer::timeout, this, [this]() {
        update();
    });
}

void VideoDisplayWidget::setVideoManager(VideoStreamManager* manager) {
    m_videoManager = manager;
}

void VideoDisplayWidget::setSource(const QString& sourceId) {
    m_sourceId = sourceId;
    m_updateTimer->start();
}

void VideoDisplayWidget::updateFrame(const QImage& frame) {
    m_currentFrame = frame;
    update();
}

void VideoDisplayWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    // Draw rounded background
    QPainterPath path;
    path.addRoundedRect(rect(), 6, 6);
    painter.setClipPath(path);
    
    if (!m_currentFrame.isNull()) {
        QImage scaled = m_currentFrame.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int x = (width() - scaled.width()) / 2;
        int y = (height() - scaled.height()) / 2;
        
        // Fill background
        painter.fillRect(rect(), QColor("#000000"));
        painter.drawImage(x, y, scaled);
    } else {
        // No signal display
        painter.fillRect(rect(), QColor("#0d1117"));
        
        // Draw "No Signal" text with modern styling
        painter.setPen(QColor("#484f58"));
        QFont font = painter.font();
        font.setPixelSize(14);
        font.setWeight(QFont::Medium);
        painter.setFont(font);
        
        QString displayText = m_sourceId.isEmpty() ? "NO VIDEO SOURCE" : m_sourceId;
        painter.drawText(rect(), Qt::AlignCenter, displayText);
        
        // Draw subtle grid pattern
        painter.setPen(QPen(QColor("#21262d"), 1));
        int gridSize = 30;
        for (int x = 0; x < width(); x += gridSize) {
            painter.drawLine(x, 0, x, height());
        }
        for (int y = 0; y < height(); y += gridSize) {
            painter.drawLine(0, y, width(), y);
        }
    }
    
    // Draw overlay
    if (m_overlayEnabled) {
        // Semi-transparent top bar
        QLinearGradient topGradient(0, 0, 0, 30);
        topGradient.setColorAt(0, QColor(0, 0, 0, 180));
        topGradient.setColorAt(1, QColor(0, 0, 0, 0));
        painter.fillRect(0, 0, width(), 30, topGradient);
        
        // Source ID
        painter.setPen(QColor("#00a8e8"));
        QFont overlayFont = painter.font();
        overlayFont.setPixelSize(11);
        overlayFont.setWeight(QFont::Bold);
        painter.setFont(overlayFont);
        painter.drawText(10, 18, m_sourceId);
        
        // Semi-transparent bottom bar
        QLinearGradient bottomGradient(0, height() - 25, 0, height());
        bottomGradient.setColorAt(0, QColor(0, 0, 0, 0));
        bottomGradient.setColorAt(1, QColor(0, 0, 0, 180));
        painter.fillRect(0, height() - 25, width(), 25, bottomGradient);
        
        // Timestamp
        painter.setPen(QColor("#e6edf3"));
        overlayFont.setWeight(QFont::Normal);
        overlayFont.setFamily("Consolas");
        painter.setFont(overlayFont);
        painter.drawText(10, height() - 8, QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
        
        // Recording indicator (if recording)
        // Draw a red dot if recording
        // painter.setBrush(QColor("#dc3545"));
        // painter.setPen(Qt::NoPen);
        // painter.drawEllipse(width() - 20, 10, 10, 10);
    }
}

void VideoDisplayWidget::mouseDoubleClickEvent(QMouseEvent* event) {
    Q_UNUSED(event)
    emit doubleClicked();
}

void VideoDisplayWidget::mousePressEvent(QMouseEvent* event) {
    Q_UNUSED(event)
    emit clicked();
}

} // namespace CounterUAS
