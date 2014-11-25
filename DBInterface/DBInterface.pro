#-------------------------------------------------
#
# Project created by QtCreator 2014-10-02T20:55:51
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = DBInterface
TEMPLATE = lib

DEFINES += DBINTERFACE_LIBRARY

DESTDIR = $$PWD/../bin

SOURCES += dbinterface.cpp \
    dbobject.cpp

HEADERS += dbinterface.h\
        DBInterface_global.h \
    dbobject.h \
    dbdefaults.h

