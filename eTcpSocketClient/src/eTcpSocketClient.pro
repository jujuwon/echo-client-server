TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        eclient.cpp \
        esocket.cpp \
        main.cpp

HEADERS += \
    eclient.h \
    esocket.h \
    stdafx.h
