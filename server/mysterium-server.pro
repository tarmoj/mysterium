#-------------------------------------------------
#
# Project created by QtCreator 2017-02-09T22:03:29
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#NB! I don't know why but on Linux QtCreator wants QT_ASSUME_STDERR_HAS_CONSOLE in the Evironment to show output in Application Output

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


# Add the copy command after the build process
unix {
    QMAKE_POST_LINK += cp $$PWD/command-files/syrr.commands $$OUT_PWD
}



macx {
    deploy.path = $$PWD
    deploy.commands = $$[QT_INSTALL_PREFIX]/bin/macdeployqt $$OUT_PWD/$$DESTDIR/$${TARGET}.app -qmldir=$$PWD -dmg # deployment
    INSTALLS = deploy

}


win32 {
    QMAKE_POST_LINK += copy $$PWD/command-files/syrr.commands $$OUT_PWD # untested

    first.path = $$PWD
    first.commands = $$[QT_INSTALL_PREFIX]/bin/windeployqt  -qmldir=$$PWD  $$OUT_PWD/$$DESTDIR/release/$${TARGET}.exe # first deployment
    INSTALLS += first


}


RESOURCES += \
    command-files.qrc
