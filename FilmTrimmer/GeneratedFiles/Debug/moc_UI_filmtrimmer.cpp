/****************************************************************************
** Meta object code from reading C++ file 'UI_filmtrimmer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UI_filmtrimmer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI_filmtrimmer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI_FilmTrimmer_t {
    QByteArrayData data[15];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UI_FilmTrimmer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UI_FilmTrimmer_t qt_meta_stringdata_UI_FilmTrimmer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "UI_FilmTrimmer"
QT_MOC_LITERAL(1, 15, 14), // "SlotSwitchPage"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "nPageItem"
QT_MOC_LITERAL(4, 41, 16), // "SlotMachineStart"
QT_MOC_LITERAL(5, 58, 16), // "SlotMachineReset"
QT_MOC_LITERAL(6, 75, 15), // "SlotMachineStop"
QT_MOC_LITERAL(7, 91, 16), // "SlotMachineEStop"
QT_MOC_LITERAL(8, 108, 13), // "SlotUserLogin"
QT_MOC_LITERAL(9, 122, 18), // "SlotUserTypeUpdata"
QT_MOC_LITERAL(10, 141, 20), // "SlotUpdataSystemtime"
QT_MOC_LITERAL(11, 162, 13), // "SlotSetPutPid"
QT_MOC_LITERAL(12, 176, 13), // "SlotSetGetPid"
QT_MOC_LITERAL(13, 190, 17), // "SlotSetLaserParam"
QT_MOC_LITERAL(14, 208, 5) // "nCard"

    },
    "UI_FilmTrimmer\0SlotSwitchPage\0\0nPageItem\0"
    "SlotMachineStart\0SlotMachineReset\0"
    "SlotMachineStop\0SlotMachineEStop\0"
    "SlotUserLogin\0SlotUserTypeUpdata\0"
    "SlotUpdataSystemtime\0SlotSetPutPid\0"
    "SlotSetGetPid\0SlotSetLaserParam\0nCard"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI_FilmTrimmer[] = {

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
       1,    1,   69,    2, 0x09 /* Protected */,
       4,    0,   72,    2, 0x09 /* Protected */,
       5,    0,   73,    2, 0x09 /* Protected */,
       6,    0,   74,    2, 0x09 /* Protected */,
       7,    0,   75,    2, 0x09 /* Protected */,
       8,    0,   76,    2, 0x09 /* Protected */,
       9,    0,   77,    2, 0x09 /* Protected */,
      10,    0,   78,    2, 0x09 /* Protected */,
      11,    0,   79,    2, 0x09 /* Protected */,
      12,    0,   80,    2, 0x09 /* Protected */,
      13,    1,   81,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void UI_FilmTrimmer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UI_FilmTrimmer *_t = static_cast<UI_FilmTrimmer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotSwitchPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->SlotMachineStart(); break;
        case 2: _t->SlotMachineReset(); break;
        case 3: _t->SlotMachineStop(); break;
        case 4: _t->SlotMachineEStop(); break;
        case 5: _t->SlotUserLogin(); break;
        case 6: _t->SlotUserTypeUpdata(); break;
        case 7: _t->SlotUpdataSystemtime(); break;
        case 8: _t->SlotSetPutPid(); break;
        case 9: _t->SlotSetGetPid(); break;
        case 10: _t->SlotSetLaserParam((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject UI_FilmTrimmer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UI_FilmTrimmer.data,
      qt_meta_data_UI_FilmTrimmer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UI_FilmTrimmer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI_FilmTrimmer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UI_FilmTrimmer.stringdata0))
        return static_cast<void*>(const_cast< UI_FilmTrimmer*>(this));
    if (!strcmp(_clname, "UI_InterfaceBase"))
        return static_cast< UI_InterfaceBase*>(const_cast< UI_FilmTrimmer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UI_FilmTrimmer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
