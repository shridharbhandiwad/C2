/**
 * Counter-UAS Command & Control System
 * 
 * A real-time command and control application for Counter-UAS system
 * protecting military installations.
 * 
 * Features:
 * - Multi-sensor integration (Radar, RF, Camera)
 * - Track management with Kalman filtering
 * - Threat assessment and prioritization
 * - Video feed management with overlays
 * - Effector control (RF Jammer, Kinetic, Directed Energy)
 * - Modern Qt-based tactical interface with professional dark theme
 */

#include <QApplication>
#include <QStyleFactory>
#include <QSurfaceFormat>
#include <QScreen>
#include "ui/MainWindow.h"
#include "ui/ThemeManager.h"
#include "config/ConfigManager.h"
#include "config/DatabaseManager.h"
#include "utils/Logger.h"
#include "simulators/TrackSimulator.h"

using namespace CounterUAS;

int main(int argc, char *argv[])
{
    // Enable HiDPI scaling before creating QApplication
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    
    // Set OpenGL format for video rendering
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
    
    QApplication app(argc, argv);
    app.setApplicationName("Counter-UAS C2");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Defense Systems");
    
    // Initialize theme manager with modern dark theme
    ThemeManager::instance().initialize(&app);
    
    // Initialize logger
    Logger::instance().setLogLevel(LogLevel::Debug);
    Logger::instance().setLogToConsole(true);
    Logger::instance().info("Main", "Counter-UAS C2 System starting...");
    
    // Load configuration
    ConfigManager::instance().loadDefaults();
    
    // Initialize database
    DatabaseManager::instance().initialize("data/counter_uas.db");
    
    // Create and show main window
    MainWindow mainWindow;
    mainWindow.show();
    
    // Create track simulator for testing
    TrackSimulator simulator(mainWindow.trackManager());
    simulator.start();
    
    // Start simulation automatically for demo
    mainWindow.startSimulation();
    
    Logger::instance().info("Main", "System initialized successfully");
    
    int result = app.exec();
    
    // Cleanup
    simulator.stop();
    DatabaseManager::instance().close();
    
    Logger::instance().info("Main", "System shutdown complete");
    
    return result;
}
