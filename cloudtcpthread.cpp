#include "cloudtcpthread.h"

// 构造函数
CloudTcpThread::CloudTcpThread() {}

CloudTcpThread::~CloudTcpThread()
{
    qDebug()<<"退出云服务线程";
}

// 子线程
void CloudTcpThread::run()
{
    emit passCloudInfo("进入云平台数据传输子线程");
    cloudForU = new CloudPlatform();
    connect(cloudForU, &CloudPlatform::sendMsg, this, &CloudTcpThread::relayCloudInfo);
    connect(this,&CloudTcpThread::destroyTcpClient,cloudForU,&CloudPlatform::deleteTcpClient);
    exec();
}

// 传递信息：从云平台socket到界面
void CloudTcpThread::relayCloudInfo(QString jamie)
{
    emit passCloudInfo(jamie);
}

// 关闭线程
void CloudTcpThread::closeThread()
{
    emit destroyTcpClient();
    sleep(1);
    quit();
    wait();
}
