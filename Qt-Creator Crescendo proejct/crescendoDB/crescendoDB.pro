TEMPLATE = subdirs

SUBDIRS += \
    crescendoDB \
    crescendoDB-CLI \
    crescendoDB-tests

crescendoDB-tests.depends = crescendoDB
crescendoDB-CLI.depends = crescendoDB

CONFIG += console c++17
CONFIG -= app.bundle
CONFIG -= qt

SOURCES +=

HEADERS +=
