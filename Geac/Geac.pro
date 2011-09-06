#-------------------------------------------------
#
# Project created by QtCreator 2011-02-11T21:24:50
#
#-------------------------------------------------

QT       += core gui svg

TARGET = Geac
TEMPLATE = app

SOURCES += main.cpp\
        geac.cpp \
    esiextractor.cpp \
    checkfiledialog.cpp \
    logparser.cpp \
    filemanager.cpp \
    checkablefile.cpp \
    filemanagerdelegate.cpp \
    fileprocessor.cpp

HEADERS  += geac.h \
    esiextractor.h \
    checkfiledialog.h \
    logparser.h \
    filemanager.h \
    checkablefile.h \
    filemanagerdelegate.h \
    fileprocessor.h

FORMS    += geac.ui

TRANSLATIONS += geac_fr.ts \
                geac_en.ts

RESOURCES += \
    images.qrc
