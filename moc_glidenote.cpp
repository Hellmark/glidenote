/****************************************************************************
** Meta object code from reading C++ file 'glidenote.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "glidenote.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glidenote.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Glidenote[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      18,   10,   10,   10, 0x08,
      25,   10,   10,   10, 0x08,
      32,   10,   10,   10, 0x08,
      40,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Glidenote[] = {
    "Glidenote\0\0open()\0save()\0anim()\0about()\0"
    "scale()\0"
};

void Glidenote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Glidenote *_t = static_cast<Glidenote *>(_o);
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->save(); break;
        case 2: _t->anim(); break;
        case 3: _t->about(); break;
        case 4: _t->scale(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Glidenote::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Glidenote::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Glidenote,
      qt_meta_data_Glidenote, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Glidenote::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Glidenote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Glidenote::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Glidenote))
        return static_cast<void*>(const_cast< Glidenote*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Glidenote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
