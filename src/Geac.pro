#-------------------------------------------------
#
# Project created by QtCreator 2011-02-11T21:24:50
#
#-------------------------------------------------

QT       += core gui widgets svg concurrent

TARGET = Geac
TEMPLATE = app

SOURCES += main.cpp\
    geac.cpp \
    checkfiledialog.cpp \
    logparser.cpp \
    filemanager.cpp \
    checkablefile.cpp \
    filemanagerdelegate.cpp \
    esiwriter.cpp \
    cifwriter.cpp \
    xyzwriter.cpp

HEADERS  += geac.h \
    checkfiledialog.h \
    logparser.h \
    filemanager.h \
    checkablefile.h \
    filemanagerdelegate.h \
    esiwriter.h \
    cifwriter.h \
    xyzwriter.h

FORMS    += geac.ui

TRANSLATIONS += geac_fr.ts \
                geac_en.ts

RESOURCES += \
    images.qrc
