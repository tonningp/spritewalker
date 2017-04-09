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
    ctilescene.cpp \
    actor.cpp \
    herorules.cpp \
    villagerrules.cpp \
    monsterrules.cpp \
    scheusalrules.cpp \
    actorassets.cpp \
    cruleset.cpp \
    assetmanager.cpp \
    cactordialog.cpp \
    cutilities.cpp \
    cgameengine.cpp \
    sequentialguid.cpp \
    lineeditwidget.cpp \
    cconsolewidget.cpp \
    ckeypressconsumer.cpp \
    scenemanager.cpp

HEADERS  += mainwindow.h \
    sprite.h \
    ctilescene.h \
    actor.h \
    herorules.h \
    villagerrules.h \
    monsterrules.h \
    scheusalrules.h \
    actorassets.h \
    cruleset.h \
    assetmanager.h \
    cactordialog.h \
    cutilities.h \
    cgameengine.h \
    typedefs.h \
    sequentialguid.h \
    lineeditwidget.h \
    cconsolewidget.h \
    ckeypressconsumer.h \
    scenemanager.h

FORMS    += mainwindow.ui \
    cactordialog.ui

RESOURCES += \
    resources.qrc
