/****************************************************************************
** Meta object code from reading C++ file 'PPIDisplayWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/ui/PPIDisplayWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PPIDisplayWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CounterUAS__PPIDisplayWidget_t {
    QByteArrayData data[31];
    char stringdata0[375];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CounterUAS__PPIDisplayWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CounterUAS__PPIDisplayWidget_t qt_meta_stringdata_CounterUAS__PPIDisplayWidget = {
    {
QT_MOC_LITERAL(0, 0, 28), // "CounterUAS::PPIDisplayWidget"
QT_MOC_LITERAL(1, 29, 13), // "trackSelected"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 7), // "trackId"
QT_MOC_LITERAL(4, 52, 18), // "trackDoubleClicked"
QT_MOC_LITERAL(5, 71, 10), // "mapClicked"
QT_MOC_LITERAL(6, 82, 11), // "GeoPosition"
QT_MOC_LITERAL(7, 94, 3), // "pos"
QT_MOC_LITERAL(8, 98, 17), // "rangeScaleChanged"
QT_MOC_LITERAL(9, 116, 6), // "rangeM"
QT_MOC_LITERAL(10, 123, 17), // "sweepAngleChanged"
QT_MOC_LITERAL(11, 141, 5), // "angle"
QT_MOC_LITERAL(12, 147, 18), // "displayModeChanged"
QT_MOC_LITERAL(13, 166, 14), // "PPIDisplayMode"
QT_MOC_LITERAL(14, 181, 4), // "mode"
QT_MOC_LITERAL(15, 186, 8), // "addTrack"
QT_MOC_LITERAL(16, 195, 11), // "updateTrack"
QT_MOC_LITERAL(17, 207, 11), // "removeTrack"
QT_MOC_LITERAL(18, 219, 11), // "clearTracks"
QT_MOC_LITERAL(19, 231, 10), // "startSweep"
QT_MOC_LITERAL(20, 242, 9), // "stopSweep"
QT_MOC_LITERAL(21, 252, 10), // "resetSweep"
QT_MOC_LITERAL(22, 263, 7), // "refresh"
QT_MOC_LITERAL(23, 271, 11), // "updateSweep"
QT_MOC_LITERAL(24, 283, 17), // "onMapTileReceived"
QT_MOC_LITERAL(25, 301, 14), // "QNetworkReply*"
QT_MOC_LITERAL(26, 316, 5), // "reply"
QT_MOC_LITERAL(27, 322, 18), // "updateTrackHistory"
QT_MOC_LITERAL(28, 341, 10), // "sweepAngle"
QT_MOC_LITERAL(29, 352, 10), // "rangeScale"
QT_MOC_LITERAL(30, 363, 11) // "displayMode"

    },
    "CounterUAS::PPIDisplayWidget\0trackSelected\0"
    "\0trackId\0trackDoubleClicked\0mapClicked\0"
    "GeoPosition\0pos\0rangeScaleChanged\0"
    "rangeM\0sweepAngleChanged\0angle\0"
    "displayModeChanged\0PPIDisplayMode\0"
    "mode\0addTrack\0updateTrack\0removeTrack\0"
    "clearTracks\0startSweep\0stopSweep\0"
    "resetSweep\0refresh\0updateSweep\0"
    "onMapTileReceived\0QNetworkReply*\0reply\0"
    "updateTrackHistory\0sweepAngle\0rangeScale\0"
    "displayMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CounterUAS__PPIDisplayWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       3,  136, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    1,  102,    2, 0x06 /* Public */,
       5,    1,  105,    2, 0x06 /* Public */,
       8,    1,  108,    2, 0x06 /* Public */,
      10,    1,  111,    2, 0x06 /* Public */,
      12,    1,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,  117,    2, 0x0a /* Public */,
      16,    1,  120,    2, 0x0a /* Public */,
      17,    1,  123,    2, 0x0a /* Public */,
      18,    0,  126,    2, 0x0a /* Public */,
      19,    0,  127,    2, 0x0a /* Public */,
      20,    0,  128,    2, 0x0a /* Public */,
      21,    0,  129,    2, 0x0a /* Public */,
      22,    0,  130,    2, 0x0a /* Public */,
      23,    0,  131,    2, 0x08 /* Private */,
      24,    1,  132,    2, 0x08 /* Private */,
      27,    0,  135,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void,

 // properties: name, type, flags
      28, QMetaType::Double, 0x00495001,
      29, QMetaType::Double, 0x00495103,
      30, 0x80000000 | 13, 0x0049510b,

 // properties: notify_signal_id
       4,
       3,
       5,

       0        // eod
};

void CounterUAS::PPIDisplayWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PPIDisplayWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->trackSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->trackDoubleClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->mapClicked((*reinterpret_cast< const GeoPosition(*)>(_a[1]))); break;
        case 3: _t->rangeScaleChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->sweepAngleChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->displayModeChanged((*reinterpret_cast< PPIDisplayMode(*)>(_a[1]))); break;
        case 6: _t->addTrack((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->updateTrack((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->removeTrack((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->clearTracks(); break;
        case 10: _t->startSweep(); break;
        case 11: _t->stopSweep(); break;
        case 12: _t->resetSweep(); break;
        case 13: _t->refresh(); break;
        case 14: _t->updateSweep(); break;
        case 15: _t->onMapTileReceived((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 16: _t->updateTrackHistory(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PPIDisplayWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PPIDisplayWidget::trackSelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PPIDisplayWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PPIDisplayWidget::trackDoubleClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PPIDisplayWidget::*)(const GeoPosition & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PPIDisplayWidget::mapClicked)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PPIDisplayWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PPIDisplayWidget::rangeScaleChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PPIDisplayWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PPIDisplayWidget::sweepAngleChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PPIDisplayWidget::*)(PPIDisplayMode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PPIDisplayWidget::displayModeChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PPIDisplayWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->sweepAngle(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->rangeScale(); break;
        case 2: *reinterpret_cast< PPIDisplayMode*>(_v) = _t->displayMode(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PPIDisplayWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setRangeScale(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setDisplayMode(*reinterpret_cast< PPIDisplayMode*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject CounterUAS::PPIDisplayWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CounterUAS__PPIDisplayWidget.data,
    qt_meta_data_CounterUAS__PPIDisplayWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CounterUAS::PPIDisplayWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CounterUAS::PPIDisplayWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CounterUAS__PPIDisplayWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CounterUAS::PPIDisplayWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CounterUAS::PPIDisplayWidget::trackSelected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CounterUAS::PPIDisplayWidget::trackDoubleClicked(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CounterUAS::PPIDisplayWidget::mapClicked(const GeoPosition & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CounterUAS::PPIDisplayWidget::rangeScaleChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CounterUAS::PPIDisplayWidget::sweepAngleChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CounterUAS::PPIDisplayWidget::displayModeChanged(PPIDisplayMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
