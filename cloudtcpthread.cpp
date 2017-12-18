#include "cloudtcpthread.h"

// 构造函数
CloudTcpThread::CloudTcpThread()  {}

// 析构函数
CloudTcpThread::~CloudTcpThread()
{
    qDebug()<<"云服务平台线程已退出";
}

// 子线程
void CloudTcpThread::run()
{
    emit passCloudInfo("进入云服务平台线程",1);
    cloudForU = new CloudPlatform();
    connect(cloudForU, &CloudPlatform::sendMsg, this, &CloudTcpThread::relayCloudInfo);
    connect(this,&CloudTcpThread::destroyTcpClient,cloudForU,&CloudPlatform::deleteTcpClient);
    exec();
}

// 传递信息：从云平台socket到界面
void CloudTcpThread::relayCloudInfo(QString jamie,int jack)
{
    emit passCloudInfo(jamie,jack);
}

// 关闭线程
void CloudTcpThread::closeThread()
{
    emit destroyTcpClient();
    sleep(1);
    quit();
    wait();
}
