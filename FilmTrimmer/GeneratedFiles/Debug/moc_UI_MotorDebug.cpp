/****************************************************************************
** Meta object code from reading C++ file 'UI_MotorDebug.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UI_MotorDebug.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI_MotorDebug.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI_MotorDebug_t {
    QByteArrayData data[14];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UI_MotorDebug_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UI_MotorDebug_t qt_meta_stringdata_UI_MotorDebug = {
    {
QT_MOC_LITERAL(0, 0, 13), // "UI_MotorDebug"
QT_MOC_LITERAL(1, 14, 8), // "SlotSave"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "SlotAbsMove"
QT_MOC_LITERAL(4, 36, 20), // "SlotAdvanceMovePress"
QT_MOC_LITERAL(5, 57, 22), // "SlotAdvanceMoveRelease"
QT_MOC_LITERAL(6, 80, 20), // "SlotRetreatMovePress"
QT_MOC_LITERAL(7, 101, 22), // "SlotRetreatMoveRelease"
QT_MOC_LITERAL(8, 124, 12), // "SlotGotoHome"
QT_MOC_LITERAL(9, 137, 10), // "SlotEnable"
QT_MOC_LITERAL(10, 148, 8), // "SlotStop"
QT_MOC_LITERAL(11, 157, 14), // "SlotCleanAlarm"
QT_MOC_LITERAL(12, 172, 14), // "SlotSwitchAxis"
QT_MOC_LITERAL(13, 187, 5) // "nAxis"

    },
    "UI_MotorDebug\0SlotSave\0\0SlotAbsMove\0"
    "SlotAdvanceMovePress\0SlotAdvanceMoveRelease\0"
    "SlotRetreatMovePress\0SlotRetreatMoveRelease\0"
    "SlotGotoHome\0SlotEnable\0SlotStop\0"
    "SlotCleanAlarm\0SlotSwitchAxis\0nAxis"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI_MotorDebug[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x09 /* Protected */,
       3,    0,   70,    2, 0x09 /* Protected */,
       4,    0,   71,    2, 0x09 /* Protected */,
       5,    0,   72,    2, 0x09 /* Protected */,
       6,    0,   73,    2, 0x09 /* Protected */,
       7,    0,   74,    2, 0x09 /* Protected */,
       8,    0,   75,    2, 0x09 /* Protected */,
       9,    0,   76,    2, 0x09 /* Protected */,
      10,    0,   77,    2, 0x09 /* Protected */,
      11,    0,   78,    2, 0x09 /* Protected */,
      12,    1,   79,    2, 0x09 /* Protected */,

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
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void UI_MotorDebug::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UI_MotorDebug *_t = static_cast<UI_MotorDebug *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotSave(); break;
        case 1: _t->SlotAbsMove(); break;
        case 2: _t->SlotAdvanceMovePress(); break;
        case 3: _t->SlotAdvanceMoveRelease(); break;
        case 4: _t->SlotRetreatMovePress(); break;
        case 5: _t->SlotRetreatMoveRelease(); break;
        case 6: _t->SlotGotoHome(); break;
        case 7: _t->SlotEnable(); break;
        case 8: _t->SlotStop(); break;
        case 9: _t->SlotCleanAlarm(); break;
        case 10: _t->SlotSwitchAxis((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject UI_MotorDebug::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UI_MotorDebug.data,
      qt_meta_data_UI_MotorDebug,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UI_MotorDebug::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI_MotorDebug::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UI_MotorDebug.stringdata0))
        return static_cast<void*>(const_cast< UI_MotorDebug*>(this));
    if (!strcmp(_clname, "UI_InterfaceBase"))
        return static_cast< UI_InterfaceBase*>(const_cast< UI_MotorDebug*>(this));
    return QWidget::qt_metacast(_clname);
}

int UI_MotorDebug::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
