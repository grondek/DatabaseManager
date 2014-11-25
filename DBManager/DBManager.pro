#-------------------------------------------------
#
# Project created by QtCreator 2014-10-02T00:29:53
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = DBManager
TEMPLATE = app

DESTDIR = $$PWD/../bin

INCLUDEPATH += ../DBInterface

LIBS += -L$$PWD/../bin -lDBInterface

SOURCES += main.cpp\
        dbmanagerwindow.cpp \
    dbpluginloader.cpp \
    dbtreemodel.cpp

HEADERS  += dbmanagerwindow.h \
    dbpluginloader.h \
    dbtreemodel.h

FORMS    += dbmanagerwindow.ui
