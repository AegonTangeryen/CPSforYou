#include "envisensor.h"

Env_Node ENV_ALL_Node[Env_Number_Max];
bool envWorkingStatus = false;

QString envMap[4] =
{
    "28f3deee050000a0",
    "28ff401e0516031d",
    "28ff2cf700160441",
    "28ff7cff001604c8"
};

EnviSensor::EnviSensor()    {}

EnviSensor::EnviSensor(QString path, QString globalPort)
{
    envHostIp = getHostIpAddress();  // 获取本地IP
    envPort = globalPort.toInt();
    envNewFullFragment = false;
    errCnt = 0;
    envLock = new QMutex();
    envDir = new QDir();
    envServer = new QTcpServer();
    envSocket = new QTcpSocket();

    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    environmentPath = path+"/环境温度总集"+"("+currentDate+")";
    if(!envDir->exists(environmentPath))
    {
        envDir->mkdir(environmentPath);
    }
    listenEnvironment();
    connect(envServer,&QTcpServer::newConnection,this,&EnviSensor::newClientConnection);
}

// 检查某个ID是否在ID列表中
int EnviSensor::checkDchIDInList(QString IdIn)
{
    for (int i = 0; i < Env_Number_Max; i++)
    {
        if (IdIn == envMap[i]) return i;
    }
    return -1;
}

// 开始监听传感器2002端口
bool EnviSensor::listenEnvironment()
{
    if(!envServer->listen(QHostAddress(envHostIp), envPort))
    {
        qDebug()<<envServer->errorString();
        return false;
    }
    return true;
}

// 当传感器连接到补偿器
void EnviSensor::newClientConnection()
{
    envSocket = envServer->nextPendingConnection();  //获取客户端连接
    emit sendMsg("环境温度已连接",1);
    connect(envSocket, &QTcpSocket::readyRead, this, &EnviSensor::readEnvData);
    connect(envSocket, &QTcpSocket::disconnected, this, &EnviSensor::socketDisconnected);
}

// 读取传感器发送的数据
void EnviSensor::readEnvData()
{
    qDebug()<<"3";
    envWorkingStatus = true;
    QByteArray buffer;
    buffer = envSocket->readAll();                      // 读取本次全部数据
    EnvDataALL+=buffer;                                 // 存入数据队列
    buffer.clear();                                     // 缓存清空
    if(!envNewFullFragment)                             // 开始接收后,检测有没有“S0,00”这5个字节
    {
        int headerIndex;
        if(EnvDataALL.size()<5) return;                 // 如果不够5个字节,退出
        else
        {
          headerIndex = EnvDataALL.indexOf("S0,00");    // 检索第一次出现“S0,00”的位置
          if(headerIndex == -1)  return;                // 还没有收到“S0,00”,退出
          else                                          // 收到了，表明新一轮发送开始
          {
              envNewFullFragment = true;
              EnvDataALL = EnvDataALL.mid(headerIndex); // 丢弃“S0,00”之前的部分
          }
        }
    }

    QList<QByteArray> nodeList = EnvDataALL.split('\n');// 按‘\n’拆分
    int itemNum = nodeList.size();                      // 拆分后的项数
    if(itemNum == 1) return;                            // 不足一帧（没有'\n'）,退出，下次再来
    if(itemNum == 2)                                    // 一帧多一点
    {
        processData(nodeList[0]);
        EnvDataALL.clear();
        EnvDataALL = nodeList[1];                       // 处理一次
    }
    if(itemNum > 2)                                     // 多帧
    {
        for(int i=0; i<itemNum-1; i++)
        {
            processData(nodeList[i]);
        }
        EnvDataALL.clear();
        EnvDataALL = nodeList[itemNum-1];
    }
}

// 传感器socket连接断开
void EnviSensor::socketDisconnected()
{
    emit sendMsg("环境温度连接断开",-1);
    envSocket->abort();
    envWorkingStatus = false;
}

// 解析每个通道
void EnviSensor::processData(QByteArray a)
{
    if(a.size()<30 || a.size()>31)                              // 异常帧
    {
        sendMsg("数据帧大小不在正常范围内",3);
        return;
    }
    if(a[0]!='S' || a[a.size()-1]!='\r')
    {
        sendMsg("不符合规定格式",3);
        return;
    }
    a = a.mid(1);                                               // 去除首部'S'
    QList<QByteArray> paragraph = a.split(',');                 // 按','分割
    if(paragraph.size()!=5)  // 异常帧,退出，防止崩溃
    {
        qDebug()<<"envFalut";
        return;
    }
    QString ID, temperature;								    // ID和温度
    unsigned int channel = 0, indx = 0, sign = 0;				// 通道,序列号，正负号

    channel = paragraph[0].toInt();                             // 通道号:0~1
    indx = paragraph[1].toInt();                                // 序列号:00~01
    ID = paragraph[2];                                          // id号
    sign = paragraph[3].toInt();                                // 正负号
    int signIndex = paragraph[4].indexOf('\r');
    temperature = paragraph[4].left(signIndex);                  // 温度
    if(sign == 0){temperature = "-"+temperature;}

    if(((channel >= 0) && (channel <= 1)) && ((indx >= 0) && (indx <= 1)))
    {
        int IDseries = checkDchIDInList(ID);
        if (IDseries == -1)  return;            // 如果列表中找不到ID，退出
        else
        {
            bool ok;
            double nowdat = temperature.toDouble(&ok);
            if(ok) // 转换成功
            {
                if (nowdat >= -10 && nowdat <= 85) // 正常情况
                {
                    ENV_ALL_Node[IDseries].temperature = temperature;
                    ENV_ALL_Node[IDseries].ID = ID;
                    recordSingleSensor(ID,temperature);
                }
                else                               // 异常情况
                {
                    errCnt++;
                    if (errCnt >= 19941008){errCnt = 0;}
                    temperature = QString::number(85,10); // 异常值默认为85度
                    ENV_ALL_Node[IDseries].ID = ID;
                    ENV_ALL_Node[IDseries].temperature = temperature;
                }
            }
        }
    }
}

// 为每个传感器建立一个单独的文件
void EnviSensor::recordSingleSensor(QString id, QString temper)
{
    QString fileName,content;
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    fileName = environmentPath+"/"+id+".csv";
    content = currentDate+","+temper;
    writeFile(fileName,content);
}

// 释放TCP内存
void EnviSensor::deleteEnvServer()
{
    envWorkingStatus = false;
    envServer->close();
    envSocket->close();
    delete envServer;
    delete envDir;
    delete envLock;
    sendMsg(NULL,9);
}

// 创建新的一天的文件
void EnviSensor::niceNewDay(QString path)
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString currentDate = current_date_time.toString("yyyy-MM-dd hh：mm：ss");
    environmentPath = path+"/环境温度总集"+"("+currentDate+")";
    if(!envDir->exists(environmentPath))
    {
        envDir->mkdir(environmentPath);
    }
}
