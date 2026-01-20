/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/ui/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CounterUAS__MainWindow_t {
    QByteArrayData data[44];
    char stringdata0[700];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CounterUAS__MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CounterUAS__MainWindow_t qt_meta_stringdata_CounterUAS__MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 22), // "CounterUAS::MainWindow"
QT_MOC_LITERAL(1, 23, 15), // "startSimulation"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 14), // "stopSimulation"
QT_MOC_LITERAL(4, 55, 15), // "pauseSimulation"
QT_MOC_LITERAL(5, 71, 15), // "resetSimulation"
QT_MOC_LITERAL(6, 87, 17), // "loadConfiguration"
QT_MOC_LITERAL(7, 105, 17), // "saveConfiguration"
QT_MOC_LITERAL(8, 123, 19), // "exportConfiguration"
QT_MOC_LITERAL(9, 143, 19), // "importConfiguration"
QT_MOC_LITERAL(10, 163, 9), // "showAbout"
QT_MOC_LITERAL(11, 173, 8), // "showHelp"
QT_MOC_LITERAL(12, 182, 15), // "updateStatusBar"
QT_MOC_LITERAL(13, 198, 15), // "onTrackSelected"
QT_MOC_LITERAL(14, 214, 7), // "trackId"
QT_MOC_LITERAL(15, 222, 17), // "onEngageRequested"
QT_MOC_LITERAL(16, 240, 21), // "onCameraSlewRequested"
QT_MOC_LITERAL(17, 262, 14), // "onAlertClicked"
QT_MOC_LITERAL(18, 277, 7), // "alertId"
QT_MOC_LITERAL(19, 285, 21), // "toggleFullScreenVideo"
QT_MOC_LITERAL(20, 307, 22), // "onSimulationVideoFrame"
QT_MOC_LITERAL(21, 330, 5), // "frame"
QT_MOC_LITERAL(22, 336, 9), // "timestamp"
QT_MOC_LITERAL(23, 346, 23), // "onSimulationCameraFrame"
QT_MOC_LITERAL(24, 370, 8), // "cameraId"
QT_MOC_LITERAL(25, 379, 17), // "onSensorConfigure"
QT_MOC_LITERAL(26, 397, 19), // "onSensorDiagnostics"
QT_MOC_LITERAL(27, 417, 16), // "onEffectorStatus"
QT_MOC_LITERAL(28, 434, 19), // "onRulesOfEngagement"
QT_MOC_LITERAL(29, 454, 19), // "onRecordingSettings"
QT_MOC_LITERAL(30, 474, 20), // "onSimulationSettings"
QT_MOC_LITERAL(31, 495, 17), // "onAddCameraStream"
QT_MOC_LITERAL(32, 513, 19), // "onStartAllRecording"
QT_MOC_LITERAL(33, 533, 18), // "onStopAllRecording"
QT_MOC_LITERAL(34, 552, 14), // "onTakeSnapshot"
QT_MOC_LITERAL(35, 567, 12), // "onSaveLayout"
QT_MOC_LITERAL(36, 580, 15), // "onRestoreLayout"
QT_MOC_LITERAL(37, 596, 13), // "onResetLayout"
QT_MOC_LITERAL(38, 610, 18), // "onTogglePPIDisplay"
QT_MOC_LITERAL(39, 629, 23), // "onPPIDisplayModeChanged"
QT_MOC_LITERAL(40, 653, 4), // "mode"
QT_MOC_LITERAL(41, 658, 17), // "onPPIRangeChanged"
QT_MOC_LITERAL(42, 676, 6), // "rangeM"
QT_MOC_LITERAL(43, 683, 16) // "onPPISweepToggle"

    },
    "CounterUAS::MainWindow\0startSimulation\0"
    "\0stopSimulation\0pauseSimulation\0"
    "resetSimulation\0loadConfiguration\0"
    "saveConfiguration\0exportConfiguration\0"
    "importConfiguration\0showAbout\0showHelp\0"
    "updateStatusBar\0onTrackSelected\0trackId\0"
    "onEngageRequested\0onCameraSlewRequested\0"
    "onAlertClicked\0alertId\0toggleFullScreenVideo\0"
    "onSimulationVideoFrame\0frame\0timestamp\0"
    "onSimulationCameraFrame\0cameraId\0"
    "onSensorConfigure\0onSensorDiagnostics\0"
    "onEffectorStatus\0onRulesOfEngagement\0"
    "onRecordingSettings\0onSimulationSettings\0"
    "onAddCameraStream\0onStartAllRecording\0"
    "onStopAllRecording\0onTakeSnapshot\0"
    "onSaveLayout\0onRestoreLayout\0onResetLayout\0"
    "onTogglePPIDisplay\0onPPIDisplayModeChanged\0"
    "mode\0onPPIRangeChanged\0rangeM\0"
    "onPPISweepToggle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CounterUAS__MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  189,    2, 0x0a /* Public */,
       3,    0,  190,    2, 0x0a /* Public */,
       4,    0,  191,    2, 0x0a /* Public */,
       5,    0,  192,    2, 0x0a /* Public */,
       6,    0,  193,    2, 0x0a /* Public */,
       7,    0,  194,    2, 0x0a /* Public */,
       8,    0,  195,    2, 0x0a /* Public */,
       9,    0,  196,    2, 0x0a /* Public */,
      10,    0,  197,    2, 0x0a /* Public */,
      11,    0,  198,    2, 0x0a /* Public */,
      12,    0,  199,    2, 0x08 /* Private */,
      13,    1,  200,    2, 0x08 /* Private */,
      15,    1,  203,    2, 0x08 /* Private */,
      16,    1,  206,    2, 0x08 /* Private */,
      17,    1,  209,    2, 0x08 /* Private */,
      19,    0,  212,    2, 0x08 /* Private */,
      20,    2,  213,    2, 0x08 /* Private */,
      23,    3,  218,    2, 0x08 /* Private */,
      25,    0,  225,    2, 0x08 /* Private */,
      26,    0,  226,    2, 0x08 /* Private */,
      27,    0,  227,    2, 0x08 /* Private */,
      28,    0,  228,    2, 0x08 /* Private */,
      29,    0,  229,    2, 0x08 /* Private */,
      30,    0,  230,    2, 0x08 /* Private */,
      31,    0,  231,    2, 0x08 /* Private */,
      32,    0,  232,    2, 0x08 /* Private */,
      33,    0,  233,    2, 0x08 /* Private */,
      34,    0,  234,    2, 0x08 /* Private */,
      35,    0,  235,    2, 0x08 /* Private */,
      36,    0,  236,    2, 0x08 /* Private */,
      37,    0,  237,    2, 0x08 /* Private */,
      38,    0,  238,    2, 0x08 /* Private */,
      39,    1,  239,    2, 0x08 /* Private */,
      41,    1,  242,    2, 0x08 /* Private */,
      43,    0,  245,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage, QMetaType::LongLong,   21,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::QImage, QMetaType::LongLong,   24,   21,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Void, QMetaType::Double,   42,
    QMetaType::Void,

       0        // eod
};

void CounterUAS::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startSimulation(); break;
        case 1: _t->stopSimulation(); break;
        case 2: _t->pauseSimulation(); break;
        case 3: _t->resetSimulation(); break;
        case 4: _t->loadConfiguration(); break;
        case 5: _t->saveConfiguration(); break;
        case 6: _t->exportConfiguration(); break;
        case 7: _t->importConfiguration(); break;
        case 8: _t->showAbout(); break;
        case 9: _t->showHelp(); break;
        case 10: _t->updateStatusBar(); break;
        case 11: _t->onTrackSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->onEngageRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->onCameraSlewRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->onAlertClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->toggleFullScreenVideo(); break;
        case 16: _t->onSimulationVideoFrame((*reinterpret_cast< const QImage(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 17: _t->onSimulationCameraFrame((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QImage(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 18: _t->onSensorConfigure(); break;
        case 19: _t->onSensorDiagnostics(); break;
        case 20: _t->onEffectorStatus(); break;
        case 21: _t->onRulesOfEngagement(); break;
        case 22: _t->onRecordingSettings(); break;
        case 23: _t->onSimulationSettings(); break;
        case 24: _t->onAddCameraStream(); break;
        case 25: _t->onStartAllRecording(); break;
        case 26: _t->onStopAllRecording(); break;
        case 27: _t->onTakeSnapshot(); break;
        case 28: _t->onSaveLayout(); break;
        case 29: _t->onRestoreLayout(); break;
        case 30: _t->onResetLayout(); break;
        case 31: _t->onTogglePPIDisplay(); break;
        case 32: _t->onPPIDisplayModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->onPPIRangeChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 34: _t->onPPISweepToggle(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CounterUAS::MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CounterUAS__MainWindow.data,
    qt_meta_data_CounterUAS__MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CounterUAS::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CounterUAS::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CounterUAS__MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int CounterUAS::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 35;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
