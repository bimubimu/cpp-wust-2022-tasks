/****************************************************************************
** Meta object code from reading C++ file 'toolbar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HotelManagement/toolbar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ToolBar_t {
    QByteArrayData data[6];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ToolBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ToolBar_t qt_meta_stringdata_ToolBar = {
    {
QT_MOC_LITERAL(0, 0, 7), // "ToolBar"
QT_MOC_LITERAL(1, 8, 12), // "priceClicked"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "roomClicked"
QT_MOC_LITERAL(4, 34, 13), // "registClicked"
QT_MOC_LITERAL(5, 48, 15) // "employeeClicked"

    },
    "ToolBar\0priceClicked\0\0roomClicked\0"
    "registClicked\0employeeClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ToolBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ToolBar *_t = static_cast<ToolBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->priceClicked(); break;
        case 1: _t->roomClicked(); break;
        case 2: _t->registClicked(); break;
        case 3: _t->employeeClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ToolBar::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToolBar::priceClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ToolBar::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToolBar::roomClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ToolBar::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToolBar::registClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ToolBar::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ToolBar::employeeClicked)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ToolBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ToolBar.data,
      qt_meta_data_ToolBar,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ToolBar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ToolBar::priceClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ToolBar::roomClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ToolBar::registClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ToolBar::employeeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
