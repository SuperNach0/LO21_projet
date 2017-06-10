QT += widgets
CONFIG += console
QT += xml

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
    main.cpp \
    notes.cpp \
    versions.cpp \
    relations.cpp \
    fenetre_creation_note.cpp \
    fenetre_creation_relation.cpp \
    fenetre_principale.cpp

HEADERS += \
    notes.h \
    fenetres.h \
    versions.h \
    relations.h
