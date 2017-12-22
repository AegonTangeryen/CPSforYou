#include "fbgsensos.h"

QString FBG_ALL[FBG_Channel_Max][FBG_Index_Max];   // FBG波长集合
bool fbgWorkingStatus = false;

FBGSensos::FBGSensos() {}

FBGSensos::FBGSensos(QString path)
{
    fbgIp = "192.168.0.119";
    fbgPort = 4010;
//    fbgIp = getHostIpAddress();
//    fbgPort = 1994;
    fbgfileDir = path;
    fbgSocket = new QUdpSocket(this);
    fbgLock = new QMutex();
    fbgDir = new QDir();
    fbgSocket->bind(QHostAddress(fbgIp), fbgPort);
    qDebug()<<fbgSocket->errorString();
    linkFbg();
    connect(fbgSocket, &QUdpSocket::readyRead, this,&FBGSensos::readFbgData);
}

// 连接FBG解调仪
void FBGSensos::linkFbg()
{
    char connectOrder[2] = {0x01,0x02};
    char startOrder[4] = {0x01,0x0a,0x55,0x00};
    char stopOrder[4] = {0x01,0x0a,0x00,0x00};
    fbgSocket->writeDatagram(stopOrder,4,QHostAddress(fbgIp),fbgPort);        // 关闭解调仪
    fbgSocket->writeDatagram(connectOrder,2,QHostAddress(fbgIp),fbgPort);     // 连接解调仪
    fbgSocket->writeDatagram(startOrder,4,QHostAddress(fbgIp),fbgPort);       // 启动解调仪

    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    fbgfileDir = fbgfileDir+"/FBG波长数据"+"("+currentDate+")";
    if(!fbgDir->exists(fbgfileDir))
    {
        fbgDir->mkdir(fbgfileDir);
    }
    fbgWorkingStatus = true;
}

// 读取socket缓存数据
void FBGSensos::readFbgData()
{
    char recBuf[1000];
    while (fbgSocket->hasPendingDatagrams())
    {
        fbgSocket->readDatagram(recBuf,999); // 数据接收在recBuff里
    }

    if(strlen(recBuf) == 0)                  // 如果啥也没有收到，判定udp断开
    {
        fbgWorkingStatus = false;
        emit sendPara2Ui(0);
        return;
    }
    else
    {
        fbgWorkingStatus = true;
        emit sendPara2Ui(1);
    }

    if (recBuf[0] == '0' || recBuf[1] == 'E')   return;
    if (recBuf[0] == 0x01 && recBuf[1] == 0x02) return;
    int currentSignal = ((recBuf[1] == 12) ? 0 : 1);						// 12为前16个通道，14为后16个
    for (int i = 0; i<16; i++)												// 获取16个通道的数据
    {
        char idxNum = recBuf[3 + 62 * i];									// 某通道的节点数量
        int startIdx = 4 + 62 * i;											// 第一个点的位置
        for (int j = 0; j<30; j++)											// 每个通道30个节点
        {
            unsigned char highInfo = recBuf[startIdx + j * 2];				// 高八位
            unsigned char lowInfo = recBuf[startIdx + j * 2 + 1];			// 低八位
            double fbgw = 1520.0 + (256.0 * lowInfo + highInfo) / 1000.0;	// fbg转换公式
            if (fbgw<1500)
            {
                qDebug("Blood and fire");
            }
            if (j < FBG_Index_Max)											// 只保存20个点
            {
                if (j >= idxNum) fbgw = 0.0;
                QString fbgDataStr = QString::number(fbgw,10,3);            // 3位小数
                int channel = i + currentSignal * 16;
                FBG_ALL[channel][j] = fbgDataStr;
                recordSingleSensor(channel,j,fbgDataStr);
            }
        }
    }
    memset(recBuf,0x00,1000);                                               // 清空接收缓存
}

// 创建新的一天的文件夹
void FBGSensos::niceNewDay(QString path)
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString currentDate = current_date_time.toString("yyyy-MM-dd hh：mm：ss");
    fbgfileDir = path+"/FBG波长数据"+"("+currentDate+")";
    if(!fbgDir->exists(fbgfileDir))
    {
        fbgDir->mkdir(fbgfileDir);
    }
}

// 迫于大哥(@fjc)压力，为每个通道的每个点建立一个文件
void FBGSensos::recordSingleSensor(unsigned int channel, unsigned int index, QString FBGwave)
{
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString furtherFileName,content;
    furtherFileName = fbgfileDir+"/通道"+QString::number(channel+1,10);
    if(fbgDir->exists(furtherFileName))
    {
        furtherFileName = furtherFileName+"/"+QString::number(index+1,10)+".csv";
        content = currentDate+","+FBGwave;
        writeFile(furtherFileName,content);
    }
    else
    {
        if(fbgDir->mkdir(furtherFileName))
        {
            furtherFileName = furtherFileName+"/"+QString::number(index+1,10)+".csv";
            content = currentDate+","+FBGwave;
            writeFile(furtherFileName,content);
        }
    }
}

// 关闭FBG
void FBGSensos::deleteUdpSocket()
{
    fbgWorkingStatus = false;
    fbgSocket->close();
    delete fbgLock;
    delete fbgSocket;
    delete fbgDir;
    emit sendPara2Ui(-1);
}

