#include "cloudplatform.h"

bool cloudLinkStatus = false;  //云平台连接状态

CloudPlatform::CloudPlatform(QString skyIP, QString sunPort)
{
    cloudServerIP = skyIP;             // 正式连接
//    cloudServerIP = getHostIpAddress();          // 本地连接测试
    cloudServerPort = sunPort.toInt();
    cloudSocket = new QTcpSocket();
    cloudTimer = new QTimer(this);
    userOperation = false;
    ticToc = 0;
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
    cloudSocket->connectToHost(QHostAddress(cloudServerIP), cloudServerPort);
    if(!cloudSocket->waitForConnected(5000))
    {
        emit sendMsg("云平台已断开",-1);
    }
    cloudLinkStatus = false;
}

// 清除内存
void CloudPlatform::deleteTcpClient()
{
    qDebug()<<"6.2";
    cloudLinkStatus = false;
    userOperation = true;
    cloudSocket->close();
    delete cloudTimer;
    cloudSocket->deleteLater();
    emit sendMsg("已删除cloudsocket",0);
}

// 定时器中断
void CloudPlatform::onTimeIsUp()
{
    qDebug()<<"6.3";
    packageData();
    QString xmlOutStr = dataXML::xmlStrCreat(dataInfo);
    xmlOutStr += "end\n";
    cloudSocket->write(xmlOutStr.toLatin1());
    cloudSocket->flush();
    ticToc++;
    if((!cloudLinkStatus) && (ticToc == 6)) linkOnceAgain();
}

 // 定时30s重新连接云平台
void CloudPlatform::linkOnceAgain()
{
    qDebug()<<"6.4";
    ticToc = 0;
    cloudSocket->connectToHost(QHostAddress(cloudServerIP), cloudServerPort);
    if(!cloudSocket->waitForConnected(5000)) emit sendMsg("本次云平台尝试连接失败",2);
    else    cloudLinkStatus = true;
}

// 数据整理成XML格式
void CloudPlatform::packageData()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString currentTime =current_date_time.toString("yyyyMMddhhmmsszzz");
    dataInfo.headInfo.time = currentTime;
    dataInfo.headInfo.macId = getHostMacAddress();// 获取本机Mac地址
    dataInfo.headInfo.macId.replace(QString("-"),QString(""));
    dataInfo.headInfo.macId.replace(QString(":"),QString(""));
    dataInfo.headInfo.msg = "Wuhan Heavy-duty machine tool ZK5540A";

    for(int i = 0; i < CCD_DIMENSION; i++){
        dataInfo.ccdInfo.CCDdata.insert(dataInfo.ccdInfo.CCDkey[i],ccdInfo[i]);
    }

    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[0], QString::number(CNCInfo.ch,10,4));
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
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[13],QString::number(CNCInfo.feedrate,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[14],QString::number(CNCInfo.speed,10,4));
    dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[15],CNCInfo.PauseStatus);

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
    for(int i=0;i<4;i++) // 环境温度
    {
        dataInfo.dsbInfo.DSBdata.insert(dataInfo.dsbInfo.DSBkey[122+i],ENV_ALL_Node[i].temperature);
    }

    QString temp1;
    QString temp2;
    for(int i = 0; i < FBG_CHANNEL; i++){
        for(int j = 0; j < FBG_NODE; j++){
            temp1 = dataInfo.fbgInfo.FBGchannelKey[i];
            temp2 = temp1.append(dataInfo.fbgInfo.FBGnodeKey[j]);
            dataInfo.fbgInfo.FBGdata.insert(temp2, FBG_ALL[i][j]);
        }
    }

    for(int i = 0; i < CLOUD_URLS_DIMENSION; i++){
        dataInfo.cloudInfo.cloudURLS.insert(dataInfo.cloudInfo.cloudURLSkey[i], "https://user.qzone.qq.com/1181836535/infocenter");
    }
    dataInfo.cloudInfo.cloudCMDS = "No cmds";
}
