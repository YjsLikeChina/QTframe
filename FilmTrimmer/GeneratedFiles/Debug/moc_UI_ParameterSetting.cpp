/****************************************************************************
** Meta object code from reading C++ file 'UI_ParameterSetting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UI_ParameterSetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI_ParameterSetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI_ParameterSetting_t {
    QByteArrayData data[8];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UI_ParameterSetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UI_ParameterSetting_t qt_meta_stringdata_UI_ParameterSetting = {
    {
QT_MOC_LITERAL(0, 0, 19), // "UI_ParameterSetting"
QT_MOC_LITERAL(1, 20, 14), // "SlotParameSave"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 19), // "SlotBoolItemChanged"
QT_MOC_LITERAL(4, 56, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 73, 4), // "item"
QT_MOC_LITERAL(6, 78, 19), // "SlotDataItemChanged"
QT_MOC_LITERAL(7, 98, 21) // "SlotLaserSoftwareShow"

    },
    "UI_ParameterSetting\0SlotParameSave\0\0"
    "SlotBoolItemChanged\0QTreeWidgetItem*\0"
    "item\0SlotDataItemChanged\0SlotLaserSoftwareShow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI_ParameterSetting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x09 /* Protected */,
       3,    2,   35,    2, 0x09 /* Protected */,
       6,    0,   40,    2, 0x09 /* Protected */,
       7,    0,   41,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UI_ParameterSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UI_ParameterSetting *_t = static_cast<UI_ParameterSetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotParameSave(); break;
        case 1: _t->SlotBoolItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->SlotDataItemChanged(); break;
        case 3: _t->SlotLaserSoftwareShow(); break;
        default: ;
        }
    }
}

const QMetaObject UI_ParameterSetting::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UI_ParameterSetting.data,
      qt_meta_data_UI_ParameterSetting,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UI_ParameterSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI_ParameterSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UI_ParameterSetting.stringdata0))
        return static_cast<void*>(const_cast< UI_ParameterSetting*>(this));
    if (!strcmp(_clname, "UI_InterfaceBase"))
        return static_cast< UI_InterfaceBase*>(const_cast< UI_ParameterSetting*>(this));
    return QWidget::qt_metacast(_clname);
}

int UI_ParameterSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
