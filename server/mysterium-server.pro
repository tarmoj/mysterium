#-------------------------------------------------
#
# Project created by QtCreator 2017-02-09T22:03:29
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mysterium-server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wsserver.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    wsserver.h \
    player.h

FORMS    += mainwindow.ui

macx {
    deploy.path = $$PWD
    deploy.commands = $$[QT_INSTALL_PREFIX]/bin/macdeployqt $$OUT_PWD/$$DESTDIR/$${TARGET}.app -qmldir=$$PWD -dmg # deployment
    INSTALLS = deploy

}

RESOURCES += \
    command-files.qrc
