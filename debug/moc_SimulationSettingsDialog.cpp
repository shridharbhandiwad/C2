/****************************************************************************
** Meta object code from reading C++ file 'SimulationSettingsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/ui/dialogs/SimulationSettingsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimulationSettingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CounterUAS__SimulationSettingsDialog_t {
    QByteArrayData data[21];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CounterUAS__SimulationSettingsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CounterUAS__SimulationSettingsDialog_t qt_meta_stringdata_CounterUAS__SimulationSettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 36), // "CounterUAS::SimulationSetting..."
QT_MOC_LITERAL(1, 37, 15), // "scenarioChanged"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 18), // "SimulationScenario"
QT_MOC_LITERAL(4, 73, 8), // "scenario"
QT_MOC_LITERAL(5, 82, 14), // "targetInjected"
QT_MOC_LITERAL(6, 97, 8), // "targetId"
QT_MOC_LITERAL(7, 106, 18), // "onScenarioSelected"
QT_MOC_LITERAL(8, 125, 5), // "index"
QT_MOC_LITERAL(9, 131, 7), // "onApply"
QT_MOC_LITERAL(10, 139, 12), // "onLoadCustom"
QT_MOC_LITERAL(11, 152, 12), // "onSaveCustom"
QT_MOC_LITERAL(12, 165, 13), // "updatePreview"
QT_MOC_LITERAL(13, 179, 14), // "onInjectTarget"
QT_MOC_LITERAL(14, 194, 14), // "onClearTargets"
QT_MOC_LITERAL(15, 209, 18), // "onAutoSpawnToggled"
QT_MOC_LITERAL(16, 228, 7), // "enabled"
QT_MOC_LITERAL(17, 236, 16), // "onTargetInjected"
QT_MOC_LITERAL(18, 253, 11), // "GeoPosition"
QT_MOC_LITERAL(19, 265, 8), // "position"
QT_MOC_LITERAL(20, 274, 15) // "onTargetRemoved"

    },
    "CounterUAS::SimulationSettingsDialog\0"
    "scenarioChanged\0\0SimulationScenario\0"
    "scenario\0targetInjected\0targetId\0"
    "onScenarioSelected\0index\0onApply\0"
    "onLoadCustom\0onSaveCustom\0updatePreview\0"
    "onInjectTarget\0onClearTargets\0"
    "onAutoSpawnToggled\0enabled\0onTargetInjected\0"
    "GeoPosition\0position\0onTargetRemoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CounterUAS__SimulationSettingsDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   80,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    1,   89,    2, 0x08 /* Private */,
      17,    2,   92,    2, 0x08 /* Private */,
      20,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 18,    6,   19,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void CounterUAS::SimulationSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimulationSettingsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->scenarioChanged((*reinterpret_cast< const SimulationScenario(*)>(_a[1]))); break;
        case 1: _t->targetInjected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onScenarioSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onApply(); break;
        case 4: _t->onLoadCustom(); break;
        case 5: _t->onSaveCustom(); break;
        case 6: _t->updatePreview(); break;
        case 7: _t->onInjectTarget(); break;
        case 8: _t->onClearTargets(); break;
        case 9: _t->onAutoSpawnToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->onTargetInjected((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const GeoPosition(*)>(_a[2]))); break;
        case 11: _t->onTargetRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SimulationSettingsDialog::*)(const SimulationScenario & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulationSettingsDialog::scenarioChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SimulationSettingsDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulationSettingsDialog::targetInjected)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CounterUAS::SimulationSettingsDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CounterUAS__SimulationSettingsDialog.data,
    qt_meta_data_CounterUAS__SimulationSettingsDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CounterUAS::SimulationSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CounterUAS::SimulationSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CounterUAS__SimulationSettingsDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CounterUAS::SimulationSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void CounterUAS::SimulationSettingsDialog::scenarioChanged(const SimulationScenario & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CounterUAS::SimulationSettingsDialog::targetInjected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
