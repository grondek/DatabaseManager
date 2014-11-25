#-------------------------------------------------
#
# Project created by QtCreator 2014-10-03T00:09:35
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = SQLiteDatabase
TEMPLATE = lib

DEFINES += SQLITEDATABASE_LIBRARY

DESTDIR = $$PWD/../bin/plugins

INCLUDEPATH += ../DBInterface

LIBS += -L$$PWD/../bin -lDBInterface

SOURCES += sqlitedatabase.cpp \
    sqlitecreatedatabase.cpp

HEADERS += sqlitedatabase.h\
        SQLiteDatabase_global.h \
    sqlitecreatedatabase.h \
    sqlitedbdefaults.h

OTHER_FILES += \
    sqlitedatabase.json

RESOURCES += \
    sqlitedatabase.qrc

FORMS += \
    sqlitecreatedatabase.ui
