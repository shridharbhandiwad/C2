#include "ui/AlertQueue.h"
#include "core/ThreatAssessor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>

namespace CounterUAS {

AlertQueue::AlertQueue(ThreatAssessor* assessor, QWidget* parent)
    : QWidget(parent), m_assessor(assessor) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);
    
    // Header with icon
    QWidget* headerWidget = new QWidget(this);
    QHBoxLayout* headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel* alertIcon = new QLabel(headerWidget);
    alertIcon->setPixmap(QIcon(":/icons/alert.svg").pixmap(16, 16));
    headerLayout->addWidget(alertIcon);
    
    QLabel* titleLabel = new QLabel("THREAT ALERTS", headerWidget);
    titleLabel->setStyleSheet(
        "color: #dc3545;"
        "font-weight: bold;"
        "font-size: 11px;"
        "letter-spacing: 1px;"
    );
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    
    QWidget* headerContainer = new QWidget(this);
    headerContainer->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "   stop:0 #21262d, stop:1 #161b22);"
        "border: 1px solid #30363d;"
        "border-radius: 4px;"
    );
    QVBoxLayout* headerContainerLayout = new QVBoxLayout(headerContainer);
    headerContainerLayout->setContentsMargins(10, 6, 10, 6);
    headerContainerLayout->addWidget(headerWidget);
    
    layout->addWidget(headerContainer);
    
    m_listWidget = new QListWidget(this);
    m_listWidget->setStyleSheet(
        "QListWidget {"
        "   background-color: #0d1117;"
        "   border: 1px solid #30363d;"
        "   border-radius: 6px;"
        "   padding: 4px;"
        "   outline: none;"
        "}"
        "QListWidget::item {"
        "   background-color: transparent;"
        "   border-radius: 4px;"
        "   padding: 10px 12px;"
        "   margin: 2px 0;"
        "   color: #e6edf3;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #21262d;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #1e3a5f;"
        "   color: #ffffff;"
        "}"
    );
    layout->addWidget(m_listWidget);
    
    if (m_assessor) {
        connect(m_assessor, &ThreatAssessor::newAlert, this, &AlertQueue::onNewAlert);
    }
    
    connect(m_listWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        emit alertClicked(item->data(Qt::UserRole).toString());
    });
}

void AlertQueue::onNewAlert(const ThreatAlert& alert) {
    QString timeStr = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString displayText = QString("[%1] %2").arg(timeStr, alert.message);
    
    QListWidgetItem* item = new QListWidgetItem(displayText);
    item->setData(Qt::UserRole, alert.alertId);
    
    // Apply styled background based on threat level
    if (alert.threatLevel >= 4) {
        // Critical alert - red gradient
        item->setBackground(QBrush(QColor(139, 26, 26)));  // Dark red
        item->setForeground(QColor(255, 200, 200));
        item->setToolTip("CRITICAL THREAT - Immediate action required");
    } else if (alert.threatLevel >= 3) {
        // High alert - orange gradient
        item->setBackground(QBrush(QColor(153, 77, 0)));  // Dark orange
        item->setForeground(QColor(255, 220, 180));
        item->setToolTip("HIGH THREAT - Monitor closely");
    } else if (alert.threatLevel >= 2) {
        // Medium alert - yellow tint
        item->setBackground(QBrush(QColor(100, 100, 30)));  // Dark yellow
        item->setForeground(QColor(255, 255, 200));
        item->setToolTip("MEDIUM THREAT - Tracking");
    } else {
        // Low alert - blue tint
        item->setBackground(QBrush(QColor(30, 58, 95)));  // Dark blue
        item->setForeground(QColor(200, 220, 255));
        item->setToolTip("LOW THREAT - Monitoring");
    }
    
    m_listWidget->insertItem(0, item);
    
    // Keep only the last 50 alerts
    while (m_listWidget->count() > 50) {
        delete m_listWidget->takeItem(m_listWidget->count() - 1);
    }
}

} // namespace CounterUAS
