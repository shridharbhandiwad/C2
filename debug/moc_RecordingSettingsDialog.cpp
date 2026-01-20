/****************************************************************************
** Meta object code from reading C++ file 'RecordingSettingsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/ui/dialogs/RecordingSettingsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RecordingSettingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CounterUAS__RecordingSettingsDialog_t {
    QByteArrayData data[12];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CounterUAS__RecordingSettingsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CounterUAS__RecordingSettingsDialog_t qt_meta_stringdata_CounterUAS__RecordingSettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 35), // "CounterUAS::RecordingSettings..."
QT_MOC_LITERAL(1, 36, 15), // "settingsChanged"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 17), // "RecordingSettings"
QT_MOC_LITERAL(4, 71, 8), // "settings"
QT_MOC_LITERAL(5, 80, 17), // "startAllRecording"
QT_MOC_LITERAL(6, 98, 16), // "stopAllRecording"
QT_MOC_LITERAL(7, 115, 12), // "onBrowsePath"
QT_MOC_LITERAL(8, 128, 7), // "onApply"
QT_MOC_LITERAL(9, 136, 10), // "onStartAll"
QT_MOC_LITERAL(10, 147, 9), // "onStopAll"
QT_MOC_LITERAL(11, 157, 14) // "onTakeSnapshot"

    },
    "CounterUAS::RecordingSettingsDialog\0"
    "settingsChanged\0\0RecordingSettings\0"
    "settings\0startAllRecording\0stopAllRecording\0"
    "onBrowsePath\0onApply\0onStartAll\0"
    "onStopAll\0onTakeSnapshot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CounterUAS__RecordingSettingsDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,
      10,    0,   62,    2, 0x08 /* Private */,
      11,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CounterUAS::RecordingSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RecordingSettingsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->settingsChanged((*reinterpret_cast< const RecordingSettings(*)>(_a[1]))); break;
        case 1: _t->startAllRecording(); break;
        case 2: _t->stopAllRecording(); break;
        case 3: _t->onBrowsePath(); break;
        case 4: _t->onApply(); break;
        case 5: _t->onStartAll(); break;
        case 6: _t->onStopAll(); break;
        case 7: _t->onTakeSnapshot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RecordingSettingsDialog::*)(const RecordingSettings & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordingSettingsDialog::settingsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RecordingSettingsDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordingSettingsDialog::startAllRecording)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RecordingSettingsDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordingSettingsDialog::stopAllRecording)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CounterUAS::RecordingSettingsDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CounterUAS__RecordingSettingsDialog.data,
    qt_meta_data_CounterUAS__RecordingSettingsDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CounterUAS::RecordingSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CounterUAS::RecordingSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CounterUAS__RecordingSettingsDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CounterUAS::RecordingSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CounterUAS::RecordingSettingsDialog::settingsChanged(const RecordingSettings & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CounterUAS::RecordingSettingsDialog::startAllRecording()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CounterUAS::RecordingSettingsDialog::stopAllRecording()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
