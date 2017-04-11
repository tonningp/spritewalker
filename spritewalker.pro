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
    actorassets.cpp \
    cruleset.cpp \
    assetmanager.cpp \
    cutilities.cpp \
    sequentialguid.cpp \
    lineeditwidget.cpp \
    ckeypressconsumer.cpp \
    scenemanager.cpp \
    consolewidget.cpp \
    gameengine.cpp \
    gamescene.cpp \
    actordialog.cpp

HEADERS  += mainwindow.h \
    sprite.h \
    actor.h \
    herorules.h \
    villagerrules.h \
    monsterrules.h \
    scheusalrules.h \
    actorassets.h \
    cruleset.h \
    assetmanager.h \
    cutilities.h \
    typedefs.h \
    sequentialguid.h \
    lineeditwidget.h \
    ckeypressconsumer.h \
    scenemanager.h \
    consolewidget.h \
    gameengine.h \
    gamescene.h \
    actordialog.h

FORMS    += mainwindow.ui \
    actordialog.ui

RESOURCES += \
    resources.qrc
