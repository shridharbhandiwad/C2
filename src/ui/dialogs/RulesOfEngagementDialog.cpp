/**
 * @file RulesOfEngagementDialog.cpp
 * @brief Implementation of rules of engagement dialog
 */

#include "ui/dialogs/RulesOfEngagementDialog.h"
#include "core/EngagementManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>

namespace CounterUAS {

RulesOfEngagementDialog::RulesOfEngagementDialog(EngagementManager* manager, QWidget* parent)
    : QDialog(parent)
    , m_manager(manager)
{
    setWindowTitle("Rules of Engagement");
    setMinimumSize(500, 650);
    
    // Apply modern dialog styling
    setStyleSheet(
        "QDialog {"
        "   background-color: #0d1117;"
        "}"
        "QGroupBox {"
        "   background-color: #161b22;"
        "   border: 1px solid #30363d;"
        "   border-radius: 8px;"
        "   margin-top: 16px;"
        "   padding: 16px 12px 12px 12px;"
        "   font-weight: 600;"
        "   color: #e6edf3;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   subcontrol-position: top left;"
        "   left: 16px;"
        "   padding: 4px 12px;"
        "   background-color: #1e3a5f;"
        "   border-radius: 4px;"
        "   color: #ffffff;"
        "}"
        "QLabel {"
        "   color: #e6edf3;"
        "}"
        "QSpinBox, QDoubleSpinBox {"
        "   background-color: #0d1117;"
        "   border: 1px solid #30363d;"
        "   border-radius: 6px;"
        "   padding: 6px 8px;"
        "   color: #e6edf3;"
        "   min-height: 24px;"
        "}"
        "QSpinBox:focus, QDoubleSpinBox:focus {"
        "   border-color: #00a8e8;"
        "}"
        "QCheckBox {"
        "   color: #e6edf3;"
        "   spacing: 8px;"
        "}"
        "QCheckBox::indicator {"
        "   width: 18px;"
        "   height: 18px;"
        "   border: 2px solid #30363d;"
        "   border-radius: 4px;"
        "   background-color: #0d1117;"
        "}"
        "QCheckBox::indicator:checked {"
        "   background-color: #00a8e8;"
        "   border-color: #00a8e8;"
        "}"
        "QCheckBox::indicator:hover {"
        "   border-color: #8b949e;"
        "}"
        "QListWidget {"
        "   background-color: #0d1117;"
        "   border: 1px solid #30363d;"
        "   border-radius: 6px;"
        "   padding: 4px;"
        "   color: #e6edf3;"
        "}"
        "QListWidget::item {"
        "   padding: 8px 12px;"
        "   border-radius: 4px;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #21262d;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #1e3a5f;"
        "   color: #ffffff;"
        "}"
        "QPushButton {"
        "   background-color: #21262d;"
        "   border: 1px solid #30363d;"
        "   border-radius: 6px;"
        "   padding: 8px 16px;"
        "   color: #e6edf3;"
        "   font-weight: 500;"
        "}"
        "QPushButton:hover {"
        "   background-color: #30363d;"
        "   border-color: #8b949e;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1e3a5f;"
        "}"
    );
    
    setupUI();
}

void RulesOfEngagementDialog::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Authorization settings
    QGroupBox* authGroup = new QGroupBox("Authorization", this);
    QFormLayout* authLayout = new QFormLayout(authGroup);
    
    m_requireAuth = new QCheckBox("Require operator authorization", this);
    m_requireAuth->setChecked(true);
    authLayout->addRow(m_requireAuth);
    
    m_authTimeout = new QSpinBox(this);
    m_authTimeout->setRange(10, 300);
    m_authTimeout->setValue(60);
    m_authTimeout->setSuffix(" seconds");
    authLayout->addRow("Authorization timeout:", m_authTimeout);
    
    m_minThreatLevel = new QSpinBox(this);
    m_minThreatLevel->setRange(1, 5);
    m_minThreatLevel->setValue(3);
    authLayout->addRow("Minimum threat level:", m_minThreatLevel);
    
    m_autoEngageHigh = new QCheckBox("Auto-engage high threat (level 5)", this);
    m_autoEngageHigh->setChecked(false);
    authLayout->addRow(m_autoEngageHigh);
    
    m_autoSelectEffector = new QCheckBox("Auto-select best effector", this);
    m_autoSelectEffector->setChecked(true);
    authLayout->addRow(m_autoSelectEffector);
    
    mainLayout->addWidget(authGroup);
    
    // Engagement parameters
    QGroupBox* engageGroup = new QGroupBox("Engagement Parameters", this);
    QFormLayout* engageLayout = new QFormLayout(engageGroup);
    
    m_minDistance = new QDoubleSpinBox(this);
    m_minDistance->setRange(0, 1000);
    m_minDistance->setValue(100);
    m_minDistance->setSuffix(" m");
    engageLayout->addRow("Minimum engage distance:", m_minDistance);
    
    m_maxDistance = new QDoubleSpinBox(this);
    m_maxDistance->setRange(100, 10000);
    m_maxDistance->setValue(2000);
    m_maxDistance->setSuffix(" m");
    engageLayout->addRow("Maximum engage distance:", m_maxDistance);
    
    m_requireBDA = new QCheckBox("Require Battle Damage Assessment", this);
    m_requireBDA->setChecked(true);
    engageLayout->addRow(m_requireBDA);
    
    m_allowMultiple = new QCheckBox("Allow simultaneous engagements", this);
    m_allowMultiple->setChecked(false);
    engageLayout->addRow(m_allowMultiple);
    
    mainLayout->addWidget(engageGroup);
    
    // Authorized effectors
    QGroupBox* effectorGroup = new QGroupBox("Authorized Effector Types", this);
    QVBoxLayout* effectorLayout = new QVBoxLayout(effectorGroup);
    
    m_authRFJammer = new QCheckBox("RF Jammer", this);
    m_authRFJammer->setChecked(true);
    effectorLayout->addWidget(m_authRFJammer);
    
    m_authKinetic = new QCheckBox("Kinetic Interceptor", this);
    m_authKinetic->setChecked(true);
    effectorLayout->addWidget(m_authKinetic);
    
    m_authDE = new QCheckBox("Directed Energy", this);
    m_authDE->setChecked(true);
    effectorLayout->addWidget(m_authDE);
    
    mainLayout->addWidget(effectorGroup);
    
    // Restricted zones
    QGroupBox* zoneGroup = new QGroupBox("Restricted Engagement Zones", this);
    QVBoxLayout* zoneLayout = new QVBoxLayout(zoneGroup);
    
    m_restrictedZonesList = new QListWidget(this);
    zoneLayout->addWidget(m_restrictedZonesList);
    
    QHBoxLayout* zoneBtnLayout = new QHBoxLayout();
    QPushButton* addZoneBtn = new QPushButton("Add Zone", this);
    connect(addZoneBtn, &QPushButton::clicked, this, &RulesOfEngagementDialog::onAddRestrictedZone);
    QPushButton* removeZoneBtn = new QPushButton("Remove Zone", this);
    connect(removeZoneBtn, &QPushButton::clicked, this, &RulesOfEngagementDialog::onRemoveRestrictedZone);
    zoneBtnLayout->addWidget(addZoneBtn);
    zoneBtnLayout->addWidget(removeZoneBtn);
    zoneBtnLayout->addStretch();
    zoneLayout->addLayout(zoneBtnLayout);
    
    mainLayout->addWidget(zoneGroup);
    
    // Dialog buttons
    QHBoxLayout* btnLayout = new QHBoxLayout();
    QPushButton* applyBtn = new QPushButton("Apply", this);
    connect(applyBtn, &QPushButton::clicked, this, &RulesOfEngagementDialog::onApply);
    QPushButton* okBtn = new QPushButton("OK", this);
    connect(okBtn, &QPushButton::clicked, this, [this]() {
        onApply();
        accept();
    });
    QPushButton* cancelBtn = new QPushButton("Cancel", this);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    
    btnLayout->addStretch();
    btnLayout->addWidget(applyBtn);
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
    mainLayout->addLayout(btnLayout);
}

ROESettings RulesOfEngagementDialog::getSettings() const {
    ROESettings settings;
    settings.requireOperatorAuthorization = m_requireAuth->isChecked();
    settings.authorizationTimeoutSeconds = m_authTimeout->value();
    settings.minimumThreatLevel = m_minThreatLevel->value();
    settings.autoEngageHighThreat = m_autoEngageHigh->isChecked();
    settings.autoSelectEffector = m_autoSelectEffector->isChecked();
    settings.minimumEngageDistance = m_minDistance->value();
    settings.maximumEngageDistance = m_maxDistance->value();
    settings.requireBDA = m_requireBDA->isChecked();
    settings.allowMultipleEngagements = m_allowMultiple->isChecked();
    
    settings.authorizedEffectorTypes.clear();
    if (m_authRFJammer->isChecked()) settings.authorizedEffectorTypes << "RF_JAMMER";
    if (m_authKinetic->isChecked()) settings.authorizedEffectorTypes << "KINETIC";
    if (m_authDE->isChecked()) settings.authorizedEffectorTypes << "DIRECTED_ENERGY";
    
    for (int i = 0; i < m_restrictedZonesList->count(); i++) {
        settings.restrictedZones << m_restrictedZonesList->item(i)->text();
    }
    
    return settings;
}

void RulesOfEngagementDialog::setSettings(const ROESettings& settings) {
    m_requireAuth->setChecked(settings.requireOperatorAuthorization);
    m_authTimeout->setValue(settings.authorizationTimeoutSeconds);
    m_minThreatLevel->setValue(settings.minimumThreatLevel);
    m_autoEngageHigh->setChecked(settings.autoEngageHighThreat);
    m_autoSelectEffector->setChecked(settings.autoSelectEffector);
    m_minDistance->setValue(settings.minimumEngageDistance);
    m_maxDistance->setValue(settings.maximumEngageDistance);
    m_requireBDA->setChecked(settings.requireBDA);
    m_allowMultiple->setChecked(settings.allowMultipleEngagements);
    
    m_authRFJammer->setChecked(settings.authorizedEffectorTypes.contains("RF_JAMMER"));
    m_authKinetic->setChecked(settings.authorizedEffectorTypes.contains("KINETIC"));
    m_authDE->setChecked(settings.authorizedEffectorTypes.contains("DIRECTED_ENERGY"));
    
    m_restrictedZonesList->clear();
    for (const QString& zone : settings.restrictedZones) {
        m_restrictedZonesList->addItem(zone);
    }
}

void RulesOfEngagementDialog::onApply() {
    ROESettings settings = getSettings();
    
    if (m_manager) {
        m_manager->setAuthorizationTimeout(settings.authorizationTimeoutSeconds);
        m_manager->setAutoRecommendEffector(settings.autoSelectEffector);
    }
    
    emit settingsChanged(settings);
    QMessageBox::information(this, "ROE Applied", "Rules of engagement have been updated.");
}

void RulesOfEngagementDialog::onAddRestrictedZone() {
    QString zone = QInputDialog::getText(this, "Add Restricted Zone",
        "Enter zone name or coordinates:");
    if (!zone.isEmpty()) {
        m_restrictedZonesList->addItem(zone);
    }
}

void RulesOfEngagementDialog::onRemoveRestrictedZone() {
    QListWidgetItem* item = m_restrictedZonesList->currentItem();
    if (item) {
        delete item;
    }
}

} // namespace CounterUAS
