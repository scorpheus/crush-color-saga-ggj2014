#------------------------------------------------
#
# Project created by QtCreator 2014-01-24T23:48:42
#
#-------------------------------------------------

QT += core gui network xml phonon
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = crushcolorsaga
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    character.cpp \
    level.cpp \
    platform.cpp \
    inputmanager.cpp \
    background.cpp \
    contour.cpp \
    level_1.cpp \
    health_display.cpp \
    level_2.cpp \
    end_level.cpp \
    movingprojectorbackground.cpp \
    simplevariantanimation.cpp \
    gameconfiguration.cpp \
    fireball.cpp \
    soundmanager.cpp \
    blowup.cpp\
    level_3.cpp \
    movingprojectorbackground_level3.cpp \
    wikimediaimagebackground.cpp

HEADERS  += mainwindow.h \
    character.h \
    level.h \
    platform.h \
    inputmanager.h \
    background.h \
    contour.h \
    level_1.h \
    health_display.h \
    level_2.h \
    end_level.h \
    movingprojectorbackground.h \
    simplevariantanimation.h \
    gameconfiguration.h \
    fireball.h \
    soundmanager.h \
    blowup.h\
    level_3.h \
    movingprojectorbackground_level3.h \
    wikimediaimagebackground.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
