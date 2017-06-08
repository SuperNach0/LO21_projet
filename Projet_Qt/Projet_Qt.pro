QT += widgets
CONFIG += console
QT += xml

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
    main.cpp \
    notes.cpp \
    fenetres.cpp \
    versions.cpp

HEADERS += \
    notes.h \
    fenetres.h \
    versions.h \
    relations.h
