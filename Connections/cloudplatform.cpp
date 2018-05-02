#include "cloudplatform.h"

bool cloudLinkStatus = false;  //云平台连接状态

CloudPlatform::CloudPlatform(QString skyIP, QString sunPort)
{
    ticToc = 0;
    cloudServerIP = skyIP;             // 正式连接
//    cloudServerIP = getHostIpAddress();  // 本地连接测试
    cloudServerPort = sunPort.toInt();
    cloudSocket = new QTcpSocket();
    cloudTimer = new QTimer(this);
    hncPrivateTimer = new QTimer(this);
    userOperation = false;
    connect(cloudSocket,&QTcpSocket::connected,this,&CloudPlatform::afterConnected);

    connect(cloudTimer,&QTimer::timeout, this,&CloudPlatform::onTimeIsUp);
    cloudTimer->setTimerType(Qt::PreciseTimer);
    cloudTimer->setInterval(5000); // 5s一次发送传感器信息
    cloudTimer->start();

    connect(hncPrivateTimer,&QTimer::timeout,this,&CloudPlatform::onPrivateTimeUp);
    hncPrivateTimer->setTimerType(Qt::PreciseTimer);
    hncPrivateTimer->setInterval(200); // 200ms一次单独发送hnc信息
    hncPrivateTimer->start();
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
    dataXML::xmlStrRead(QString(recBuff));
    updateIni = new QSettings((QDir::currentPath()+"/update.ini", QSettings::IniFormat,this));
    QString cloudUrls = dataInfo.cloudInfo.cloudURLS.value("MODELBIN"); // 下载的URL地址
    double cloudCmds = dataInfo.cloudInfo.cloudCMDS.toDouble(); // 新版本号
    QStringList urlList = cloudUrls.split(",");
    if(urlList.size()==2) // url地址写入ini文件中
    {
        updateIni->setValue("/update/exeUrl",urlList[0]);
        updateIni->setValue("/update/exeUrl",urlList[1]);
    }
    updateIni->setValue("/update/newVersion",cloudCmds); // 新版本号写入ini文件中
}

// 云平台单方面断开连接
void CloudPlatform::afterDisconnected()
{
    qDebug()<<"6.1";
    if(userOperation) return; // 如果是用户操作，直接返回
    cloudSocket->abort(); // 如果是云平台单方面断开
    emit sendMsg("云平台已断开",-1);
    cloudLinkStatus = false;
    ticToc = 0;  // 开始计时
}

// 主定时器中断
void CloudPlatform::onTimeIsUp()
{
    ticToc++;
    if(cloudLinkStatus) // 如果连接上了云平台，发送信息
    {
        qDebug()<<"6.3";
        packageSensorsData();
        QString xmlOutStr = dataXML::xmlStrCreat(dataInfo);
        xmlOutStr += "end\n";
        cloudSocket->write(xmlOutStr.toLatin1());
        cloudSocket->flush();
    }
    else // 如果与云平台断开，定时10s重连
    {
        if(ticToc == 2) linkOnceAgain();
    }
}

// 数控系统专属定时器中断
void CloudPlatform::onPrivateTimeUp()
{
    // 如果已连接云平台和数控机床，每200ms发送一次机床信息包
    if((!cncWorkingStatus) && cloudLinkStatus) // 此处！号为调试用，正式使用需要去掉
    {
        qDebug()<<"6.5";
        packageHncData();
        QString xmlOutStr = dataXML::xmlHncCreat(hncInfo);
        xmlOutStr += "end\n";
        cloudSocket->write(xmlOutStr.toLatin1());
        cloudSocket->flush();
    }
}

 // 重新连接云平台
void CloudPlatform::linkOnceAgain()
{
    qDebug()<<"6.4";
    ticToc = 0;
    cloudSocket->connectToHost(QHostAddress(cloudServerIP), cloudServerPort);
    if(cloudSocket->errorString() != "Unknown error")
    {
        qDebug()<<cloudSocket->errorString();
    }
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

// 数控系统信息单独打包成XML格式
void CloudPlatform::packageHncData()
{
    // 包头信息
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString currentTime =current_date_time.toString("yyyyMMddhhmmsszzz");
    hncInfo.headInfo.time = currentTime;
    QString hostMac = getHostMacAddress();// 获取本机Mac地址
    hostMac.replace(QString("-"),QString(""));
    hostMac.replace(QString(":"),QString(""));
    hncInfo.headInfo.macId = hostMac;
    hncInfo.headInfo.msg = "Wuhan Heavy-duty machine tool ZK5540A";

    // 数控系统信息
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[0], QString::number(CNCInfo.ch,10));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[1], QString::number(CNCInfo.AXIS_X_POS,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[2], QString::number(CNCInfo.AXIS_Y_POS,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[3], QString::number(CNCInfo.AXIS_Z_POS,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[4], QString::number(CNCInfo.AXIS_MA_POS,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[5], QString::number(CNCInfo.AXIS_X_PWR,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[6], QString::number(CNCInfo.AXIS_Y_PWR,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[7], QString::number(CNCInfo.AXIS_Z_PWR,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[8], QString::number(CNCInfo.AXIS_MA_PWR,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[9], QString::number(CNCInfo.AXIS_X_FUHE,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[10],QString::number(CNCInfo.AXIS_Z_FUHE,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[11],QString::number(CNCInfo.AXIS_Y_FUHE,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[12],QString::number(CNCInfo.AXIS_MA_FUHE,10,4));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[13],QString::number(CNCInfo.feedrate,10,3));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[14],QString::number(CNCInfo.speed,10,0));
    hncInfo.cncInfo.CNCdata.insert(hncInfo.cncInfo.CNCkey[15],CNCInfo.PauseStatus);
}

// 所有传感器数据整理成XML格式
void CloudPlatform::packageSensorsData()
{
    // 包头信息
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString currentTime =current_date_time.toString("yyyyMMddhhmmsszzz");
    dataInfo.headInfo.time = currentTime;
    QString hostMac = getHostMacAddress();// 获取本机Mac地址
    hostMac.replace(QString("-"),QString(""));
    hostMac.replace(QString(":"),QString(""));
    dataInfo.headInfo.macId = hostMac;
    dataInfo.headInfo.msg = "WHUT CPS Sensors";

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
