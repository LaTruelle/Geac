#-------------------------------------------------
#
# Project created by QtCreator 2011-02-11T21:24:50
#
#-------------------------------------------------

QT       += core gui

TARGET = Geac
TEMPLATE = app


SOURCES += main.cpp\
        geac.cpp \
    esiextractor.cpp \
    checkfiledialog.cpp \
    logparser.cpp

HEADERS  += geac.h \
    esiextractor.h \
    checkfiledialog.h \
    logparser.h

FORMS    += geac.ui

TRANSLATIONS += geac_fr.ts
