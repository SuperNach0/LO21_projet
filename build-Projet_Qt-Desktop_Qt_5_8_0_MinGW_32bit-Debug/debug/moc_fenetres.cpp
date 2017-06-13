/****************************************************************************
** Meta object code from reading C++ file 'fenetres.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Projet_Qt/fenetres.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetres.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FenPrincipale_t {
    QByteArrayData data[16];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FenPrincipale_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FenPrincipale_t qt_meta_stringdata_FenPrincipale = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FenPrincipale"
QT_MOC_LITERAL(1, 14, 5), // "popup"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 22), // "popupAnciennesVersions"
QT_MOC_LITERAL(4, 44, 21), // "popupCreationRelation"
QT_MOC_LITERAL(5, 66, 25), // "affichage_notes_relations"
QT_MOC_LITERAL(6, 92, 21), // "affichage_single_note"
QT_MOC_LITERAL(7, 114, 2), // "id"
QT_MOC_LITERAL(8, 117, 4), // "date"
QT_MOC_LITERAL(9, 122, 25), // "affichage_single_relation"
QT_MOC_LITERAL(10, 148, 5), // "titre"
QT_MOC_LITERAL(11, 154, 14), // "menuContextuel"
QT_MOC_LITERAL(12, 169, 13), // "supprimerNote"
QT_MOC_LITERAL(13, 183, 10), // "editerNote"
QT_MOC_LITERAL(14, 194, 8), // "load_xml"
QT_MOC_LITERAL(15, 203, 22) // "affichage_arborescence"

    },
    "FenPrincipale\0popup\0\0popupAnciennesVersions\0"
    "popupCreationRelation\0affichage_notes_relations\0"
    "affichage_single_note\0id\0date\0"
    "affichage_single_relation\0titre\0"
    "menuContextuel\0supprimerNote\0editerNote\0"
    "load_xml\0affichage_arborescence"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FenPrincipale[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    2,   78,    2, 0x0a /* Public */,
       6,    1,   83,    2, 0x2a /* Public | MethodCloned */,
       9,    1,   86,    2, 0x0a /* Public */,
      11,    1,   89,    2, 0x0a /* Public */,
      12,    0,   92,    2, 0x0a /* Public */,
      13,    0,   93,    2, 0x0a /* Public */,
      14,    0,   94,    2, 0x0a /* Public */,
      15,    1,   95,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void FenPrincipale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FenPrincipale *_t = static_cast<FenPrincipale *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->popup(); break;
        case 1: _t->popupAnciennesVersions(); break;
        case 2: _t->popupCreationRelation(); break;
        case 3: _t->affichage_notes_relations(); break;
        case 4: _t->affichage_single_note((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->affichage_single_note((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->affichage_single_relation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->menuContextuel((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 8: _t->supprimerNote(); break;
        case 9: _t->editerNote(); break;
        case 10: _t->load_xml(); break;
        case 11: _t->affichage_arborescence((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject FenPrincipale::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FenPrincipale.data,
      qt_meta_data_FenPrincipale,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FenPrincipale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FenPrincipale::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FenPrincipale.stringdata0))
        return static_cast<void*>(const_cast< FenPrincipale*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FenPrincipale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
struct qt_meta_stringdata_fenetre_creation_note_t {
    QByteArrayData data[4];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fenetre_creation_note_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fenetre_creation_note_t qt_meta_stringdata_fenetre_creation_note = {
    {
QT_MOC_LITERAL(0, 0, 21), // "fenetre_creation_note"
QT_MOC_LITERAL(1, 22, 15), // "choisir_fichier"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 4) // "save"

    },
    "fenetre_creation_note\0choisir_fichier\0"
    "\0save"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fenetre_creation_note[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void fenetre_creation_note::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fenetre_creation_note *_t = static_cast<fenetre_creation_note *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->choisir_fichier(); break;
        case 1: _t->save(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject fenetre_creation_note::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fenetre_creation_note.data,
      qt_meta_data_fenetre_creation_note,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *fenetre_creation_note::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fenetre_creation_note::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_fenetre_creation_note.stringdata0))
        return static_cast<void*>(const_cast< fenetre_creation_note*>(this));
    return QWidget::qt_metacast(_clname);
}

int fenetre_creation_note::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_fenetre_creation_relation_t {
    QByteArrayData data[5];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fenetre_creation_relation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fenetre_creation_relation_t qt_meta_stringdata_fenetre_creation_relation = {
    {
QT_MOC_LITERAL(0, 0, 25), // "fenetre_creation_relation"
QT_MOC_LITERAL(1, 26, 17), // "affichage_couples"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 11), // "save_couple"
QT_MOC_LITERAL(4, 57, 13) // "save_relation"

    },
    "fenetre_creation_relation\0affichage_couples\0"
    "\0save_couple\0save_relation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fenetre_creation_relation[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void fenetre_creation_relation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fenetre_creation_relation *_t = static_cast<fenetre_creation_relation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->affichage_couples(); break;
        case 1: _t->save_couple(); break;
        case 2: _t->save_relation(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject fenetre_creation_relation::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_fenetre_creation_relation.data,
      qt_meta_data_fenetre_creation_relation,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *fenetre_creation_relation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fenetre_creation_relation::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_fenetre_creation_relation.stringdata0))
        return static_cast<void*>(const_cast< fenetre_creation_relation*>(this));
    return QWidget::qt_metacast(_clname);
}

int fenetre_creation_relation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
