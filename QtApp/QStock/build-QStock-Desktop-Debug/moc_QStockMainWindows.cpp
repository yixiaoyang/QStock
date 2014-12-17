/****************************************************************************
** Meta object code from reading C++ file 'QStockMainWindows.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QStock/QStockMainWindows.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QStockMainWindows.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QStockMainWindows[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      50,   18,   18,   18, 0x08,
      76,   74,   18,   18, 0x08,
     111,   18,   18,   18, 0x08,
     142,   18,   18,   18, 0x08,
     164,   18,   18,   18, 0x08,
     182,   18,   18,   18, 0x08,
     209,   18,   18,   18, 0x08,
     233,   18,   18,   18, 0x08,
     257,   18,   18,   18, 0x08,
     280,   18,   18,   18, 0x08,
     323,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QStockMainWindows[] = {
    "QStockMainWindows\0\0on_pushButtonAddCode_clicked()\0"
    "slot_sinaHttpDone(bool)\0,\0"
    "slot_sinaDataReadProgress(int,int)\0"
    "slot_sinaReadyRead(QByteArray)\0"
    "slot_sysTimeFreshed()\0slot_idbChanged()\0"
    "on_actionAbout_triggered()\0"
    "slot_runtimeDelAction()\0slot_runtimeTopAction()\0"
    "slot_runtimeHlAction()\0"
    "slot_tblCustomContextMenuRequested(QPoint)\0"
    "on_action_SaveWatchList_triggered()\0"
};

void QStockMainWindows::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QStockMainWindows *_t = static_cast<QStockMainWindows *>(_o);
        switch (_id) {
        case 0: _t->on_pushButtonAddCode_clicked(); break;
        case 1: _t->slot_sinaHttpDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slot_sinaDataReadProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slot_sinaReadyRead((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->slot_sysTimeFreshed(); break;
        case 5: _t->slot_idbChanged(); break;
        case 6: _t->on_actionAbout_triggered(); break;
        case 7: _t->slot_runtimeDelAction(); break;
        case 8: _t->slot_runtimeTopAction(); break;
        case 9: _t->slot_runtimeHlAction(); break;
        case 10: _t->slot_tblCustomContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 11: _t->on_action_SaveWatchList_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QStockMainWindows::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QStockMainWindows::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QStockMainWindows,
      qt_meta_data_QStockMainWindows, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QStockMainWindows::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QStockMainWindows::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QStockMainWindows::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QStockMainWindows))
        return static_cast<void*>(const_cast< QStockMainWindows*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QStockMainWindows::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
