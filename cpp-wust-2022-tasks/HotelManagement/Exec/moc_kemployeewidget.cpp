/****************************************************************************
** Meta object code from reading C++ file 'kemployeewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HotelManagement/hotelWidget/kemployeewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kemployeewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KEmployeeWidget_t {
    QByteArrayData data[11];
    char stringdata0[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KEmployeeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KEmployeeWidget_t qt_meta_stringdata_KEmployeeWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "KEmployeeWidget"
QT_MOC_LITERAL(1, 16, 29), // "on_pushButtonRegister_clicked"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 34), // "on_pushButtonRegisterClean_cl..."
QT_MOC_LITERAL(4, 82, 32), // "on_pushButtonUpdateQuery_clicked"
QT_MOC_LITERAL(5, 115, 37), // "on_comboBoxUpdate_currentInde..."
QT_MOC_LITERAL(6, 153, 5), // "index"
QT_MOC_LITERAL(7, 159, 27), // "on_pushButtonUpdate_clicked"
QT_MOC_LITERAL(8, 187, 32), // "on_pushButtonUpdateClean_clicked"
QT_MOC_LITERAL(9, 220, 27), // "on_pushButtonDelete_clicked"
QT_MOC_LITERAL(10, 248, 27) // "on_tabWidget_currentChanged"

    },
    "KEmployeeWidget\0on_pushButtonRegister_clicked\0"
    "\0on_pushButtonRegisterClean_clicked\0"
    "on_pushButtonUpdateQuery_clicked\0"
    "on_comboBoxUpdate_currentIndexChanged\0"
    "index\0on_pushButtonUpdate_clicked\0"
    "on_pushButtonUpdateClean_clicked\0"
    "on_pushButtonDelete_clicked\0"
    "on_tabWidget_currentChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KEmployeeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    1,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void KEmployeeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KEmployeeWidget *_t = static_cast<KEmployeeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonRegister_clicked(); break;
        case 1: _t->on_pushButtonRegisterClean_clicked(); break;
        case 2: _t->on_pushButtonUpdateQuery_clicked(); break;
        case 3: _t->on_comboBoxUpdate_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_pushButtonUpdate_clicked(); break;
        case 5: _t->on_pushButtonUpdateClean_clicked(); break;
        case 6: _t->on_pushButtonDelete_clicked(); break;
        case 7: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject KEmployeeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_KEmployeeWidget.data,
      qt_meta_data_KEmployeeWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *KEmployeeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KEmployeeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KEmployeeWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int KEmployeeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
