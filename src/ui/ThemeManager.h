/**
 * @file ThemeManager.h
 * @brief Centralized theme management for Counter-UAS C2 application
 * 
 * Provides consistent styling, color management, and HiDPI support
 * throughout the application.
 */

#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QColor>
#include <QFont>
#include <QIcon>
#include <QPalette>
#include <QString>
#include <QMap>

namespace CounterUAS {

/**
 * @brief Color palette for the application theme
 */
struct ThemeColors {
    // Primary colors
    QColor primary;         // Main accent color
    QColor primaryDark;     // Darker variant
    QColor primaryLight;    // Lighter variant
    QColor accent;          // Secondary accent
    
    // Background colors
    QColor background;      // Main background
    QColor surface;         // Surface/card background
    QColor surfaceAlt;      // Alternative surface
    
    // Border colors
    QColor border;          // Standard border
    QColor borderLight;     // Lighter border
    QColor borderHover;     // Border on hover
    
    // Text colors
    QColor text;            // Primary text
    QColor textSecondary;   // Secondary/muted text
    QColor textDisabled;    // Disabled text
    
    // Status colors
    QColor success;         // Success/online
    QColor warning;         // Warning/caution
    QColor danger;          // Error/danger/hostile
    QColor info;            // Information
    
    // Threat level colors
    QColor threatCritical;
    QColor threatHigh;
    QColor threatMedium;
    QColor threatLow;
    QColor threatMinimal;
    
    // Track classification colors
    QColor hostile;
    QColor friendly;
    QColor neutral;
    QColor unknown;
    QColor pending;
};

/**
 * @brief Singleton theme manager for consistent UI styling
 */
class ThemeManager : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Get singleton instance
     */
    static ThemeManager& instance();
    
    /**
     * @brief Initialize theme manager and apply theme
     * @param app QApplication pointer
     */
    void initialize(class QApplication* app);
    
    /**
     * @brief Load and apply the dark theme stylesheet
     */
    void applyDarkTheme();
    
    /**
     * @brief Get current theme colors
     */
    const ThemeColors& colors() const { return m_colors; }
    
    /**
     * @brief Get the application palette
     */
    QPalette palette() const { return m_palette; }
    
    /**
     * @brief Get stylesheet for a specific component type
     * @param componentType Type of component (button, panel, etc.)
     */
    QString styleSheet(const QString& componentType) const;
    
    // Convenience methods for common styling needs
    
    /**
     * @brief Get color for threat level (1-5)
     */
    QColor threatColor(int level) const;
    
    /**
     * @brief Get color for track classification
     */
    QColor classificationColor(int classification) const;
    
    /**
     * @brief Get color for status string
     */
    QColor statusColor(const QString& status) const;
    
    /**
     * @brief Get styled icon with theme-appropriate colors
     * @param iconName Base icon name (without extension)
     */
    QIcon icon(const QString& iconName) const;
    
    /**
     * @brief Create a styled panel header label
     * @param text Header text
     */
    static QString panelHeaderStyle(const QString& text);
    
    /**
     * @brief Get standard font for different uses
     * @param type Font type: "heading", "body", "small", "mono"
     */
    QFont font(const QString& type) const;
    
    /**
     * @brief Get scaled size for HiDPI displays
     * @param baseSize Size at 1x scale
     */
    int scaledSize(int baseSize) const;
    
    /**
     * @brief Get current DPI scale factor
     */
    qreal scaleFactor() const { return m_scaleFactor; }
    
    /**
     * @brief Set custom scale factor (override auto-detection)
     */
    void setScaleFactor(qreal factor);
    
    // Predefined style snippets
    static QString tableStyle();
    static QString buttonStyle(const QString& type = "default");
    static QString groupBoxStyle();
    static QString dockWidgetStyle();
    static QString comboBoxStyle();
    static QString spinBoxStyle();
    static QString listWidgetStyle();
    static QString progressBarStyle();
    static QString engageButtonStyle();
    static QString videoPanelStyle();
    
signals:
    void themeChanged();
    void scaleFactorChanged(qreal factor);

private:
    ThemeManager(QObject* parent = nullptr);
    ~ThemeManager() override = default;
    
    // Prevent copying
    ThemeManager(const ThemeManager&) = delete;
    ThemeManager& operator=(const ThemeManager&) = delete;
    
    void initializeColors();
    void initializeFonts();
    void buildPalette();
    QString loadStyleSheet() const;
    void detectScaleFactor();
    
    ThemeColors m_colors;
    QPalette m_palette;
    QMap<QString, QString> m_styleSheets;
    QMap<QString, QFont> m_fonts;
    qreal m_scaleFactor;
    class QApplication* m_app;
};

} // namespace CounterUAS

#endif // THEMEMANAGER_H
