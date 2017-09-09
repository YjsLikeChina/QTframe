/****************************************************************************
** Meta object code from reading C++ file 'UI_FloatingWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UI_FloatingWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI_FloatingWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI_FloatingWindow_t {
    QByteArrayData data[12];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UI_FloatingWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UI_FloatingWindow_t qt_meta_stringdata_UI_FloatingWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "UI_FloatingWindow"
QT_MOC_LITERAL(1, 18, 20), // "SigMachineStatusCtrl"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 17), // "EM_MACHINE_SIGNAL"
QT_MOC_LITERAL(4, 58, 15), // "emMachineStatus"
QT_MOC_LITERAL(5, 74, 16), // "SlotMachineStart"
QT_MOC_LITERAL(6, 91, 15), // "SlotMachineStop"
QT_MOC_LITERAL(7, 107, 16), // "SlotMachineReset"
QT_MOC_LITERAL(8, 124, 16), // "SlotMachineEStop"
QT_MOC_LITERAL(9, 141, 13), // "SlotRunSchema"
QT_MOC_LITERAL(10, 155, 16), // "SlotRunDirection"
QT_MOC_LITERAL(11, 172, 19) // "SlotOnloadDirection"

    },
    "UI_FloatingWindow\0SigMachineStatusCtrl\0"
    "\0EM_MACHINE_SIGNAL\0emMachineStatus\0"
    "SlotMachineStart\0SlotMachineStop\0"
    "SlotMachineReset\0SlotMachineEStop\0"
    "SlotRunSchema\0SlotRunDirection\0"
    "SlotOnloadDirection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI_FloatingWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   57,    2, 0x09 /* Protected */,
       6,    0,   58,    2, 0x09 /* Protected */,
       7,    0,   59,    2, 0x09 /* Protected */,
       8,    0,   60,    2, 0x09 /* Protected */,
       9,    0,   61,    2, 0x09 /* Protected */,
      10,    0,   62,    2, 0x09 /* Protected */,
      11,    0,   63,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UI_FloatingWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UI_FloatingWindow *_t = static_cast<UI_FloatingWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigMachineStatusCtrl((*reinterpret_cast< EM_MACHINE_SIGNAL(*)>(_a[1]))); break;
        case 1: _t->SlotMachineStart(); break;
        case 2: _t->SlotMachineStop(); break;
        case 3: _t->SlotMachineReset(); break;
        case 4: _t->SlotMachineEStop(); break;
        case 5: _t->SlotRunSchema(); break;
        case 6: _t->SlotRunDirection(); break;
        case 7: _t->SlotOnloadDirection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UI_FloatingWindow::*_t)(EM_MACHINE_SIGNAL );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UI_FloatingWindow::SigMachineStatusCtrl)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject UI_FloatingWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UI_FloatingWindow.data,
      qt_meta_data_UI_FloatingWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UI_FloatingWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI_FloatingWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UI_FloatingWindow.stringdata0))
        return static_cast<void*>(const_cast< UI_FloatingWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int UI_FloatingWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void UI_FloatingWindow::SigMachineStatusCtrl(EM_MACHINE_SIGNAL _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
