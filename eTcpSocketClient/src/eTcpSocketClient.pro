TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
DESTDIR = $${PWD}/../../bin

SOURCES += \
        eclient.cpp \
        eclientMain.cpp \
        esocket.cpp

HEADERS += \
    eclient.h \
    esocket.h \
    stdafx.h
