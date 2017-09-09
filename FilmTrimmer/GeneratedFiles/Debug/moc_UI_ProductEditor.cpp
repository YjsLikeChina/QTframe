/****************************************************************************
** Meta object code from reading C++ file 'UI_ProductEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UI_ProductEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI_ProductEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI_ProductEditor_t {
    QByteArrayData data[17];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UI_ProductEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UI_ProductEditor_t qt_meta_stringdata_UI_ProductEditor = {
    {
QT_MOC_LITERAL(0, 0, 16), // "UI_ProductEditor"
QT_MOC_LITERAL(1, 17, 21), // "SlotSetCurrentPackage"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 15), // "SlotCopyPackage"
QT_MOC_LITERAL(4, 56, 17), // "SlotDeletePackage"
QT_MOC_LITERAL(5, 74, 14), // "SlotNewPackage"
QT_MOC_LITERAL(6, 89, 15), // "SlotSavePackage"
QT_MOC_LITERAL(7, 105, 18), // "SlotAddPackageStep"
QT_MOC_LITERAL(8, 124, 17), // "SlotSwitchPackage"
QT_MOC_LITERAL(9, 142, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(10, 159, 4), // "item"
QT_MOC_LITERAL(11, 164, 14), // "SlotDeleteStep"
QT_MOC_LITERAL(12, 179, 7), // "nButton"
QT_MOC_LITERAL(13, 187, 19), // "SlotItemDoubleClick"
QT_MOC_LITERAL(14, 207, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(15, 224, 7), // "nColumn"
QT_MOC_LITERAL(16, 232, 15) // "SlotItemChanged"

    },
    "UI_ProductEditor\0SlotSetCurrentPackage\0"
    "\0SlotCopyPackage\0SlotDeletePackage\0"
    "SlotNewPackage\0SlotSavePackage\0"
    "SlotAddPackageStep\0SlotSwitchPackage\0"
    "QListWidgetItem*\0item\0SlotDeleteStep\0"
    "nButton\0SlotItemDoubleClick\0"
    "QTreeWidgetItem*\0nColumn\0SlotItemChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI_ProductEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x09 /* Protected */,
       3,    0,   65,    2, 0x09 /* Protected */,
       4,    0,   66,    2, 0x09 /* Protected */,
       5,    0,   67,    2, 0x09 /* Protected */,
       6,    0,   68,    2, 0x09 /* Protected */,
       7,    0,   69,    2, 0x09 /* Protected */,
       8,    1,   70,    2, 0x09 /* Protected */,
      11,    1,   73,    2, 0x09 /* Protected */,
      13,    2,   76,    2, 0x09 /* Protected */,
      16,    0,   81,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,   10,   15,
    QMetaType::Void,

       0        // eod
};

void UI_ProductEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UI_ProductEditor *_t = static_cast<UI_ProductEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotSetCurrentPackage(); break;
        case 1: _t->SlotCopyPackage(); break;
        case 2: _t->SlotDeletePackage(); break;
        case 3: _t->SlotNewPackage(); break;
        case 4: _t->SlotSavePackage(); break;
        case 5: _t->SlotAddPackageStep(); break;
        case 6: _t->SlotSwitchPackage((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->SlotDeleteStep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->SlotItemDoubleClick((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->SlotItemChanged(); break;
        default: ;
        }
    }
}

const QMetaObject UI_ProductEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UI_ProductEditor.data,
      qt_meta_data_UI_ProductEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UI_ProductEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI_ProductEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UI_ProductEditor.stringdata0))
        return static_cast<void*>(const_cast< UI_ProductEditor*>(this));
    if (!strcmp(_clname, "UI_InterfaceBase"))
        return static_cast< UI_InterfaceBase*>(const_cast< UI_ProductEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int UI_ProductEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
