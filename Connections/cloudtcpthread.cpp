#include "cloudtcpthread.h"

// 构造函数
CloudTcpThread::CloudTcpThread(QString ourIp,QString ourPort)
{
    cloudIp = ourIp;
    cloudPort = ourPort;
}

// 析构函数
CloudTcpThread::~CloudTcpThread() {}

// 子线程
void CloudTcpThread::run()
{
    emit passCloudInfo("进入云服务平台线程",1);
    CloudPlatform *cloudForU = new CloudPlatform(cloudIp,cloudPort);
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
    qDebug()<<"cloudQuit";
}
