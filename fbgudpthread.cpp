#include "fbgudpthread.h"

FBGUdpThread::FBGUdpThread() {}

FBGUdpThread::FBGUdpThread(QString path)
{
    fbgPath = path;
}

FBGUdpThread::~FBGUdpThread()
{
    qDebug()<<endl<<"FBG的udp通信子线程退出";
}

void FBGUdpThread::run()
{
    FBGSensos *farewellSensors = new FBGSensos(fbgPath);
    qDebug()<<"进入FBG专属UDP socket通信子线程";
    connect(farewellSensors,&FBGSensos::sendMsg2Ui,this,&FBGUdpThread::relayUdpInfo);
    connect(this,&FBGUdpThread::destroyUdp,farewellSensors,&FBGSensos::deleteUdpSocket);
    connect(this,&FBGUdpThread::sendNewDay,farewellSensors,&FBGSensos::niceNewDay);
    exec();
}

// 用户手动退出
void FBGUdpThread::forceThread2Quit()
{ 
    emit destroyUdp();
    sleep(1);
    quit();
    wait();
}

// 创建新一天文件夹
void FBGUdpThread::newDayforYou(QString davos)
{
    emit sendNewDay(davos);
}

void FBGUdpThread::relayUdpInfo(QString tywin)
{
    emit passUdpInfo(tywin);
}

