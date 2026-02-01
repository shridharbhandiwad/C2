#include "ui/TrackDetailPanel.h"
#include "ui/ThemeManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QFrame>

namespace CounterUAS {

TrackDetailPanel::TrackDetailPanel(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setSpacing(12);
    
    // Header
    QLabel* headerLabel = new QLabel("TRACK DETAILS", this);
    headerLabel->setStyleSheet(
        "QLabel {"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "       stop:0 #21262d, stop:1 #161b22);"
        "   border: 1px solid #30363d;"
        "   border-radius: 4px;"
        "   padding: 8px 12px;"
        "   font-weight: bold;"
        "   font-size: 11px;"
        "   letter-spacing: 1px;"
        "   color: #00a8e8;"
        "}"
    );
    headerLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(headerLabel);
    
    // Form container with styled background
    QWidget* formContainer = new QWidget(this);
    formContainer->setStyleSheet(
        "QWidget {"
        "   background-color: #161b22;"
        "   border: 1px solid #30363d;"
        "   border-radius: 6px;"
        "}"
    );
    
    QVBoxLayout* formContainerLayout = new QVBoxLayout(formContainer);
    formContainerLayout->setContentsMargins(12, 12, 12, 12);
    
    QFormLayout* formLayout = new QFormLayout();
    formLayout->setSpacing(10);
    formLayout->setLabelAlignment(Qt::AlignRight);
    
    // Styled labels
    QString labelStyle = "color: #8b949e; font-weight: 500;";
    QString valueStyle = "color: #e6edf3; font-weight: 500; font-family: 'Consolas', monospace;";
    
    m_idLabel = new QLabel("-");
    m_idLabel->setStyleSheet(valueStyle);
    QLabel* idLabelTitle = new QLabel("Track ID:");
    idLabelTitle->setStyleSheet(labelStyle);
    formLayout->addRow(idLabelTitle, m_idLabel);
    
    m_classLabel = new QLabel("-");
    m_classLabel->setStyleSheet(valueStyle);
    QLabel* classLabelTitle = new QLabel("Classification:");
    classLabelTitle->setStyleSheet(labelStyle);
    formLayout->addRow(classLabelTitle, m_classLabel);
    
    m_posLabel = new QLabel("-");
    m_posLabel->setStyleSheet(valueStyle);
    m_posLabel->setWordWrap(true);
    QLabel* posLabelTitle = new QLabel("Position:");
    posLabelTitle->setStyleSheet(labelStyle);
    formLayout->addRow(posLabelTitle, m_posLabel);
    
    m_velLabel = new QLabel("-");
    m_velLabel->setStyleSheet(valueStyle);
    QLabel* velLabelTitle = new QLabel("Velocity:");
    velLabelTitle->setStyleSheet(labelStyle);
    formLayout->addRow(velLabelTitle, m_velLabel);
    
    m_threatLabel = new QLabel("-");
    m_threatLabel->setStyleSheet(valueStyle);
    QLabel* threatLabelTitle = new QLabel("Threat Level:");
    threatLabelTitle->setStyleSheet(labelStyle);
    formLayout->addRow(threatLabelTitle, m_threatLabel);
    
    m_stateLabel = new QLabel("-");
    m_stateLabel->setStyleSheet(valueStyle);
    QLabel* stateLabelTitle = new QLabel("State:");
    stateLabelTitle->setStyleSheet(labelStyle);
    formLayout->addRow(stateLabelTitle, m_stateLabel);
    
    formContainerLayout->addLayout(formLayout);
    mainLayout->addWidget(formContainer);
    
    // Separator
    QFrame* separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setStyleSheet("background-color: #30363d;");
    separator->setFixedHeight(1);
    mainLayout->addWidget(separator);
    
    // Action buttons
    QLabel* actionsLabel = new QLabel("ACTIONS", this);
    actionsLabel->setStyleSheet(
        "color: #8b949e;"
        "font-weight: bold;"
        "font-size: 10px;"
        "letter-spacing: 1px;"
    );
    mainLayout->addWidget(actionsLabel);
    
    QPushButton* engageBtn = new QPushButton("ENGAGE TARGET");
    engageBtn->setStyleSheet(ThemeManager::engageButtonStyle());
    engageBtn->setMinimumHeight(45);
    engageBtn->setCursor(Qt::PointingHandCursor);
    
    QPushButton* slewBtn = new QPushButton("Slew Camera");
    slewBtn->setStyleSheet(ThemeManager::buttonStyle("primary"));
    slewBtn->setMinimumHeight(36);
    slewBtn->setCursor(Qt::PointingHandCursor);
    
    connect(engageBtn, &QPushButton::clicked, this, [this]() {
        if (m_track) emit engageRequested(m_track->trackId());
    });
    connect(slewBtn, &QPushButton::clicked, this, [this]() {
        if (m_track) emit slewCameraRequested(m_track->trackId());
    });
    
    mainLayout->addWidget(engageBtn);
    mainLayout->addWidget(slewBtn);
    mainLayout->addStretch();
}

void TrackDetailPanel::setTrack(Track* track) {
    m_track = track;
    updateDisplay();
    
    if (track) {
        connect(track, &Track::updated, this, &TrackDetailPanel::updateDisplay);
    }
}

void TrackDetailPanel::clear() {
    m_track = nullptr;
    m_idLabel->setText("-");
    m_classLabel->setText("-");
    m_posLabel->setText("-");
    m_velLabel->setText("-");
    m_threatLabel->setText("-");
    m_stateLabel->setText("-");
}

void TrackDetailPanel::updateDisplay() {
    if (!m_track) return;
    
    m_idLabel->setText(m_track->trackId());
    m_classLabel->setText(m_track->classificationString());
    
    GeoPosition pos = m_track->position();
    m_posLabel->setText(QString("%1, %2, %3m")
                           .arg(pos.latitude, 0, 'f', 5)
                           .arg(pos.longitude, 0, 'f', 5)
                           .arg(pos.altitude, 0, 'f', 1));
    
    VelocityVector vel = m_track->velocity();
    m_velLabel->setText(QString("%1 m/s @ %2°")
                           .arg(vel.speed(), 0, 'f', 1)
                           .arg(vel.heading(), 0, 'f', 0));
    
    m_threatLabel->setText(QString::number(m_track->threatLevel()));
    m_stateLabel->setText(m_track->stateString());
}

} // namespace CounterUAS
