/**
 * @file ThemeManager.cpp
 * @brief Implementation of centralized theme management
 */

#include "ui/ThemeManager.h"
#include <QApplication>
#include <QScreen>
#include <QFile>
#include <QTextStream>
#include <QFontDatabase>
#include <QStyleFactory>

namespace CounterUAS {

ThemeManager& ThemeManager::instance() {
    static ThemeManager instance;
    return instance;
}

ThemeManager::ThemeManager(QObject* parent)
    : QObject(parent)
    , m_scaleFactor(1.0)
    , m_app(nullptr)
{
    initializeColors();
    initializeFonts();
}

void ThemeManager::initialize(QApplication* app) {
    m_app = app;
    
    // Enable HiDPI scaling
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    
    // Detect scale factor from primary screen
    detectScaleFactor();
    
    // Set Fusion style as base (works best with custom themes)
    app->setStyle(QStyleFactory::create("Fusion"));
    
    // Apply dark theme
    applyDarkTheme();
}

void ThemeManager::initializeColors() {
    // Primary colors
    m_colors.primary = QColor("#1e3a5f");
    m_colors.primaryDark = QColor("#0d2040");
    m_colors.primaryLight = QColor("#2a4a6f");
    m_colors.accent = QColor("#00a8e8");
    
    // Background colors
    m_colors.background = QColor("#0d1117");
    m_colors.surface = QColor("#161b22");
    m_colors.surfaceAlt = QColor("#21262d");
    
    // Border colors
    m_colors.border = QColor("#30363d");
    m_colors.borderLight = QColor("#484f58");
    m_colors.borderHover = QColor("#8b949e");
    
    // Text colors
    m_colors.text = QColor("#e6edf3");
    m_colors.textSecondary = QColor("#8b949e");
    m_colors.textDisabled = QColor("#484f58");
    
    // Status colors
    m_colors.success = QColor("#28a745");
    m_colors.warning = QColor("#ffa500");
    m_colors.danger = QColor("#dc3545");
    m_colors.info = QColor("#00a8e8");
    
    // Threat level colors (1-5, minimal to critical)
    m_colors.threatMinimal = QColor("#6c757d");
    m_colors.threatLow = QColor("#ffc107");
    m_colors.threatMedium = QColor("#fd7e14");
    m_colors.threatHigh = QColor("#dc3545");
    m_colors.threatCritical = QColor("#ff1744");
    
    // Track classification colors
    m_colors.hostile = QColor("#ff5252");
    m_colors.friendly = QColor("#50c878");
    m_colors.neutral = QColor("#ffd700");
    m_colors.unknown = QColor("#8b949e");
    m_colors.pending = QColor("#b0b0b0");
}

void ThemeManager::initializeFonts() {
    // Default font family (platform-specific)
#ifdef Q_OS_WIN
    QString fontFamily = "Segoe UI";
#elif defined(Q_OS_MACOS)
    QString fontFamily = "SF Pro Display";
#else
    QString fontFamily = "Ubuntu";
#endif
    
    // Heading font
    QFont headingFont(fontFamily, 14, QFont::Bold);
    m_fonts["heading"] = headingFont;
    
    // Body font
    QFont bodyFont(fontFamily, 11, QFont::Normal);
    m_fonts["body"] = bodyFont;
    
    // Small font
    QFont smallFont(fontFamily, 10, QFont::Normal);
    m_fonts["small"] = smallFont;
    
    // Monospace font (for IDs, coordinates, etc.)
    QFont monoFont("Consolas", 11, QFont::Normal);
#ifndef Q_OS_WIN
    monoFont.setFamily("Monaco");
#endif
    m_fonts["mono"] = monoFont;
    
    // Large heading
    QFont largeHeading(fontFamily, 16, QFont::Bold);
    m_fonts["largeHeading"] = largeHeading;
    
    // Panel header
    QFont panelHeader(fontFamily, 11, QFont::Bold);
    panelHeader.setLetterSpacing(QFont::AbsoluteSpacing, 1.0);
    m_fonts["panelHeader"] = panelHeader;
}

void ThemeManager::buildPalette() {
    m_palette = QPalette();
    
    // Window colors
    m_palette.setColor(QPalette::Window, m_colors.background);
    m_palette.setColor(QPalette::WindowText, m_colors.text);
    
    // Base colors (for input fields, list views)
    m_palette.setColor(QPalette::Base, m_colors.background);
    m_palette.setColor(QPalette::AlternateBase, m_colors.surface);
    
    // Text colors
    m_palette.setColor(QPalette::Text, m_colors.text);
    m_palette.setColor(QPalette::PlaceholderText, m_colors.textSecondary);
    
    // Button colors
    m_palette.setColor(QPalette::Button, m_colors.surfaceAlt);
    m_palette.setColor(QPalette::ButtonText, m_colors.text);
    
    // Highlight colors
    m_palette.setColor(QPalette::Highlight, m_colors.primary);
    m_palette.setColor(QPalette::HighlightedText, Qt::white);
    
    // Tooltip colors
    m_palette.setColor(QPalette::ToolTipBase, m_colors.surfaceAlt);
    m_palette.setColor(QPalette::ToolTipText, m_colors.text);
    
    // Link colors
    m_palette.setColor(QPalette::Link, m_colors.accent);
    m_palette.setColor(QPalette::LinkVisited, m_colors.primaryLight);
    
    // Disabled colors
    m_palette.setColor(QPalette::Disabled, QPalette::WindowText, m_colors.textDisabled);
    m_palette.setColor(QPalette::Disabled, QPalette::Text, m_colors.textDisabled);
    m_palette.setColor(QPalette::Disabled, QPalette::ButtonText, m_colors.textDisabled);
    
    // Bright text (used for alerts)
    m_palette.setColor(QPalette::BrightText, m_colors.danger);
}

void ThemeManager::applyDarkTheme() {
    if (!m_app) return;
    
    // Build and apply palette
    buildPalette();
    m_app->setPalette(m_palette);
    
    // Load and apply stylesheet
    QString stylesheet = loadStyleSheet();
    m_app->setStyleSheet(stylesheet);
    
    emit themeChanged();
}

QString ThemeManager::loadStyleSheet() const {
    QFile file(":/styles/dark_theme.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        return stream.readAll();
    }
    
    // Fallback: try loading from filesystem
    QFile fallbackFile("resources/styles/dark_theme.qss");
    if (fallbackFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&fallbackFile);
        return stream.readAll();
    }
    
    return QString();
}

void ThemeManager::detectScaleFactor() {
    if (!m_app) return;
    
    QScreen* screen = m_app->primaryScreen();
    if (screen) {
        qreal dpi = screen->logicalDotsPerInch();
        m_scaleFactor = dpi / 96.0;  // 96 DPI is standard
        
        // Clamp to reasonable range
        if (m_scaleFactor < 1.0) m_scaleFactor = 1.0;
        if (m_scaleFactor > 3.0) m_scaleFactor = 3.0;
    }
}

QString ThemeManager::styleSheet(const QString& componentType) const {
    return m_styleSheets.value(componentType, QString());
}

QColor ThemeManager::threatColor(int level) const {
    switch (level) {
        case 5: return m_colors.threatCritical;
        case 4: return m_colors.threatHigh;
        case 3: return m_colors.threatMedium;
        case 2: return m_colors.threatLow;
        default: return m_colors.threatMinimal;
    }
}

QColor ThemeManager::classificationColor(int classification) const {
    // TrackClassification enum values
    switch (classification) {
        case 2: return m_colors.hostile;    // Hostile
        case 3: return m_colors.friendly;   // Friendly
        case 4: return m_colors.neutral;    // Neutral
        case 1: return m_colors.unknown;    // Unknown
        default: return m_colors.pending;   // Pending
    }
}

QColor ThemeManager::statusColor(const QString& status) const {
    QString lower = status.toLower();
    
    if (lower == "active" || lower == "online" || lower == "ready" || lower == "engaged") {
        return m_colors.success;
    } else if (lower == "inactive" || lower == "offline" || lower == "dropped") {
        return m_colors.textSecondary;
    } else if (lower == "warning" || lower == "degraded" || lower == "coasting") {
        return m_colors.warning;
    } else if (lower == "error" || lower == "fault" || lower == "critical") {
        return m_colors.danger;
    } else if (lower == "initiated" || lower == "initializing") {
        return m_colors.info;
    }
    
    return m_colors.text;
}

QIcon ThemeManager::icon(const QString& iconName) const {
    QString path = QString(":/icons/%1.svg").arg(iconName);
    QIcon icon(path);
    
    // Fallback to PNG if SVG not available
    if (icon.isNull()) {
        path = QString(":/icons/%1.png").arg(iconName);
        icon = QIcon(path);
    }
    
    return icon;
}

QString ThemeManager::panelHeaderStyle(const QString& text) {
    Q_UNUSED(text)
    return QString(
        "QLabel { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #21262d, stop:1 #161b22); "
        "   border: 1px solid #30363d; "
        "   border-radius: 4px; "
        "   padding: 8px 12px; "
        "   font-weight: bold; "
        "   font-size: 11px; "
        "   text-transform: uppercase; "
        "   letter-spacing: 1px; "
        "   color: #00a8e8; "
        "}"
    );
}

QFont ThemeManager::font(const QString& type) const {
    return m_fonts.value(type, m_fonts.value("body"));
}

int ThemeManager::scaledSize(int baseSize) const {
    return qRound(baseSize * m_scaleFactor);
}

void ThemeManager::setScaleFactor(qreal factor) {
    if (factor > 0 && factor != m_scaleFactor) {
        m_scaleFactor = factor;
        emit scaleFactorChanged(factor);
    }
}

// Static style snippet generators

QString ThemeManager::tableStyle() {
    return QString(
        "QTableView, QTableWidget { "
        "   background-color: #0d1117; "
        "   alternate-background-color: #161b22; "
        "   border: 1px solid #30363d; "
        "   border-radius: 6px; "
        "   gridline-color: #21262d; "
        "   selection-background-color: #1e3a5f; "
        "   selection-color: #ffffff; "
        "   outline: none; "
        "} "
        "QTableView::item, QTableWidget::item { "
        "   padding: 8px; "
        "   border-bottom: 1px solid #21262d; "
        "} "
        "QTableView::item:hover, QTableWidget::item:hover { "
        "   background-color: #21262d; "
        "} "
        "QTableView::item:selected, QTableWidget::item:selected { "
        "   background-color: #1e3a5f; "
        "   color: #ffffff; "
        "} "
        "QHeaderView::section { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #21262d, stop:1 #161b22); "
        "   color: #e6edf3; "
        "   padding: 10px 8px; "
        "   border: none; "
        "   border-right: 1px solid #30363d; "
        "   border-bottom: 1px solid #30363d; "
        "   font-weight: 600; "
        "}"
    );
}

QString ThemeManager::buttonStyle(const QString& type) {
    if (type == "primary") {
        return QString(
            "QPushButton { "
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "       stop:0 #1e3a5f, stop:1 #0d2040); "
            "   border: 1px solid #00a8e8; "
            "   border-radius: 6px; "
            "   padding: 8px 16px; "
            "   color: #ffffff; "
            "   font-weight: 600; "
            "} "
            "QPushButton:hover { "
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "       stop:0 #2a4a6f, stop:1 #1e3a5f); "
            "   border-color: #33b5e5; "
            "} "
            "QPushButton:pressed { "
            "   background: #0d2040; "
            "} "
            "QPushButton:disabled { "
            "   background-color: #21262d; "
            "   border-color: #30363d; "
            "   color: #484f58; "
            "}"
        );
    } else if (type == "danger") {
        return QString(
            "QPushButton { "
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "       stop:0 #8b1a1a, stop:1 #5a1010); "
            "   border: 1px solid #dc3545; "
            "   border-radius: 6px; "
            "   padding: 8px 16px; "
            "   color: #ffffff; "
            "   font-weight: 600; "
            "} "
            "QPushButton:hover { "
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "       stop:0 #a52a2a, stop:1 #8b1a1a); "
            "   border-color: #ff4545; "
            "} "
            "QPushButton:pressed { "
            "   background: #5a1010; "
            "} "
            "QPushButton:disabled { "
            "   background-color: #21262d; "
            "   border-color: #30363d; "
            "   color: #484f58; "
            "}"
        );
    } else if (type == "success") {
        return QString(
            "QPushButton { "
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "       stop:0 #1a5c1a, stop:1 #0d3d0d); "
            "   border: 1px solid #28a745; "
            "   border-radius: 6px; "
            "   padding: 8px 16px; "
            "   color: #ffffff; "
            "   font-weight: 600; "
            "} "
            "QPushButton:hover { "
            "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "       stop:0 #2a6c2a, stop:1 #1a5c1a); "
            "   border-color: #4caf50; "
            "} "
            "QPushButton:pressed { "
            "   background: #0d3d0d; "
            "} "
            "QPushButton:disabled { "
            "   background-color: #21262d; "
            "   border-color: #30363d; "
            "   color: #484f58; "
            "}"
        );
    }
    
    // Default button style
    return QString(
        "QPushButton { "
        "   background-color: #21262d; "
        "   border: 1px solid #30363d; "
        "   border-radius: 6px; "
        "   padding: 8px 16px; "
        "   color: #e6edf3; "
        "   font-weight: 500; "
        "} "
        "QPushButton:hover { "
        "   background-color: #30363d; "
        "   border-color: #8b949e; "
        "} "
        "QPushButton:pressed { "
        "   background-color: #1e3a5f; "
        "   border-color: #00a8e8; "
        "} "
        "QPushButton:disabled { "
        "   background-color: #161b22; "
        "   border-color: #21262d; "
        "   color: #484f58; "
        "}"
    );
}

QString ThemeManager::groupBoxStyle() {
    return QString(
        "QGroupBox { "
        "   background-color: #161b22; "
        "   border: 1px solid #30363d; "
        "   border-radius: 8px; "
        "   margin-top: 16px; "
        "   padding: 16px 12px 12px 12px; "
        "   font-weight: 600; "
        "} "
        "QGroupBox::title { "
        "   subcontrol-origin: margin; "
        "   subcontrol-position: top left; "
        "   left: 16px; "
        "   padding: 4px 12px; "
        "   background-color: #1e3a5f; "
        "   border-radius: 4px; "
        "   color: #ffffff; "
        "}"
    );
}

QString ThemeManager::dockWidgetStyle() {
    return QString(
        "QDockWidget { "
        "   background-color: #0d1117; "
        "} "
        "QDockWidget::title { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #21262d, stop:1 #161b22); "
        "   padding: 10px 12px; "
        "   border: 1px solid #30363d; "
        "   border-bottom: 2px solid #1e3a5f; "
        "   font-weight: 600; "
        "   text-transform: uppercase; "
        "   letter-spacing: 1px; "
        "} "
        "QDockWidget::close-button, QDockWidget::float-button { "
        "   background-color: transparent; "
        "   border: none; "
        "   padding: 4px; "
        "   border-radius: 4px; "
        "} "
        "QDockWidget::close-button:hover, QDockWidget::float-button:hover { "
        "   background-color: #30363d; "
        "}"
    );
}

QString ThemeManager::comboBoxStyle() {
    return QString(
        "QComboBox { "
        "   background-color: #0d1117; "
        "   border: 1px solid #30363d; "
        "   border-radius: 6px; "
        "   padding: 6px 12px; "
        "   padding-right: 30px; "
        "   color: #e6edf3; "
        "   min-height: 24px; "
        "} "
        "QComboBox:hover { "
        "   border-color: #8b949e; "
        "} "
        "QComboBox:focus { "
        "   border-color: #00a8e8; "
        "} "
        "QComboBox::drop-down { "
        "   subcontrol-origin: padding; "
        "   subcontrol-position: top right; "
        "   width: 24px; "
        "   border-left: 1px solid #30363d; "
        "   border-top-right-radius: 6px; "
        "   border-bottom-right-radius: 6px; "
        "   background-color: #21262d; "
        "} "
        "QComboBox::drop-down:hover { "
        "   background-color: #30363d; "
        "} "
        "QComboBox QAbstractItemView { "
        "   background-color: #161b22; "
        "   border: 1px solid #30363d; "
        "   border-radius: 6px; "
        "   padding: 4px; "
        "   selection-background-color: #1e3a5f; "
        "   outline: none; "
        "}"
    );
}

QString ThemeManager::spinBoxStyle() {
    return QString(
        "QSpinBox, QDoubleSpinBox { "
        "   background-color: #0d1117; "
        "   border: 1px solid #30363d; "
        "   border-radius: 6px; "
        "   padding: 6px 8px; "
        "   padding-right: 24px; "
        "   color: #e6edf3; "
        "   min-height: 24px; "
        "} "
        "QSpinBox:focus, QDoubleSpinBox:focus { "
        "   border-color: #00a8e8; "
        "} "
        "QSpinBox::up-button, QDoubleSpinBox::up-button { "
        "   subcontrol-origin: border; "
        "   subcontrol-position: top right; "
        "   width: 20px; "
        "   border-left: 1px solid #30363d; "
        "   border-top-right-radius: 6px; "
        "   background-color: #21262d; "
        "} "
        "QSpinBox::up-button:hover, QDoubleSpinBox::up-button:hover { "
        "   background-color: #30363d; "
        "} "
        "QSpinBox::down-button, QDoubleSpinBox::down-button { "
        "   subcontrol-origin: border; "
        "   subcontrol-position: bottom right; "
        "   width: 20px; "
        "   border-left: 1px solid #30363d; "
        "   border-bottom-right-radius: 6px; "
        "   background-color: #21262d; "
        "} "
        "QSpinBox::down-button:hover, QDoubleSpinBox::down-button:hover { "
        "   background-color: #30363d; "
        "}"
    );
}

QString ThemeManager::listWidgetStyle() {
    return QString(
        "QListWidget { "
        "   background-color: #0d1117; "
        "   border: 1px solid #30363d; "
        "   border-radius: 6px; "
        "   padding: 4px; "
        "   outline: none; "
        "} "
        "QListWidget::item { "
        "   background-color: transparent; "
        "   border-radius: 4px; "
        "   padding: 8px 12px; "
        "   margin: 2px 0; "
        "} "
        "QListWidget::item:hover { "
        "   background-color: #21262d; "
        "} "
        "QListWidget::item:selected { "
        "   background-color: #1e3a5f; "
        "   color: #ffffff; "
        "}"
    );
}

QString ThemeManager::progressBarStyle() {
    return QString(
        "QProgressBar { "
        "   background-color: #21262d; "
        "   border: none; "
        "   border-radius: 4px; "
        "   text-align: center; "
        "   color: #e6edf3; "
        "   font-weight: 500; "
        "   min-height: 20px; "
        "} "
        "QProgressBar::chunk { "
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "       stop:0 #00a8e8, stop:1 #1e3a5f); "
        "   border-radius: 4px; "
        "}"
    );
}

QString ThemeManager::engageButtonStyle() {
    return QString(
        "QPushButton { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #8b1a1a, stop:1 #5a1010); "
        "   border: 2px solid #dc3545; "
        "   border-radius: 8px; "
        "   color: #ffffff; "
        "   font-weight: bold; "
        "   font-size: 14px; "
        "   padding: 12px 24px; "
        "   text-transform: uppercase; "
        "   letter-spacing: 2px; "
        "} "
        "QPushButton:hover:enabled { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #a52a2a, stop:1 #8b1a1a); "
        "   border-color: #ff4545; "
        "} "
        "QPushButton:pressed { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "       stop:0 #5a1010, stop:1 #3a0808); "
        "} "
        "QPushButton:disabled { "
        "   background-color: #21262d; "
        "   border-color: #30363d; "
        "   color: #484f58; "
        "}"
    );
}

QString ThemeManager::videoPanelStyle() {
    return QString(
        "QWidget { "
        "   background-color: #0d1117; "
        "   border: 2px solid #30363d; "
        "   border-radius: 8px; "
        "} "
        "QWidget:hover { "
        "   border-color: #1e3a5f; "
        "}"
    );
}

} // namespace CounterUAS
