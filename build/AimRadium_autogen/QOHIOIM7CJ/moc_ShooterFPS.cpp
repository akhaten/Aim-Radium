/****************************************************************************
** Meta object code from reading C++ file 'ShooterFPS.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/FPS/ShooterFPS.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShooterFPS.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ra__Gui__ShooterFPS_t {
    const uint offsetsAndSize[22];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Ra__Gui__ShooterFPS_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Ra__Gui__ShooterFPS_t qt_meta_stringdata_Ra__Gui__ShooterFPS = {
    {
QT_MOC_LITERAL(0, 19), // "Ra::Gui::ShooterFPS"
QT_MOC_LITERAL(20, 8), // "fitScene"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 10), // "Core::Aabb"
QT_MOC_LITERAL(41, 4), // "aabb"
QT_MOC_LITERAL(46, 17), // "setCameraPosition"
QT_MOC_LITERAL(64, 13), // "Core::Vector3"
QT_MOC_LITERAL(78, 8), // "position"
QT_MOC_LITERAL(87, 15), // "setCameraTarget"
QT_MOC_LITERAL(103, 6), // "target"
QT_MOC_LITERAL(110, 11) // "resetCamera"

    },
    "Ra::Gui::ShooterFPS\0fitScene\0\0Core::Aabb\0"
    "aabb\0setCameraPosition\0Core::Vector3\0"
    "position\0setCameraTarget\0target\0"
    "resetCamera"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ra__Gui__ShooterFPS[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x0a,    1 /* Public */,
       5,    1,   41,    2, 0x0a,    3 /* Public */,
       8,    1,   44,    2, 0x0a,    5 /* Public */,
      10,    0,   47,    2, 0x0a,    7 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    9,
    QMetaType::Void,

       0        // eod
};

void Ra::Gui::ShooterFPS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShooterFPS *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fitScene((*reinterpret_cast< std::add_pointer_t<Core::Aabb>>(_a[1]))); break;
        case 1: _t->setCameraPosition((*reinterpret_cast< std::add_pointer_t<Core::Vector3>>(_a[1]))); break;
        case 2: _t->setCameraTarget((*reinterpret_cast< std::add_pointer_t<Core::Vector3>>(_a[1]))); break;
        case 3: _t->resetCamera(); break;
        default: ;
        }
    }
}

const QMetaObject Ra::Gui::ShooterFPS::staticMetaObject = { {
    QMetaObject::SuperData::link<Ra::Gui::CameraManipulator::staticMetaObject>(),
    qt_meta_stringdata_Ra__Gui__ShooterFPS.offsetsAndSize,
    qt_meta_data_Ra__Gui__ShooterFPS,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Ra__Gui__ShooterFPS_t
, QtPrivate::TypeAndForceComplete<ShooterFPS, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Core::Aabb &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Core::Vector3 &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const Core::Vector3 &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Ra::Gui::ShooterFPS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ra::Gui::ShooterFPS::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ra__Gui__ShooterFPS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "KeyMappingManageable<ShooterFPS>"))
        return static_cast< KeyMappingManageable<ShooterFPS>*>(this);
    return Ra::Gui::CameraManipulator::qt_metacast(_clname);
}

int Ra::Gui::ShooterFPS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Ra::Gui::CameraManipulator::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
