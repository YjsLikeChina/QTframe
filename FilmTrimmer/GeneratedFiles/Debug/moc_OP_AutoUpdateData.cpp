/****************************************************************************
** Meta object code from reading C++ file 'OP_AutoUpdateData.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../OP_AutoUpdateData.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OP_AutoUpdateData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OP_AutoUpdateData_t {
    QByteArrayData data[14];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OP_AutoUpdateData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OP_AutoUpdateData_t qt_meta_stringdata_OP_AutoUpdateData = {
    {
QT_MOC_LITERAL(0, 0, 17), // "OP_AutoUpdateData"
QT_MOC_LITERAL(1, 18, 17), // "SigAutoProduction"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 20), // "QList<ST_UPDATEDATA>"
QT_MOC_LITERAL(4, 58, 10), // "SigIODebug"
QT_MOC_LITERAL(5, 69, 13), // "SigMotorDebug"
QT_MOC_LITERAL(6, 83, 19), // "SigParameterSetting"
QT_MOC_LITERAL(7, 103, 16), // "SigProductEditor"
QT_MOC_LITERAL(8, 120, 24), // "SigHistoricalInformation"
QT_MOC_LITERAL(9, 145, 15), // "SigMachineAlarm"
QT_MOC_LITERAL(10, 161, 8), // "qslAlarm"
QT_MOC_LITERAL(11, 170, 8), // "qslError"
QT_MOC_LITERAL(12, 179, 15), // "SigMachineModel"
QT_MOC_LITERAL(13, 195, 5) // "bFlag"

    },
    "OP_AutoUpdateData\0SigAutoProduction\0"
    "\0QList<ST_UPDATEDATA>\0SigIODebug\0"
    "SigMotorDebug\0SigParameterSetting\0"
    "SigProductEditor\0SigHistoricalInformation\0"
    "SigMachineAlarm\0qslAlarm\0qslError\0"
    "SigMachineModel\0bFlag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OP_AutoUpdateData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       5,    1,   60,    2, 0x06 /* Public */,
       6,    1,   63,    2, 0x06 /* Public */,
       7,    1,   66,    2, 0x06 /* Public */,
       8,    1,   69,    2, 0x06 /* Public */,
       9,    2,   72,    2, 0x06 /* Public */,
      12,    1,   77,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void OP_AutoUpdateData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OP_AutoUpdateData *_t = static_cast<OP_AutoUpdateData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigAutoProduction((*reinterpret_cast< QList<ST_UPDATEDATA>(*)>(_a[1]))); break;
        case 1: _t->SigIODebug((*reinterpret_cast< QList<ST_UPDATEDATA>(*)>(_a[1]))); break;
        case 2: _t->SigMotorDebug((*reinterpret_cast< QList<ST_UPDATEDATA>(*)>(_a[1]))); break;
        case 3: _t->SigParameterSetting((*reinterpret_cast< QList<ST_UPDATEDATA>(*)>(_a[1]))); break;
        case 4: _t->SigProductEditor((*reinterpret_cast< QList<ST_UPDATEDATA>(*)>(_a[1]))); break;
        case 5: _t->SigHistoricalInformation((*reinterpret_cast< QList<ST_UPDATEDATA>(*)>(_a[1]))); break;
        case 6: _t->SigMachineAlarm((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->SigMachineModel((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OP_AutoUpdateData::*_t)(QList<ST_UPDATEDATA> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OP_AutoUpdateData::SigAutoProduction)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (OP_AutoUpdateData::*_t)(QList<ST_UPDATEDATA> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OP_AutoUpdateData::SigIODebug)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (OP_AutoUpdateData::*_t)(QList<ST_UPDATEDATA> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OP_AutoUpdateData::SigMotorDebug)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (OP_AutoUpdateData::*_t)(QList<ST_UPDATEDATA> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OP_AutoUpdateData::SigParameterSetting)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (OP_AutoUpdateData::*_t)(QList<ST_UPDATEDATA> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OP_AutoUpdateData::SigProductEditor)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (OP_AutoUpdateData::*_t)(QList<ST_UPDATEDATA> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OP_AutoUpdateData::SigHistoricalInformation)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (OP_AutoUpdateData::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OP_AutoUpdateData::SigMachineAlarm)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (OP_AutoUpdateData::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OP_AutoUpdateData::SigMachineModel)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject OP_AutoUpdateData::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_OP_AutoUpdateData.data,
      qt_meta_data_OP_AutoUpdateData,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OP_AutoUpdateData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OP_AutoUpdateData::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OP_AutoUpdateData.stringdata0))
        return static_cast<void*>(const_cast< OP_AutoUpdateData*>(this));
    return QThread::qt_metacast(_clname);
}

int OP_AutoUpdateData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void OP_AutoUpdateData::SigAutoProduction(QList<ST_UPDATEDATA> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OP_AutoUpdateData::SigIODebug(QList<ST_UPDATEDATA> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OP_AutoUpdateData::SigMotorDebug(QList<ST_UPDATEDATA> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void OP_AutoUpdateData::SigParameterSetting(QList<ST_UPDATEDATA> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void OP_AutoUpdateData::SigProductEditor(QList<ST_UPDATEDATA> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void OP_AutoUpdateData::SigHistoricalInformation(QList<ST_UPDATEDATA> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void OP_AutoUpdateData::SigMachineAlarm(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void OP_AutoUpdateData::SigMachineModel(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
