#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T14:48:44
#
#-------------------------------------------------

QT       += core gui \
            multimedia \
            multimediawidgets \
            script


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spritewalker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sprite.cpp \
    actor.cpp \
    herorules.cpp \
    villagerrules.cpp \
    monsterrules.cpp \
    scheusalrules.cpp \
    assetmanager.cpp \
    sequentialguid.cpp \
    scenemanager.cpp \
    consolewidget.cpp \
    gameengine.cpp \
    gamescene.cpp \
    actordialog.cpp \
    keypressconsumer.cpp \
    ruleset.cpp \
    utilities.cpp

HEADERS  += mainwindow.h \
    sprite.h \
    actor.h \
    herorules.h \
    villagerrules.h \
    monsterrules.h \
    scheusalrules.h \
    assetmanager.h \
    typedefs.h \
    sequentialguid.h \
    scenemanager.h \
    consolewidget.h \
    gameengine.h \
    gamescene.h \
    actordialog.h \
    keypressconsumer.h \
    ruleset.h \
    utilities.h

FORMS    += mainwindow.ui \
    actordialog.ui

RESOURCES += \
    resources.qrc
