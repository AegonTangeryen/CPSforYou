#include "fbgudpthread.h"

FBGUdpThread::FBGUdpThread()  {}

FBGUdpThread::~FBGUdpThread() {}

FBGUdpThread::FBGUdpThread(QString path)
{
    fbgPath = path;
}

// 子线程
void FBGUdpThread::run()
{
    FBGSensos *farewellSensors = new FBGSensos(fbgPath);
    connect(farewellSensors,&FBGSensos::sendPara2Ui,this,&FBGUdpThread::relayUdpInfo);
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

// 中转消息
void FBGUdpThread::relayUdpInfo(int tywin)
{
    emit passUdpInfo(tywin);
}

