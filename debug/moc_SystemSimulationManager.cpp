/****************************************************************************
** Meta object code from reading C++ file 'SystemSimulationManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/simulators/SystemSimulationManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SystemSimulationManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CounterUAS__SystemSimulationManager_t {
    QByteArrayData data[34];
    char stringdata0[443];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CounterUAS__SystemSimulationManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CounterUAS__SystemSimulationManager_t qt_meta_stringdata_CounterUAS__SystemSimulationManager = {
    {
QT_MOC_LITERAL(0, 0, 35), // "CounterUAS::SystemSimulationM..."
QT_MOC_LITERAL(1, 36, 14), // "runningChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 7), // "running"
QT_MOC_LITERAL(4, 60, 13), // "pausedChanged"
QT_MOC_LITERAL(5, 74, 6), // "paused"
QT_MOC_LITERAL(6, 81, 14), // "scenarioLoaded"
QT_MOC_LITERAL(7, 96, 4), // "name"
QT_MOC_LITERAL(8, 101, 18), // "simulationProgress"
QT_MOC_LITERAL(9, 120, 7), // "percent"
QT_MOC_LITERAL(10, 128, 17), // "statisticsUpdated"
QT_MOC_LITERAL(11, 146, 15), // "SimulationStats"
QT_MOC_LITERAL(12, 162, 5), // "stats"
QT_MOC_LITERAL(13, 168, 13), // "targetSpawned"
QT_MOC_LITERAL(14, 182, 7), // "trackId"
QT_MOC_LITERAL(15, 190, 11), // "GeoPosition"
QT_MOC_LITERAL(16, 202, 8), // "position"
QT_MOC_LITERAL(17, 211, 15), // "targetDestroyed"
QT_MOC_LITERAL(18, 227, 17), // "engagementStarted"
QT_MOC_LITERAL(19, 245, 10), // "effectorId"
QT_MOC_LITERAL(20, 256, 19), // "engagementCompleted"
QT_MOC_LITERAL(21, 276, 7), // "success"
QT_MOC_LITERAL(22, 284, 19), // "sensorStatusChanged"
QT_MOC_LITERAL(23, 304, 8), // "sensorId"
QT_MOC_LITERAL(24, 313, 6), // "online"
QT_MOC_LITERAL(25, 320, 21), // "effectorStatusChanged"
QT_MOC_LITERAL(26, 342, 5), // "ready"
QT_MOC_LITERAL(27, 348, 5), // "error"
QT_MOC_LITERAL(28, 354, 7), // "message"
QT_MOC_LITERAL(29, 362, 16), // "updateSimulation"
QT_MOC_LITERAL(30, 379, 14), // "onTrackCreated"
QT_MOC_LITERAL(31, 394, 14), // "onTrackDropped"
QT_MOC_LITERAL(32, 409, 20), // "onEngagementComplete"
QT_MOC_LITERAL(33, 430, 12) // "engagementId"

    },
    "CounterUAS::SystemSimulationManager\0"
    "runningChanged\0\0running\0pausedChanged\0"
    "paused\0scenarioLoaded\0name\0"
    "simulationProgress\0percent\0statisticsUpdated\0"
    "SimulationStats\0stats\0targetSpawned\0"
    "trackId\0GeoPosition\0position\0"
    "targetDestroyed\0engagementStarted\0"
    "effectorId\0engagementCompleted\0success\0"
    "sensorStatusChanged\0sensorId\0online\0"
    "effectorStatusChanged\0ready\0error\0"
    "message\0updateSimulation\0onTrackCreated\0"
    "onTrackDropped\0onEngagementComplete\0"
    "engagementId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CounterUAS__SystemSimulationManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       2,  152, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       6,    1,  100,    2, 0x06 /* Public */,
       8,    1,  103,    2, 0x06 /* Public */,
      10,    1,  106,    2, 0x06 /* Public */,
      13,    2,  109,    2, 0x06 /* Public */,
      17,    1,  114,    2, 0x06 /* Public */,
      18,    2,  117,    2, 0x06 /* Public */,
      20,    2,  122,    2, 0x06 /* Public */,
      22,    2,  127,    2, 0x06 /* Public */,
      25,    2,  132,    2, 0x06 /* Public */,
      27,    1,  137,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      29,    0,  140,    2, 0x08 /* Private */,
      30,    1,  141,    2, 0x08 /* Private */,
      31,    1,  144,    2, 0x08 /* Private */,
      32,    2,  147,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 15,   14,   16,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   14,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   14,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   19,   26,
    QMetaType::Void, QMetaType::QString,   28,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   33,   21,

 // properties: name, type, flags
       3, QMetaType::Bool, 0x00495001,
       5, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void CounterUAS::SystemSimulationManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SystemSimulationManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->runningChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->pausedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->scenarioLoaded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->simulationProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->statisticsUpdated((*reinterpret_cast< const SimulationStats(*)>(_a[1]))); break;
        case 5: _t->targetSpawned((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const GeoPosition(*)>(_a[2]))); break;
        case 6: _t->targetDestroyed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->engagementStarted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->engagementCompleted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: _t->sensorStatusChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 10: _t->effectorStatusChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 11: _t->error((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->updateSimulation(); break;
        case 13: _t->onTrackCreated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->onTrackDropped((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->onEngagementComplete((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SystemSimulationManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::runningChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::pausedChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::scenarioLoaded)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::simulationProgress)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(const SimulationStats & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::statisticsUpdated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(const QString & , const GeoPosition & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::targetSpawned)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::targetDestroyed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::engagementStarted)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(const QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::engagementCompleted)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(const QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::sensorStatusChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(const QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::effectorStatusChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SystemSimulationManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSimulationManager::error)) {
                *result = 11;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SystemSimulationManager *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isRunning(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isPaused(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject CounterUAS::SystemSimulationManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CounterUAS__SystemSimulationManager.data,
    qt_meta_data_CounterUAS__SystemSimulationManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CounterUAS::SystemSimulationManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CounterUAS::SystemSimulationManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CounterUAS__SystemSimulationManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CounterUAS::SystemSimulationManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CounterUAS::SystemSimulationManager::runningChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CounterUAS::SystemSimulationManager::pausedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CounterUAS::SystemSimulationManager::scenarioLoaded(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CounterUAS::SystemSimulationManager::simulationProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CounterUAS::SystemSimulationManager::statisticsUpdated(const SimulationStats & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CounterUAS::SystemSimulationManager::targetSpawned(const QString & _t1, const GeoPosition & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CounterUAS::SystemSimulationManager::targetDestroyed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CounterUAS::SystemSimulationManager::engagementStarted(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CounterUAS::SystemSimulationManager::engagementCompleted(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CounterUAS::SystemSimulationManager::sensorStatusChanged(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void CounterUAS::SystemSimulationManager::effectorStatusChanged(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void CounterUAS::SystemSimulationManager::error(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
