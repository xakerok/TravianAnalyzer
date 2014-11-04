#-------------------------------------------------
#
# Project created by QtCreator 2014-10-22T22:41:14
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TravianAnalizator
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += $$PWD/../include

HEADERS  += ../include/gui/main_window.h \
    ../include/core/data_loader.h \
    ../include/core/world.h \
    ../include/core/player.h \
    ../include/core/village.h \
    ../include/core/alliance.h \
    ../include/core/data_holder.h


SOURCES += ../src/main.cpp\
        ../src/gui/main_window.cpp \
    ../src/core/data_loader.cpp \
    ../src/core/world.cpp \
    ../src/core/data_holder.cpp


FORMS    += ../forms/main_window.ui

win32: PLATFORM = "windows"
unix: PLATFORM = "unix"
linux: PLATFORM = "linux"

CONFIG(release, debug|release) {
   DESTDIR = $$PWD/../bin/$$PLATFORM/release
}
else {
   DESTDIR = $$PWD/../bin/$$PLATFORM/debug
}

UI_DIR = $$DESTDIR/.ui
OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
