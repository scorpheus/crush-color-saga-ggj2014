#-------------------------------------------------
#
# Project created by QtCreator 2014-01-24T23:48:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = crushcolorsaga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    character.cpp \
    level.cpp \
    platform.cpp \
    inputmanager.cpp \
    gameconfigurationdialog.cpp \
    background.cpp \
    contour.cpp \
    level_1.cpp \
    health_display.cpp \
    level_2.cpp

HEADERS  += mainwindow.h \
    character.h \
    level.h \
    platform.h \
    inputmanager.h \
    gameconfigurationdialog.h \
    background.h \
    contour.h \
    level_1.h \
    health_display.h \
    level_2.h

FORMS    += mainwindow.ui \
    gameconfigurationdialog.ui

RESOURCES += \
    resources.qrc
