#include "cloudplatform.h"

bool cloudLinkStatus = false;  //云平台连接状态

CloudPlatform::CloudPlatform(QString skyIP, QString sunPort)
{
    ticToc = 0;
    cloudServerIP = skyIP;             // 正式连接
    //cloudServerIP = getHostIpAddress();          // 本地连接测试
    cloudServerPort = sunPort.toInt();
    cloudSocket = new QTcpSocket();
    cloudTimer = new QTimer(this);          // 5s一次发送传感器信息
    hncPrivateTimer = new QTimer(this);     // 200ms一次单独发送hnc信息
    userOperation = false;
    connect(cloudSocket,&QTcpSocket::connected,this,&CloudPlatform::afterConnected);
    cloudSocket->connectToHost(QHostAddress(cloudServerIP), cloudServerPort);
    if(cloudSocket->errorString() != "Unknown error")
    {
        qDebug()<<cloudSocket->errorString();
    }

    connect(cloudTimer,&QTimer::timeout, this,&CloudPlatform::onTimeIsUp);
    cloudTimer->setTimerType(Qt::PreciseTimer);
    cloudTimer->setInterval(5000);
    cloudTimer->start();

    connect(hncPrivateTimer,&QTimer::timeout,this,&CloudPlatform::onPrivateTimeUp);
    hncPrivateTimer->setTimerType(Qt::PreciseTimer);
    hncPrivateTimer->setInterval(200);
    //hncPrivateTimer->start();
}

CloudPlatform::~CloudPlatform() {}

// 连接上云服务平台后
void CloudPlatform::afterConnected()
{
    emit sendMsg("云平台已连接",1);
    cloudLinkStatus = true;
    connect(cloudSocket,&QTcpSocket::readyRead,this,&CloudPlatform::receiveFromCloud);
    connect(cloudSocket,&QTcpSocket::disconnected,this,&CloudPlatform::afterDisconnected);
}

// 从云平台接收
void CloudPlatform::receiveFromCloud()
{
    QByteArray recBuff;
    recBuff = cloudSocket->readAll();
    QString lxd = dataXML::xmlStrRead(QString(recBuff));
    QString cloudUrls = dataInfo.cloudInfo.cloudURLS.value("MODELBIN");
    QString cloudCmds = dataInfo.cloudInfo.cloudCMDS;
}

// 云平台单方面断开连接
void CloudPlatform::afterDisconnected()
{
    qDebug()<<"6.1";
    if(userOperation) return;
    cloudSocket->abort();
    cloudSocket->connectToHost(QHostAddress(cloudServerIP), cloudServerPort);
    if(!cloudSocket->waitForConnected(5000))
    {
        emit sendMsg("云平台已断开",-1);
    }
    cloudLinkStatus = false;
    ticToc=0;  // 开始计时
}

// 清除内存
void CloudPlatform::deleteTcpClient()
{
    qDebug()<<"6.2";
    cloudLinkStatus = false;
    userOperation = true;
    cloudSocket->abort();
    cloudSocket->close();
    delete cloudTimer;
    delete hncPrivateTimer;
    delete cloudSocket;
    emit sendMsg("已删除cloudsocket",0);
}

// 主定时器中断
void CloudPlatform::onTimeIsUp()
{
    qDebug()<<"6.3";
    ticToc++;
    if(cloudLinkStatus) // 如果连接上了云平台，发送信息
    {
        packageSensorsData();
        QString xmlOutStr = dataXML::xmlStrCreat(dataInfo);
        xmlOutStr += "end\n";
        cloudSocket->write(xmlOutStr.toLatin1());
        cloudSocket->flush();
    }
    else // 如果与云平台断开，定时重连
    {
        if(ticToc==6) linkOnceAgain();
    }
}

// 数控系统专属定时器中断
void CloudPlatform::onPrivateTimeUp()
{
    qDebug()<<"6.5";
    if(!cncWorkingStatus) // 如果已连接云平台，每200ms发送一次机床信息包
    {
        packageHncData();
        QString xmlOutStr = dataXML::xmlStrCreat(dataInfo);
        xmlOutStr += "end\n";
        cloudSocket->write(xmlOutStr.toLatin1());
        cloudSocket->flush();
    }
}

 // 定时30s重新连接云平台
void CloudPlatform::linkOnceAgain()
{
    qDebug()<<"6.4";
    ticToc = 0;
    cloudSocket->connectToHost(QHostAddress(cloudServerIP), cloudServerPort);
    if(cloudSocket->waitForConnected(5000))  // 如果连上了
    {
        cloudLinkStatus = true;
    }
    else // 如果连接失败
    {
        emit sendMsg("本次云平台尝试连接失败",2);
    }
}

// 数控系统信息单独打包成XML格式
void CloudPlatform::packageHncData()
{
    // 包头信息
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString currentTime =current_date_time.toString("yyyyMMddhhmmsszzz");
    dataInfo.headInfo.time = currentTime;
    dataInfo.headInfo.macId = getHostMacAddress();// 获取本机Mac地址
    dataInfo.headInfo.macId.replace(QString("-"),QString(""));
    dataInfo.headInfo.macId.replace(QString(":"),QString(""));
    dataInfo.headInfo.msg = "Wuhan Heavy-duty machine tool ZK5540A";

    // 数控系统信息
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[0], QString::number(CNCInfo.ch,10));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[1], QString::number(CNCInfo.AXIS_X_POS,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[2], QString::number(CNCInfo.AXIS_Y_POS,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[3], QString::number(CNCInfo.AXIS_Z_POS,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[4], QString::number(CNCInfo.AXIS_MA_POS,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[5], QString::number(CNCInfo.AXIS_X_PWR,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[6], QString::number(CNCInfo.AXIS_Y_PWR,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[7], QString::number(CNCInfo.AXIS_Z_PWR,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[8], QString::number(CNCInfo.AXIS_MA_PWR,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[9], QString::number(CNCInfo.AXIS_X_FUHE,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[10],QString::number(CNCInfo.AXIS_Z_FUHE,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[11],QString::number(CNCInfo.AXIS_Y_FUHE,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[12],QString::number(CNCInfo.AXIS_MA_FUHE,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[13],QString::number(CNCInfo.feedrate,10,3));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[14],QString::number(CNCInfo.speed,10,0));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[15],CNCInfo.PauseStatus);
}

// 所有传感器数据整理成XML格式
void CloudPlatform::packageSensorsData()
{
    // 包头信息
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString currentTime =current_date_time.toString("yyyyMMddhhmmsszzz");
    dataInfo.headInfo.time = currentTime;
    dataInfo.headInfo.macId = getHostMacAddress(); // 获取本机Mac地址
    dataInfo.headInfo.macId.replace(QString("-"),QString(""));
    dataInfo.headInfo.macId.replace(QString(":"),QString(""));
    dataInfo.headInfo.msg = "Wuhan Heavy-duty machine tool ZK5540A";

    // FBG传感器
    QString temp1;
    QString temp2;
    for(int i = 0; i < FBG_CHANNEL; i++)
    {
        for(int j = 0; j < FBG_NODE; j++)
        {
            temp1 = dataInfo.fbgInfo.FBGchannelKey[i];
            temp2 = temp1.append(dataInfo.fbgInfo.FBGnodeKey[j]);
            dataInfo.fbgInfo.FBGdata.insert(temp2, FBG_ALL[i][j]);
        }
    }

    // 电类温度传感器
    for(int i = 0; i < 6; i++)   //一号板前6个通道
    {
        for(int j = 0; j < DS18B20_Index_Max; j++)
        {
            dataInfo.dsbInfo.DSBdata.insert(dataInfo.dsbInfo.DSBkey[i*8+j],DS18B20_ALL_Node[i][j].temperature);
        }
    }
    for(int i =0;i<4;i++)      //一号板第七通道四个点
    {
        dataInfo.dsbInfo.DSBdata.insert(dataInfo.dsbInfo.DSBkey[48+i],DS18B20_ALL_Node[6][i].temperature);
    }
    for(int i=0;i<DS18B20_Index_Max;i++)   //一号板第八通道
    {
        dataInfo.dsbInfo.DSBdata.insert(dataInfo.dsbInfo.DSBkey[52+i],DS18B20_ALL_Node[7][i].temperature);
    }
    for(int i=0;i<6;i++)   // 二号板第一通道后六个点
    {
        dataInfo.dsbInfo.DSBdata.insert(dataInfo.dsbInfo.DSBkey[60+i],DS18B20_ADD_Node[0][i+2].temperature);
    }
    for(int i=0;i<7;i++)  // 二号板后七个通道
    {
        for(int j=0;j<DS18B20_Index_Max;j++)
        {
            dataInfo.dsbInfo.DSBdata.insert(dataInfo.dsbInfo.DSBkey[66+i*8+j],DS18B20_ADD_Node[i+1][j].temperature);
        }
    }

    // 环境温度传感器
    for(int i=0;i<4;i++)
    {
        dataInfo.dsbInfo.DSBdata.insert(dataInfo.dsbInfo.DSBkey[122+i],ENV_ALL_Node[i].temperature);
    }

    // 激光位移传感器
    for(int i = 0; i < CCD_DIMENSION; i++){
        dataInfo.ccdInfo.CCDdata.insert(dataInfo.ccdInfo.CCDkey[i],ccdInfo[i]);
    }

    // 统一资源定位符
    for(int i = 0; i < CLOUD_URLS_DIMENSION; i++){
        dataInfo.cloudInfo.cloudURLS.insert(dataInfo.cloudInfo.cloudURLSkey[i], "https://user.qzone.qq.com/1181836535/infocenter");
    }
    // 云平台命令
    dataInfo.cloudInfo.cloudCMDS = "No cmds";
}
