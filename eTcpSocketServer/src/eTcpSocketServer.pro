TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        eserver.cpp \
        esocket.cpp \
        main.cpp

HEADERS += \
    eserver.h \
    esocket.h \
    stdafx.h
