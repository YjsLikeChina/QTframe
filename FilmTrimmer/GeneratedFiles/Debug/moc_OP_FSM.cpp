/****************************************************************************
** Meta object code from reading C++ file 'OP_FSM.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../OP_FSM.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OP_FSM.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OP_FSM_t {
    QByteArrayData data[10];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OP_FSM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OP_FSM_t qt_meta_stringdata_OP_FSM = {
    {
QT_MOC_LITERAL(0, 0, 6), // "OP_FSM"
QT_MOC_LITERAL(1, 7, 20), // "SigSetStatusFlagTest"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "strStatusHint"
QT_MOC_LITERAL(4, 43, 11), // "strOperHint"
QT_MOC_LITERAL(5, 55, 24), // "MACHINE_STATUSTOOL_COLOR"
QT_MOC_LITERAL(6, 80, 11), // "AlarmStatus"
QT_MOC_LITERAL(7, 92, 15), // "SlotMachineCtrl"
QT_MOC_LITERAL(8, 108, 17), // "EM_MACHINE_SIGNAL"
QT_MOC_LITERAL(9, 126, 7) // "emEvent"

    },
    "OP_FSM\0SigSetStatusFlagTest\0\0strStatusHint\0"
    "strOperHint\0MACHINE_STATUSTOOL_COLOR\0"
    "AlarmStatus\0SlotMachineCtrl\0"
    "EM_MACHINE_SIGNAL\0emEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OP_FSM[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   31,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 5,    3,    4,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void OP_FSM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OP_FSM *_t = static_cast<OP_FSM *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigSetStatusFlagTest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< MACHINE_STATUSTOOL_COLOR(*)>(_a[3]))); break;
        case 1: _t->SlotMachineCtrl((*reinterpret_cast< EM_MACHINE_SIGNAL(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OP_FSM::*_t)(QString , QString , MACHINE_STATUSTOOL_COLOR );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OP_FSM::SigSetStatusFlagTest)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject OP_FSM::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OP_FSM.data,
      qt_meta_data_OP_FSM,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OP_FSM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OP_FSM::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OP_FSM.stringdata0))
        return static_cast<void*>(const_cast< OP_FSM*>(this));
    return QObject::qt_metacast(_clname);
}

int OP_FSM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void OP_FSM::SigSetStatusFlagTest(QString _t1, QString _t2, MACHINE_STATUSTOOL_COLOR _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
