/****************************************************************************
** Meta object code from reading C++ file 'UI_HistoricalInformation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UI_HistoricalInformation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI_HistoricalInformation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI_HistoricalInformation_t {
    QByteArrayData data[8];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UI_HistoricalInformation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UI_HistoricalInformation_t qt_meta_stringdata_UI_HistoricalInformation = {
    {
QT_MOC_LITERAL(0, 0, 24), // "UI_HistoricalInformation"
QT_MOC_LITERAL(1, 25, 16), // "SigSwitchSection"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 6), // "nIndex"
QT_MOC_LITERAL(4, 50, 19), // "qstrHistoryFilePath"
QT_MOC_LITERAL(5, 70, 19), // "SigCleanHistoryFile"
QT_MOC_LITERAL(6, 90, 17), // "SlotSwitchSection"
QT_MOC_LITERAL(7, 108, 20) // "SlotCleanHistoryFile"

    },
    "UI_HistoricalInformation\0SigSwitchSection\0"
    "\0nIndex\0qstrHistoryFilePath\0"
    "SigCleanHistoryFile\0SlotSwitchSection\0"
    "SlotCleanHistoryFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI_HistoricalInformation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   42,    2, 0x09 /* Protected */,
       7,    0,   45,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void UI_HistoricalInformation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UI_HistoricalInformation *_t = static_cast<UI_HistoricalInformation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigSwitchSection((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->SigCleanHistoryFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->SlotSwitchSection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SlotCleanHistoryFile(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UI_HistoricalInformation::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UI_HistoricalInformation::SigSwitchSection)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UI_HistoricalInformation::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UI_HistoricalInformation::SigCleanHistoryFile)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject UI_HistoricalInformation::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UI_HistoricalInformation.data,
      qt_meta_data_UI_HistoricalInformation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UI_HistoricalInformation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI_HistoricalInformation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UI_HistoricalInformation.stringdata0))
        return static_cast<void*>(const_cast< UI_HistoricalInformation*>(this));
    if (!strcmp(_clname, "UI_InterfaceBase"))
        return static_cast< UI_InterfaceBase*>(const_cast< UI_HistoricalInformation*>(this));
    return QWidget::qt_metacast(_clname);
}

int UI_HistoricalInformation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void UI_HistoricalInformation::SigSwitchSection(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UI_HistoricalInformation::SigCleanHistoryFile(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
