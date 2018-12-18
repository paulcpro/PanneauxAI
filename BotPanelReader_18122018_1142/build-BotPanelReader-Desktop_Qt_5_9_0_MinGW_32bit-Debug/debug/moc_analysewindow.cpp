/****************************************************************************
** Meta object code from reading C++ file 'analysewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BotPanelReader/analysewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'analysewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_analyseWindow_t {
    QByteArrayData data[8];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_analyseWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_analyseWindow_t qt_meta_stringdata_analyseWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "analyseWindow"
QT_MOC_LITERAL(1, 14, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(4, 63, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(5, 87, 26), // "on_checkBox_4_stateChanged"
QT_MOC_LITERAL(6, 114, 4), // "arg1"
QT_MOC_LITERAL(7, 119, 21) // "on_checkBox_4_clicked"

    },
    "analyseWindow\0on_pushButton_3_clicked\0"
    "\0on_pushButton_2_clicked\0"
    "on_pushButton_4_clicked\0"
    "on_checkBox_4_stateChanged\0arg1\0"
    "on_checkBox_4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_analyseWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

       0        // eod
};

void analyseWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        analyseWindow *_t = static_cast<analyseWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_3_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->on_pushButton_4_clicked(); break;
        case 3: _t->on_checkBox_4_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_checkBox_4_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject analyseWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_analyseWindow.data,
      qt_meta_data_analyseWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *analyseWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *analyseWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_analyseWindow.stringdata0))
        return static_cast<void*>(const_cast< analyseWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int analyseWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
