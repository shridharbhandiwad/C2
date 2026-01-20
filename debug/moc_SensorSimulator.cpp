/****************************************************************************
** Meta object code from reading C++ file 'SensorSimulator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/simulators/SensorSimulator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SensorSimulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CounterUAS__SensorSimulator_t {
    QByteArrayData data[34];
    char stringdata0[440];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CounterUAS__SensorSimulator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CounterUAS__SensorSimulator_t qt_meta_stringdata_CounterUAS__SensorSimulator = {
    {
QT_MOC_LITERAL(0, 0, 27), // "CounterUAS::SensorSimulator"
QT_MOC_LITERAL(1, 28, 17), // "radarStateChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 2), // "id"
QT_MOC_LITERAL(4, 50, 13), // "RadarSimState"
QT_MOC_LITERAL(5, 64, 5), // "state"
QT_MOC_LITERAL(6, 70, 22), // "rfDetectorStateChanged"
QT_MOC_LITERAL(7, 93, 18), // "RFDetectorSimState"
QT_MOC_LITERAL(8, 112, 18), // "cameraStateChanged"
QT_MOC_LITERAL(9, 131, 14), // "CameraSimState"
QT_MOC_LITERAL(10, 146, 14), // "radarDetection"
QT_MOC_LITERAL(11, 161, 8), // "sensorId"
QT_MOC_LITERAL(12, 170, 11), // "GeoPosition"
QT_MOC_LITERAL(13, 182, 3), // "pos"
QT_MOC_LITERAL(14, 186, 14), // "VelocityVector"
QT_MOC_LITERAL(15, 201, 3), // "vel"
QT_MOC_LITERAL(16, 205, 7), // "quality"
QT_MOC_LITERAL(17, 213, 11), // "rfDetection"
QT_MOC_LITERAL(18, 225, 12), // "frequencyMHz"
QT_MOC_LITERAL(19, 238, 9), // "signalDbm"
QT_MOC_LITERAL(20, 248, 8), // "protocol"
QT_MOC_LITERAL(21, 257, 15), // "cameraDetection"
QT_MOC_LITERAL(22, 273, 11), // "boundingBox"
QT_MOC_LITERAL(23, 285, 11), // "objectClass"
QT_MOC_LITERAL(24, 297, 10), // "confidence"
QT_MOC_LITERAL(25, 308, 16), // "clutterGenerated"
QT_MOC_LITERAL(26, 325, 5), // "count"
QT_MOC_LITERAL(27, 331, 10), // "targetLost"
QT_MOC_LITERAL(28, 342, 8), // "targetId"
QT_MOC_LITERAL(29, 351, 17), // "newTargetDetected"
QT_MOC_LITERAL(30, 369, 17), // "simulationStarted"
QT_MOC_LITERAL(31, 387, 17), // "simulationStopped"
QT_MOC_LITERAL(32, 405, 16), // "updateSimulation"
QT_MOC_LITERAL(33, 422, 17) // "generateDetection"

    },
    "CounterUAS::SensorSimulator\0"
    "radarStateChanged\0\0id\0RadarSimState\0"
    "state\0rfDetectorStateChanged\0"
    "RFDetectorSimState\0cameraStateChanged\0"
    "CameraSimState\0radarDetection\0sensorId\0"
    "GeoPosition\0pos\0VelocityVector\0vel\0"
    "quality\0rfDetection\0frequencyMHz\0"
    "signalDbm\0protocol\0cameraDetection\0"
    "boundingBox\0objectClass\0confidence\0"
    "clutterGenerated\0count\0targetLost\0"
    "targetId\0newTargetDetected\0simulationStarted\0"
    "simulationStopped\0updateSimulation\0"
    "generateDetection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CounterUAS__SensorSimulator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       6,    2,   84,    2, 0x06 /* Public */,
       8,    2,   89,    2, 0x06 /* Public */,
      10,    4,   94,    2, 0x06 /* Public */,
      17,    5,  103,    2, 0x06 /* Public */,
      21,    4,  114,    2, 0x06 /* Public */,
      25,    2,  123,    2, 0x06 /* Public */,
      27,    2,  128,    2, 0x06 /* Public */,
      29,    2,  133,    2, 0x06 /* Public */,
      30,    0,  138,    2, 0x06 /* Public */,
      31,    0,  139,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      32,    0,  140,    2, 0x08 /* Private */,
      33,    0,  141,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7,    3,    5,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 9,    3,    5,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 12, 0x80000000 | 14, QMetaType::Double,   11,   13,   15,   16,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 12, QMetaType::Double, QMetaType::Double, QMetaType::QString,   11,   13,   18,   19,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::QRectF, QMetaType::QString, QMetaType::Double,   11,   22,   23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   11,   26,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   28,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   28,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CounterUAS::SensorSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SensorSimulator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->radarStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const RadarSimState(*)>(_a[2]))); break;
        case 1: _t->rfDetectorStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const RFDetectorSimState(*)>(_a[2]))); break;
        case 2: _t->cameraStateChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const CameraSimState(*)>(_a[2]))); break;
        case 3: _t->radarDetection((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const GeoPosition(*)>(_a[2])),(*reinterpret_cast< const VelocityVector(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 4: _t->rfDetection((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const GeoPosition(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 5: _t->cameraDetection((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QRectF(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 6: _t->clutterGenerated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->targetLost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->newTargetDetected((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->simulationStarted(); break;
        case 10: _t->simulationStopped(); break;
        case 11: _t->updateSimulation(); break;
        case 12: _t->generateDetection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SensorSimulator::*)(const QString & , const RadarSimState & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::radarStateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)(const QString & , const RFDetectorSimState & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::rfDetectorStateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)(const QString & , const CameraSimState & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::cameraStateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)(const QString & , const GeoPosition & , const VelocityVector & , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::radarDetection)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)(const QString & , const GeoPosition & , double , double , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::rfDetection)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)(const QString & , const QRectF & , const QString & , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::cameraDetection)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)(const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::clutterGenerated)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::targetLost)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::newTargetDetected)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::simulationStarted)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SensorSimulator::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SensorSimulator::simulationStopped)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CounterUAS::SensorSimulator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CounterUAS__SensorSimulator.data,
    qt_meta_data_CounterUAS__SensorSimulator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CounterUAS::SensorSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CounterUAS::SensorSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CounterUAS__SensorSimulator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CounterUAS::SensorSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CounterUAS::SensorSimulator::radarStateChanged(const QString & _t1, const RadarSimState & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CounterUAS::SensorSimulator::rfDetectorStateChanged(const QString & _t1, const RFDetectorSimState & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CounterUAS::SensorSimulator::cameraStateChanged(const QString & _t1, const CameraSimState & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CounterUAS::SensorSimulator::radarDetection(const QString & _t1, const GeoPosition & _t2, const VelocityVector & _t3, double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CounterUAS::SensorSimulator::rfDetection(const QString & _t1, const GeoPosition & _t2, double _t3, double _t4, const QString & _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CounterUAS::SensorSimulator::cameraDetection(const QString & _t1, const QRectF & _t2, const QString & _t3, double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CounterUAS::SensorSimulator::clutterGenerated(const QString & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CounterUAS::SensorSimulator::targetLost(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CounterUAS::SensorSimulator::newTargetDetected(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CounterUAS::SensorSimulator::simulationStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void CounterUAS::SensorSimulator::simulationStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
