TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        db-management-tests.cpp \
        main.cpp

include(../libcrescendoDB/Defines.pri)

HEADERS += \
    catch.hpp \
    tests.h
