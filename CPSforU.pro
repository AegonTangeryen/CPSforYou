#-------------------------------------------------
#
# Project created by QtCreator 2017-12-05T21:25:49
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += network
QT       += serialport
QT       += charts

RC_ICONS += Panda.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CPSforU
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        cloudplatform.cpp \
        cloudtcpthread.cpp \
        dataxml.cpp \
        devallinfo.cpp \
        ds18b20sensor.cpp \
        ds18tcpthread.cpp \
        fbgsensos.cpp \
        fbgudpthread.cpp \
        hnc848system.cpp \
        laserdisplacesensor.cpp \
        thermalerrorcompensation.cpp \
        tools.cpp \
        envisensor.cpp \
        envithread.cpp \
        mmtimer.cpp

HEADERS += \
        mainwindow.h \
        cloudplatform.h \
        cloudtcpthread.h \
        dataxml.h \
        devallinfo.h \
        ds18b20sensor.h \
        ds18tcpthread.h \
        fbgsensos.h \
        fbgudpthread.h \
        hnc848system.h \
        laserdisplacesensor.h \
        thermalerrorcompensation.h \
        tools.h \
        envisensor.h \
        envithread.h \
        mmtimer.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += ./IncludesRely

LIBS += $$PWD/HncNetDll.lib \
        $$PWD/LKIF2.lib \
        -lpthread libwsock32 libws2_32 \
        -lwinmm

RESOURCES += \
    rc.qrc
