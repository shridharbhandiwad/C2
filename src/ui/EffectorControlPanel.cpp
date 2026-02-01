#include "ui/EffectorControlPanel.h"
#include "ui/ThemeManager.h"
#include "core/EngagementManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFrame>

namespace CounterUAS {

EffectorControlPanel::EffectorControlPanel(EngagementManager* manager, QWidget* parent)
    : QWidget(parent)
    , m_manager(manager)
    , m_updateTimer(new QTimer(this))
{
    setupUI();
    
    connect(m_updateTimer, &QTimer::timeout, this, &EffectorControlPanel::updateEffectorStatus);
    m_updateTimer->start(500);  // Update every 500ms
    
    // Initial population
    refreshEffectorList();
}

void EffectorControlPanel::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(12);
    
    // Effector list with modern styling
    QGroupBox* listGroup = new QGroupBox("Available Effectors", this);
    listGroup->setStyleSheet(ThemeManager::groupBoxStyle());
    QVBoxLayout* listLayout = new QVBoxLayout(listGroup);
    listLayout->setContentsMargins(8, 16, 8, 8);
    
    m_effectorList = new QListWidget(this);
    m_effectorList->setMinimumHeight(150);
    m_effectorList->setStyleSheet(ThemeManager::listWidgetStyle());
    connect(m_effectorList, &QListWidget::itemClicked, 
            this, &EffectorControlPanel::onEffectorItemClicked);
    listLayout->addWidget(m_effectorList);
    
    layout->addWidget(listGroup);
    
    // Status display with modern styling
    QGroupBox* statusGroup = new QGroupBox("Selected Effector", this);
    statusGroup->setStyleSheet(ThemeManager::groupBoxStyle());
    QVBoxLayout* statusLayout = new QVBoxLayout(statusGroup);
    statusLayout->setContentsMargins(12, 20, 12, 12);
    statusLayout->setSpacing(10);
    
    m_selectedEffectorLabel = new QLabel("None selected", this);
    m_selectedEffectorLabel->setStyleSheet(
        "font-weight: bold;"
        "font-size: 13px;"
        "color: #e6edf3;"
    );
    statusLayout->addWidget(m_selectedEffectorLabel);
    
    m_statusLabel = new QLabel("Status: -", this);
    m_statusLabel->setStyleSheet("color: #8b949e;");
    statusLayout->addWidget(m_statusLabel);
    
    // Readiness bar
    QHBoxLayout* readinessLayout = new QHBoxLayout();
    QLabel* readinessLabel = new QLabel("Readiness:", this);
    readinessLabel->setStyleSheet("color: #8b949e;");
    readinessLayout->addWidget(readinessLabel);
    
    m_readinessBar = new QProgressBar(this);
    m_readinessBar->setRange(0, 100);
    m_readinessBar->setValue(0);
    m_readinessBar->setStyleSheet(ThemeManager::progressBarStyle());
    m_readinessBar->setTextVisible(true);
    m_readinessBar->setFormat("%p%");
    readinessLayout->addWidget(m_readinessBar);
    statusLayout->addLayout(readinessLayout);
    
    m_roundsLabel = new QLabel("Rounds: N/A", this);
    m_roundsLabel->setStyleSheet(
        "color: #8b949e;"
        "font-family: 'Consolas', monospace;"
    );
    statusLayout->addWidget(m_roundsLabel);
    
    layout->addWidget(statusGroup);
    
    // Control buttons with modern styling
    QGroupBox* controlGroup = new QGroupBox("Engagement Control", this);
    controlGroup->setStyleSheet(ThemeManager::groupBoxStyle());
    QVBoxLayout* controlLayout = new QVBoxLayout(controlGroup);
    controlLayout->setContentsMargins(12, 20, 12, 12);
    controlLayout->setSpacing(10);
    
    m_engageBtn = new QPushButton("ENGAGE TARGET", this);
    m_engageBtn->setStyleSheet(ThemeManager::engageButtonStyle());
    m_engageBtn->setMinimumHeight(50);
    m_engageBtn->setEnabled(false);
    m_engageBtn->setCursor(Qt::PointingHandCursor);
    connect(m_engageBtn, &QPushButton::clicked, this, &EffectorControlPanel::onEngageClicked);
    controlLayout->addWidget(m_engageBtn);
    
    m_disengageBtn = new QPushButton("DISENGAGE", this);
    m_disengageBtn->setStyleSheet(
        "QPushButton {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #cc6600, stop:1 #994d00);"
        "   border: 1px solid #ff8c00;"
        "   border-radius: 6px;"
        "   color: white;"
        "   font-weight: bold;"
        "   padding: 8px 16px;"
        "}"
        "QPushButton:hover:enabled {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #ff8c00, stop:1 #cc6600);"
        "}"
        "QPushButton:disabled {"
        "   background-color: #21262d;"
        "   border-color: #30363d;"
        "   color: #484f58;"
        "}"
    );
    m_disengageBtn->setMinimumHeight(38);
    m_disengageBtn->setEnabled(false);
    m_disengageBtn->setCursor(Qt::PointingHandCursor);
    connect(m_disengageBtn, &QPushButton::clicked, this, &EffectorControlPanel::onDisengageClicked);
    controlLayout->addWidget(m_disengageBtn);
    
    layout->addWidget(controlGroup);
    
    layout->addStretch();
}

void EffectorControlPanel::refreshEffectorList() {
    m_effectorList->clear();
    
    if (!m_manager) return;
    
    for (auto* effector : m_manager->effectors()) {
        QListWidgetItem* item = new QListWidgetItem(m_effectorList);
        item->setData(Qt::UserRole, effector->effectorId());
        updateEffectorItem(item, effector);
        m_effectorList->addItem(item);
    }
}

void EffectorControlPanel::updateEffectorItem(QListWidgetItem* item, EffectorInterface* effector) {
    if (!item || !effector) return;
    
    QString text = QString("%1 [%2]\n%3")
        .arg(effector->displayName())
        .arg(effector->effectorType())
        .arg(statusToString(effector->status()));
    
    item->setText(text);
    item->setForeground(statusToColor(effector->status()));
    
    // Add icon based on type
    if (effector->effectorType() == "RF_JAMMER") {
        item->setIcon(QIcon());  // Would set jammer icon
    } else if (effector->effectorType() == "KINETIC") {
        item->setIcon(QIcon());  // Would set missile icon
    } else if (effector->effectorType() == "DIRECTED_ENERGY") {
        item->setIcon(QIcon());  // Would set laser icon
    }
}

void EffectorControlPanel::onEffectorItemClicked(QListWidgetItem* item) {
    if (!item || !m_manager) return;
    
    m_selectedEffectorId = item->data(Qt::UserRole).toString();
    
    auto* effector = m_manager->effector(m_selectedEffectorId);
    if (effector) {
        m_selectedEffectorLabel->setText(QString("%1 (%2)")
            .arg(effector->displayName())
            .arg(effector->effectorType()));
        
        m_manager->selectEffector(m_selectedEffectorId);
        emit effectorSelected(m_selectedEffectorId);
        
        updateEffectorStatus();
    }
}

void EffectorControlPanel::onEngageClicked() {
    if (!m_manager) return;
    
    QString trackId = m_manager->selectedTrackId();
    if (trackId.isEmpty()) {
        QMessageBox::warning(this, "Engage", "No track selected for engagement.");
        return;
    }
    
    if (m_selectedEffectorId.isEmpty()) {
        QMessageBox::warning(this, "Engage", "No effector selected.");
        return;
    }
    
    // Request authorization (this starts the engagement workflow)
    m_manager->requestAuthorization();
    
    emit engageRequested(trackId);
}

void EffectorControlPanel::onDisengageClicked() {
    if (!m_manager) return;
    
    if (!m_selectedEffectorId.isEmpty()) {
        auto* effector = m_manager->effector(m_selectedEffectorId);
        if (effector && effector->isEngaged()) {
            effector->disengage();
        }
    }
}

void EffectorControlPanel::updateEffectorStatus() {
    if (!m_manager) return;
    
    // Update list items
    for (int i = 0; i < m_effectorList->count(); i++) {
        QListWidgetItem* item = m_effectorList->item(i);
        QString effectorId = item->data(Qt::UserRole).toString();
        auto* effector = m_manager->effector(effectorId);
        if (effector) {
            updateEffectorItem(item, effector);
        }
    }
    
    // Update selected effector detail
    if (!m_selectedEffectorId.isEmpty()) {
        auto* effector = m_manager->effector(m_selectedEffectorId);
        if (effector) {
            m_statusLabel->setText(QString("Status: %1").arg(statusToString(effector->status())));
            m_statusLabel->setStyleSheet(QString("color: %1;").arg(statusToColor(effector->status()).name()));
            
            int readiness = static_cast<int>(effector->health().readiness * 100);
            m_readinessBar->setValue(readiness);
            
            if (effector->health().remainingShots >= 0) {
                m_roundsLabel->setText(QString("Rounds: %1").arg(effector->health().remainingShots));
            } else {
                m_roundsLabel->setText("Rounds: Unlimited");
            }
            
            // Enable/disable buttons based on state
            bool canEngage = effector->isReady() && !m_manager->selectedTrackId().isEmpty();
            bool canDisengage = effector->isEngaged();
            
            m_engageBtn->setEnabled(canEngage);
            m_disengageBtn->setEnabled(canDisengage);
        }
    } else {
        m_engageBtn->setEnabled(false);
        m_disengageBtn->setEnabled(false);
    }
}

QColor EffectorControlPanel::statusToColor(EffectorStatus status) {
    switch (status) {
        case EffectorStatus::Ready: return QColor(0, 200, 0);
        case EffectorStatus::Engaged: return QColor(255, 165, 0);
        case EffectorStatus::Offline: return QColor(128, 128, 128);
        case EffectorStatus::Initializing:
        case EffectorStatus::Reloading:
        case EffectorStatus::Cooldown: return QColor(255, 255, 0);
        case EffectorStatus::Fault: return QColor(255, 0, 0);
        case EffectorStatus::Maintenance: return QColor(100, 100, 255);
        default: return QColor(255, 255, 255);
    }
}

QString EffectorControlPanel::statusToString(EffectorStatus status) {
    switch (status) {
        case EffectorStatus::Unknown: return "Unknown";
        case EffectorStatus::Offline: return "Offline";
        case EffectorStatus::Initializing: return "Initializing...";
        case EffectorStatus::Ready: return "READY";
        case EffectorStatus::Engaged: return "ENGAGED";
        case EffectorStatus::Reloading: return "Reloading...";
        case EffectorStatus::Cooldown: return "Cooldown";
        case EffectorStatus::Maintenance: return "Maintenance";
        case EffectorStatus::Fault: return "FAULT";
        default: return "Unknown";
    }
}

} // namespace CounterUAS
