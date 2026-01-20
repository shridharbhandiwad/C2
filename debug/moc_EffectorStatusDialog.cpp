/****************************************************************************
** Meta object code from reading C++ file 'EffectorStatusDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/ui/dialogs/EffectorStatusDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EffectorStatusDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CounterUAS__EffectorStatusDialog_t {
    QByteArrayData data[13];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CounterUAS__EffectorStatusDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CounterUAS__EffectorStatusDialog_t qt_meta_stringdata_CounterUAS__EffectorStatusDialog = {
    {
QT_MOC_LITERAL(0, 0, 32), // "CounterUAS::EffectorStatusDialog"
QT_MOC_LITERAL(1, 33, 27), // "effectorInitializeRequested"
QT_MOC_LITERAL(2, 61, 0), // ""
QT_MOC_LITERAL(3, 62, 10), // "effectorId"
QT_MOC_LITERAL(4, 73, 25), // "effectorShutdownRequested"
QT_MOC_LITERAL(5, 99, 22), // "effectorResetRequested"
QT_MOC_LITERAL(6, 122, 13), // "refreshStatus"
QT_MOC_LITERAL(7, 136, 18), // "onEffectorSelected"
QT_MOC_LITERAL(8, 155, 3), // "row"
QT_MOC_LITERAL(9, 159, 12), // "onInitialize"
QT_MOC_LITERAL(10, 172, 10), // "onShutdown"
QT_MOC_LITERAL(11, 183, 7), // "onReset"
QT_MOC_LITERAL(12, 191, 12) // "onTestEngage"

    },
    "CounterUAS::EffectorStatusDialog\0"
    "effectorInitializeRequested\0\0effectorId\0"
    "effectorShutdownRequested\0"
    "effectorResetRequested\0refreshStatus\0"
    "onEffectorSelected\0row\0onInitialize\0"
    "onShutdown\0onReset\0onTestEngage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CounterUAS__EffectorStatusDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   68,    2, 0x08 /* Private */,
       7,    1,   69,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CounterUAS::EffectorStatusDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EffectorStatusDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->effectorInitializeRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->effectorShutdownRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->effectorResetRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->refreshStatus(); break;
        case 4: _t->onEffectorSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onInitialize(); break;
        case 6: _t->onShutdown(); break;
        case 7: _t->onReset(); break;
        case 8: _t->onTestEngage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EffectorStatusDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorStatusDialog::effectorInitializeRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EffectorStatusDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorStatusDialog::effectorShutdownRequested)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EffectorStatusDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EffectorStatusDialog::effectorResetRequested)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CounterUAS::EffectorStatusDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CounterUAS__EffectorStatusDialog.data,
    qt_meta_data_CounterUAS__EffectorStatusDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CounterUAS::EffectorStatusDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CounterUAS::EffectorStatusDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CounterUAS__EffectorStatusDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CounterUAS::EffectorStatusDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CounterUAS::EffectorStatusDialog::effectorInitializeRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CounterUAS::EffectorStatusDialog::effectorShutdownRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CounterUAS::EffectorStatusDialog::effectorResetRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
