#include "ds18tcpthread.h"

Ds18TcpThread::Ds18TcpThread() {}

Ds18TcpThread::Ds18TcpThread(QString dspath)
{
    path = dspath;
}

Ds18TcpThread::~Ds18TcpThread()
{
    qDebug()<<"DS18b20 tcp socket通信子线程退出";
}

// DS18b20专属tcp socket通信子线程
void Ds18TcpThread::run()
{
    DS18b20Sensor *ds18B20 = new DS18b20Sensor(path);
    connect(ds18B20, &DS18b20Sensor::sendMsg, this, &Ds18TcpThread::passDS18Msg2Ui);
    connect(this,&Ds18TcpThread::sendNewDay,ds18B20,&DS18b20Sensor::niceNewDay);
    connect(this,&Ds18TcpThread::destroyTcp,ds18B20,&DS18b20Sensor::deleteTcpServer);
    exec();
}

// 槽函数：将socket通信的数据发往主页面显示
void Ds18TcpThread::passDS18Msg2Ui(QString para, int starkstatus)
{
    emit relayMsg2Ui(para,starkstatus);
}

// 创建新的一天的文件夹
void Ds18TcpThread::newDayforYou(QString seaworth)
{
    emit sendNewDay(seaworth);
}

// 手动退出线程
void Ds18TcpThread::forceThread2Quit()
{
    emit destroyTcp();
    sleep(1);
    quit();
    wait();
}
