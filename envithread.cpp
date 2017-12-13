#include "envithread.h"

EnviThread::EnviThread(QString filePath)
{
    path = filePath;
}

EnviThread::~EnviThread()
{
    qDebug()<<"退出环境温度子线程";
}

// 环境温度专属子线程
void EnviThread::run()
{
    EnviSensor *loveEnvironment = new EnviSensor(path);
    connect(loveEnvironment, &EnviSensor::sendMsg, this, &EnviThread::passEnvMsg2Ui);
    connect(this,&EnviThread::sendNewDay,loveEnvironment,&EnviSensor::niceNewDay);
    connect(this,&EnviThread::destroyTcp,loveEnvironment,&EnviSensor::deleteEnvServer);
    exec();
}

// 槽函数：将socket通信的数据发往主页面显示
void EnviThread::passEnvMsg2Ui(QString para, int starkstatus)
{
    emit relayMsg2Ui(para,starkstatus);
}

// 创建新的一天的文件夹
void EnviThread::newDayforYou(QString branden)
{
    emit sendNewDay(branden);
}

// 手动退出线程
void EnviThread::forceThread2Quit()
{
    emit destroyTcp();
    sleep(1);
    quit();
    wait();
}
