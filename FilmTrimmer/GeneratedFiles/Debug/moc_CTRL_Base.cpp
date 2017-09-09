/****************************************************************************
** Meta object code from reading C++ file 'CTRL_Base.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CTRL_Base.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CTRL_Base.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CTRL_Base_t {
    QByteArrayData data[5];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CTRL_Base_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CTRL_Base_t qt_meta_stringdata_CTRL_Base = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CTRL_Base"
QT_MOC_LITERAL(1, 10, 18), // "SlotAutoUpdateData"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 20), // "QList<ST_UPDATEDATA>"
QT_MOC_LITERAL(4, 51, 8) // "DataList"

    },
    "CTRL_Base\0SlotAutoUpdateData\0\0"
    "QList<ST_UPDATEDATA>\0DataList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CTRL_Base[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void CTRL_Base::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CTRL_Base *_t = static_cast<CTRL_Base *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotAutoUpdateData((*reinterpret_cast< QList<ST_UPDATEDATA>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CTRL_Base::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CTRL_Base.data,
      qt_meta_data_CTRL_Base,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CTRL_Base::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CTRL_Base::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CTRL_Base.stringdata0))
        return static_cast<void*>(const_cast< CTRL_Base*>(this));
    return QObject::qt_metacast(_clname);
}

int CTRL_Base::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
