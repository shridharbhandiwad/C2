/****************************************************************************
** Meta object code from reading C++ file 'EffectorSimulator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/simulators/EffectorSimulator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EffectorSimulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CounterUAS__EffectorSimulator_t {
    QByteArrayData data[30];
    char stringdata0[431];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CounterUAS__EffectorSimulator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CounterUAS__EffectorSimulator_t qt_meta_stringdata_CounterUAS__EffectorSimulator = {
    {
QT_MOC_LITERAL(0, 0, 29), // "CounterUAS::EffectorSimulator"
QT_MOC_LITERAL(1, 30, 20), // "rfJammerStateChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 2), // "id"
QT_MOC_LITERAL(4, 55, 16), // "RFJammerSimState"
QT_MOC_LITERAL(5, 72, 5), // "state"
QT_MOC_LITERAL(6, 78, 19), // "kineticStateChanged"
QT_MOC_LITERAL(7, 98, 15), // "KineticSimState"
QT_MOC_LITERAL(8, 114, 14), // "deStateChanged"
QT_MOC_LITERAL(9, 129, 10), // "DESimState"
QT_MOC_LITERAL(10, 140, 19), // "engagementSimulated"
QT_MOC_LITERAL(11, 160, 25), // "SimulatedEngagementResult"
QT_MOC_LITERAL(12, 186, 6), // "result"
QT_MOC_LITERAL(13, 193, 19), // "interceptorInFlight"
QT_MOC_LITERAL(14, 213, 11), // "GeoPosition"
QT_MOC_LITERAL(15, 225, 8), // "position"
QT_MOC_LITERAL(16, 234, 16), // "distanceToTarget"
QT_MOC_LITERAL(17, 251, 21), // "targetEffectSimulated"
QT_MOC_LITERAL(18, 273, 10), // "effectorId"
QT_MOC_LITERAL(19, 284, 7), // "trackId"
QT_MOC_LITERAL(20, 292, 11), // "effectLevel"
QT_MOC_LITERAL(21, 304, 17), // "simulationStarted"
QT_MOC_LITERAL(22, 322, 17), // "simulationStopped"
QT_MOC_LITERAL(23, 340, 16), // "updateSimulation"
QT_MOC_LITERAL(24, 357, 17), // "onRFJammerEngaged"
QT_MOC_LITERAL(25, 375, 7), // "engaged"
QT_MOC_LITERAL(26, 383, 17), // "onKineticLaunched"
QT_MOC_LITERAL(27, 401, 9), // "remaining"
QT_MOC_LITERAL(28, 411, 16), // "onDEPowerChanged"
QT_MOC_LITERAL(29, 428, 2) // "kw"

    },
    "CounterUAS::EffectorSimulator\0"
    "rfJammerStateChanged\0\0id\0RFJammerSimState\0"
    "state\0kineticStateChanged\0KineticSimState\0"
    "deStateChanged\0DESimState\0engagementSimulated\0"
    "SimulatedEngagementResult\0result\0"
    "interceptorInFlight\0GeoPosition\0"
    "position\0distanceToTarget\0"
    "targetEffectSimulated\0effectorId\0"
    "trackId\0effectLevel\0simulationStarted\0"
    "simulationStopped\0updateSimulation\0"
    "onRFJammerEngaged\0engaged\0onKineticLaunched\0"
    "remaining\0onDEPowerChanged\0kw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CounterUAS__EffectorSimulator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       6,    2,   79,    2, 0x06 /* Public */,
       8,    2,   84,    2, 0x06 /* Public */,
      10,    1,   89,    2, 0x06 /* Public */,
      13,    3,   92,    2, 0x06 /* Public */,
      17,    3,   99,    2, 0x06 /* Public */,
      21,    0,  106,    2, 0x06 /* Public */,
      22,    0,  107,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      23,    0,  108,    2, 0x08 /* Private */,
      24,    1,  109,    2, 0x08 /* Private */,
      26,    1,  112,    2, 0x08 /* Private */,
      28,    1,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7,    3,    5,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 9,    3,    5,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 14, QMetaType::Double,    3,   15,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Double,   18,   19,   20,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   25,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Double,   29,

       0        // eod
};

void CounterUAS::EffectorSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EffectorSimulator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rfJammerStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const RFJammerSimState(*)>(_a[2]))); break;
        case 1: _t->kineticStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const KineticSimState(*)>(_a[2]))); break;
        case 2: _t->deStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const DESimState(*)>(_a[2]))); break;
        case 3: _t->engagementSimulated((*reinterpret_cast< const SimulatedEngagementResult(*)>(_a[1]))); break;
        case 4: _t->interceptorInFlight((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const GeoPosition(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 5: _t->targetEffectSimulated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 6: _t->simulationStarted(); break;
        case 7: _t->simulationStopped(); break;
        case 8: _t->updateSimulation(); break;
        case 9: _t->onRFJammerEngaged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->onKineticLaunched((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onDEPowerChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EffectorSimulator::*)(const QString & , const RFJammerSimState & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorSimulator::rfJammerStateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EffectorSimulator::*)(const QString & , const KineticSimState & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorSimulator::kineticStateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EffectorSimulator::*)(const QString & , const DESimState & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorSimulator::deStateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (EffectorSimulator::*)(const SimulatedEngagementResult & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorSimulator::engagementSimulated)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (EffectorSimulator::*)(const QString & , const GeoPosition & , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorSimulator::interceptorInFlight)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (EffectorSimulator::*)(const QString & , const QString & , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorSimulator::targetEffectSimulated)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (EffectorSimulator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorSimulator::simulationStarted)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (EffectorSimulator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorSimulator::simulationStopped)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CounterUAS::EffectorSimulator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CounterUAS__EffectorSimulator.data,
    qt_meta_data_CounterUAS__EffectorSimulator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CounterUAS::EffectorSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CounterUAS::EffectorSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CounterUAS__EffectorSimulator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CounterUAS::EffectorSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CounterUAS::EffectorSimulator::rfJammerStateChanged(const QString & _t1, const RFJammerSimState & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CounterUAS::EffectorSimulator::kineticStateChanged(const QString & _t1, const KineticSimState & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CounterUAS::EffectorSimulator::deStateChanged(const QString & _t1, const DESimState & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CounterUAS::EffectorSimulator::engagementSimulated(const SimulatedEngagementResult & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CounterUAS::EffectorSimulator::interceptorInFlight(const QString & _t1, const GeoPosition & _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CounterUAS::EffectorSimulator::targetEffectSimulated(const QString & _t1, const QString & _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CounterUAS::EffectorSimulator::simulationStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void CounterUAS::EffectorSimulator::simulationStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
