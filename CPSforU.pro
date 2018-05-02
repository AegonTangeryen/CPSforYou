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

RC_ICONS += img/Panda.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CPSforU
TEMPLATE = app

CONFIG += resources_big
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
        Connections/cloudplatform.cpp \
        Connections/cloudtcpthread.cpp \
        Auxiliary/dataxml.cpp \
        Connections/ds18b20sensor.cpp \
        Connections/ds18tcpthread.cpp \
        Connections/fbgsensos.cpp \
        Connections/fbgudpthread.cpp \
        Connections/hnc848system.cpp \
        Connections/laserdisplacesensor.cpp \
        Auxiliary/thermalerrorcompensation.cpp \
        Auxiliary/tools.cpp \
        Connections/envisensor.cpp \
        Connections/envithread.cpp \
        Auxiliary/mmtimer.cpp \
        UI/mainwindow.cpp \
        UI/configurationui.cpp \
        UI/chartthemeoption.cpp \
        UI/fbgalldataui.cpp \
        UI/ds18seeallui.cpp \
        UI/contactusui.cpp \
        UI/aboutcpsui.cpp \
        UI/musicintrductionui.cpp \
        UI/seriesintroductionui.cpp \
        UI/animationintroductionui.cpp \
        UI/loginui.cpp \
        UI/inquireupdateui.cpp \
        UI/customui.cpp \
        Auxiliary/execdoscmd.cpp

HEADERS += \
        Connections/cloudplatform.h \
        Connections/cloudtcpthread.h \
        Auxiliary/dataxml.h \
        Connections/ds18b20sensor.h \
        Connections/ds18tcpthread.h \
        Connections/fbgsensos.h \
        Connections/fbgudpthread.h \
        Connections/hnc848system.h \
        Connections/laserdisplacesensor.h \
        Auxiliary/thermalerrorcompensation.h \
        Auxiliary/tools.h \
        Connections/envisensor.h \
        Connections/envithread.h \
        Auxiliary/mmtimer.h \
        UI/mainwindow.h \
        UI/configurationui.h \
        UI/chartthemeoption.h \
        UI/fbgalldataui.h \
        UI/ds18seeallui.h \
        UI/contactusui.h \
        UI/aboutcpsui.h \
        UI/musicintrductionui.h \
        UI/seriesintroductionui.h \
        UI/animationintroductionui.h \
        UI/loginui.h \
        UI/customui.h \
        IncludesRely/autotestncu.h \
        IncludesRely/devdict.h \
        IncludesRely/eventdef.h \
        IncludesRely/fcompen.h \
        IncludesRely/ftpsock.h \
        IncludesRely/hncactivation.h \
        IncludesRely/hncalarm.h \
        IncludesRely/hncaxis.h \
        IncludesRely/hncchan.h \
        IncludesRely/hnccrds.h \
        IncludesRely/hncdatadef.h \
        IncludesRely/hncdatatype.h \
        IncludesRely/hncevent.h \
        IncludesRely/hncfileverify.h \
        IncludesRely/hncfprogman.h \
        IncludesRely/hncinfo.h \
        IncludesRely/hnckeygen.h \
        IncludesRely/hnclad.h \
        IncludesRely/hncmath.h \
        IncludesRely/hncmodal.h \
        IncludesRely/hncmount.h \
        IncludesRely/hncmst.h \
        IncludesRely/hncnet.h \
        IncludesRely/hncparaman.h \
        IncludesRely/hncreg.h \
        IncludesRely/hncsmpl.h \
        IncludesRely/hncsys.h \
        IncludesRely/hncsysctrl.h \
        IncludesRely/hnctool.h \
        IncludesRely/hncupdate.h \
        IncludesRely/hncvar.h \
        IncludesRely/hncverify.h \
        IncludesRely/lad_def.h \
        IncludesRely/lad_file.h \
        IncludesRely/ladtbl.h \
        IncludesRely/ladwork.h \
        IncludesRely/LKIF2.h \
        IncludesRely/loadsave.h \
        IncludesRely/ncassert.h \
        IncludesRely/neterrcode.h \
        IncludesRely/osdepend.h \
        IncludesRely/passwd.h \
        IncludesRely/smplcalc.h \
        IncludesRely/temp.h \
        IncludesRely/trspack.h \
        UI/inquireupdateui.h \
        Auxiliary/execdoscmd.h

FORMS += \
        mainwindow.ui \
        configurationui.ui \
        chartthemeoption.ui \
        fbgalldataui.ui \
        ds18seeallui.ui \
        contactusui.ui \
        aboutcpsui.ui \
        musicintrductionui.ui \
        seriesintroductionui.ui \
        animationintroductionui.ui \
        loginui.ui \
        inquireupdateui.ui \
        customui.ui

INCLUDEPATH += ./IncludesRely \
               ./Auxiliary \
               ./Connections \
               ./UI \

LIBS += $$PWD/Libs/HncNetDll.lib \
        $$PWD/Libs/LKIF2.lib \
        -lpthread libwsock32 libws2_32 \
        -lwinmm

RESOURCES += \
    rc.qrc
