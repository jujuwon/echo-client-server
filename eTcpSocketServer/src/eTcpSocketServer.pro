TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DESTDIR = $${PWD}/../../bin

SOURCES += \
        eserver.cpp \
        eserverMain.cpp \
        esocket.cpp

HEADERS += \
    eserver.h \
    esocket.h \
    stdafx.h
