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
	 ../include/data_loader.h \
    ../include/core/world.h \
    ../include/core/player.h \
    ../include/core/village.h \
    ../include/core/alliance.h \
	 ../include/data_holder.h \
    ../include/core/server.h \
    ../include/config.h \
    ../include/core/servers_model.h \
    ../include/helper/server_helper.h


SOURCES += ../src/main.cpp\
        ../src/gui/main_window.cpp \
	 ../src/data_loader.cpp \
    ../src/core/world.cpp \
	 ../src/data_holder.cpp \
    ../src/core/server.cpp \
    ../src/core/servers_model.cpp \
    ../src/helper/server_helper.cpp


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
