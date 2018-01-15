#include "ds18b20sensor.h"

DS18B20_Node DS18B20_ALL_Node[DS18B20_Channel_Max][DS18B20_Index_Max];// DS18B20一号板数据集合
DS18B20_Node DS18B20_ADD_Node[DS18B20_Channel_Max][DS18B20_Index_Max];// DS18B20二号板数据集合
bool ds18WorkingStatus = false;
bool ds18No2WorkStatus = false;

QString dsmap[8][8] =               // 一号板ID列表
{
    {								// 通道1
        "28ffcdfa001604cb",
        "28ff7eeda0160301",
        "28ffa203011604fc",
        "28ffd7cc0016044b",
        "28ff6ba7a0160589",
        "28ff28f8041603d9",
        "28ff280c01160410",
        "28ff4a2305160375"
    },
    {								// 通道2
        "28ffaf1fb2150108",
        "28ff921db2150167",
        "28ff86eb041603f8",
        "28ffd3dd041603fe",
        "28ff71c100160479",
        "28ffb81cb2150311",
        "28ff6a0c0116047a",
        "28ffa2dd00160443"
    },
    {								// 通道3
        "28ff1d93a01603e3",
        "28ff78bea01603cd",
        "28ff4ec300160495",
        "28ffaddc001604a3",
        "28ffb6e500160474",
        "28ffa3f7001604e5",
        "28ff30f70016041c",
        "28ff95f7001604fd"
    },
    {								// 通道4
        "28ffe6ce00160405",
        "28ff783db215044f",
        "28ff52c600160449",
        "28ffed30b2150334",
        "28ffdcc20016042e",
        "28ffd827b215045f",
        "28ff3425051603b3",
        "28ff247eb2150310"
    },
    {								// 通道5
        "28ff76e500160456",
        "28ffa5c30016043f",
        "28ff2d22b2150195",
        "28ffcd0d01160497",
        "28ff55a7a01605af",
        "28ff56d7001604e1",
        "28ff3ccba0160491",
        "28ff0091a01604f7"
    },
    {								// 通道6
        "28ff80efa01605df",
        "28ffd7c6a0160325",
        "28ff04ada01605ec",
        "28fffdd4a0160582",
        "28ff87caa0160421",
        "28ff1d9da0160475",
        "28fffdada01605b9",
        "28ff44d3a01605b8"
    },
    {								// 通道7
        "28ff538da0160406",
        "28ff387da0160416",
        "28ffcacfa01605fb",
        "28ff16a8a0160592",
        "",
        "",
        "",
        ""
    },
    {								// 通道8
        "285c7ac7060000f3",
        "28ffafd9531704fa",
        "28ffd7da53170421",
        "28fffaee53170473",
        "28ff0524541704e2",
        "28fff1f05317042e",
        "28ff2e4d54170469",
        "28ff5ada53170406"
    }
};

QString dsNo2Map[8][9] =            // 二号板ID列表
{
    {								// 通道1
        "",
        "",
        "28ffd8ea53170406",
        "28ff65f153170409",
        "28ff1600541704ae",
        "28ff77325417043d",
        "28ff01d8531704e4",
        "28ff0048531704c8",
        ""
    },
    {								// 通道2
        "28ffa64754170487",
        "28ffb6d35317046e",
        "28ff4045541704c6",
        "28ffd41c54170425",
        "28ff2deb531704fd",
        "28ff66da531704a3",
        "28ff48da531704f9",
        "28ff643354170480",
        ""
    },
    {								// 通道3
        "28ffe44b53170485",
        "28ffed1054170440",
        "28ffda43541704c5",
        "28ff50f15317045f",
        "28fffa4754170433",
        "28ff16ee53170488",
        "28ffe9d7601704a0",
        "28ff0a1a541704d0",
        ""
    },
    {								// 通道4
        "28ffbb46531704e2",
        "28ff011f54170421",
        "28fff1495317042c",
        "28ffade553170423",
        "28ff62d8531704bb",
        "28ff8631541704de",
        "28ff3bff5317042b",
        "28ff90d85317049e",
        ""
    },
    {								// 通道5
        "28ff041a54170472",
        "28fff1d853170442",
        "28ffe0fa53170484",
        "28fff1125417041a",
        "28ff971f5417040a",
        "28ffa22654170487",
        "28ff3c1b54170447",
        "28ff2f3c54170483",
        ""
    },
    {								// 通道6
        "28ff6524541704f3",
        "28ff59025417042f",
        "28ff56ef531704ee",
        "28ff582554170414",
        "28ff1ff053170456",
        "28ff6f33541704f0",
        "28ffe04e54170461",
        "28ff5af1531704e2",
        "28fff7d953170451"          // 多余的一个，迫于大哥压力记录下来
    },
    {								// 通道7
        "28ffcded5317042e",
        "28ff533f5317043d",
        "28fffa01541704da",
        "28ff7331541704aa",
        "28ff07ff5317048e",
        "28ffd61d54170429",
        "28ff942054170496",
        "28ff1a2154170470",
        ""
    },
    {								// 通道8
        "28ffae4e5417042a",
        "28ffc83c54170408",
        "28ff6fde5317045e",
        "28ffe0d753170469",
        "28fffd46541704ed",
        "28ff393254170476",
        "28ffe37053170408",
        "28ff4fd953170420",
        ""
    }
};

DS18b20Sensor::DS18b20Sensor()  {}
DS18b20Sensor::~DS18b20Sensor() {}

DS18b20Sensor::DS18b20Sensor(QString ds18path, QString royalport, QString barcaport)
{
    errDS18B20Cnt = 0;
    dslinkport1 = royalport;
    dslinkport2 = barcaport;
    dsHostIp = getHostIpAddress();  // 获取本地IP
    ds18Dir = new QDir();
    newFullFragment = false;
    addNewFullFragment = false;
    totalRenewed = false;
    addTotalRenewed = false;
    ds18Server = new QTcpServer();
    ds18Socket = new QTcpSocket();
    ds18AddServer = new QTcpServer(this);
    ds18AddSocket = new QTcpSocket(this);

    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    dailyDir = ds18path+ "/WiFi温度数据"+"("+currentDate+")";
    dsNo1Dir = dailyDir+"/WiFi温度数据一号板"+"("+currentDate+")";
    dsNo2Dir = dailyDir+"/WiFi温度数据二号板"+"("+currentDate+")";
    // 如果不存在此文件夹,创建
    if(!ds18Dir->exists(dailyDir))   ds18Dir->mkdir(dailyDir);

    ds18ErrPath = dailyDir +"/DS18b20错误记录"+currentDate+".csv";
    QString errHeader = "时间,设备号,通道号,传感器号,ID号,当前温度,上次温度,错误计数,错误原因";
    if(!QFile::exists(ds18ErrPath))  // 如果不存在此文件
    {
        writeFile(ds18ErrPath,errHeader);
    }

    listenDS18b20();
    listenDS18Add();
    connect(ds18Server,&QTcpServer::newConnection,this,&DS18b20Sensor::newClientConnection);
    connect(ds18AddServer,&QTcpServer::newConnection,this,&DS18b20Sensor::addNewClientConnection);
}

// 检查某个ID是否在ID列表中
int DS18b20Sensor::checkDchIDInList(QString IdIn, int channel,int clientNo)
{
    if(clientNo == 1)
    {
        for (int i = 0; i < DS18B20_Index_Max; i++)
        {
            if (IdIn == dsmap[channel][i]) return i;
        }
    }
    else
    {
        for (int i = 0; i < DS18B20_Index_Max+1; i++)   //某些通道九个点
        {
            if (IdIn == dsNo2Map[channel][i]) return i;
        }
    }
    return -1;
}

// 开始监听传感器一号板1001端口
bool DS18b20Sensor::listenDS18b20()
{
    short port = dslinkport1.toInt();
    if(!ds18Server->listen(QHostAddress(dsHostIp), port))
    {
        qDebug()<<ds18Server->errorString();
        return false;
    }

    if(!ds18Dir->exists(dsNo1Dir))
    {
        ds18Dir->mkdir(dsNo1Dir);
    }

    return true;
}

// 当传感器一号板连接到补偿器
void DS18b20Sensor::newClientConnection()
{
    ds18Socket = ds18Server->nextPendingConnection();  // 获取客户端连接
    emit sendMsg(NULL,1);                              // 一号板连接成功
    connect(ds18Socket, &QTcpSocket::readyRead, this, &DS18b20Sensor::readDS18Data);
    connect(ds18Socket, &QTcpSocket::disconnected, this, &DS18b20Sensor::socketDisconnected);
}

// 读取传感器一号板发送的数据
void DS18b20Sensor::readDS18Data()
{
    qDebug()<<"2.1";
    ds18WorkingStatus = true;                      // 在此判定一号板已连接
    QByteArray buffer;
    buffer = ds18Socket->readAll();                  // 读取本次全部数据
    dataALL+=buffer;                                 // 存入数据队列
    buffer.clear();                                  // 缓存清空
    if(!newFullFragment)                             // 开始接收后,检测有没有“S0,00”这5个字节
    {
        int headerIndex;
        if(dataALL.size()<5) return;                 // 如果不够5个字节,退出
        else
        {
            headerIndex = dataALL.indexOf("S0,00");    // 检索第一次出现“S0,00”的位置
            if(headerIndex == -1)  return;             // 还没有收到“S0,00”,退出
            else                                       // 收到了，表明新一轮发送开始
            {
                newFullFragment = true;
                dataALL = dataALL.mid(headerIndex);    // 丢弃“S0,00”之前的部分
                totalRenewed = true;
            }
        }
    }

    QList<QByteArray> nodeList = dataALL.split('\n');// 按‘\n’拆分
    int itemNum = nodeList.size();                   // 拆分后的项数
    if(itemNum == 1) return;                         // 不足一帧（没有'\n'）,退出，下次再来
    if(itemNum == 2)                                 // 一帧多一点
    {
        processData(nodeList[0],1);                  // 处理一次
        dataALL.clear();
        dataALL = nodeList[1];
    }
    if(itemNum > 2)                                  // 多帧
    {
        for(int i=0; i<itemNum-1; i++)
        {
            processData(nodeList[i],1);
        }
        dataALL.clear();
        dataALL = nodeList[itemNum-1];
    }
}

// 传感器一号板socket连接断开
void DS18b20Sensor::socketDisconnected()
{
    emit sendMsg(NULL,-1);
    ds18Socket->abort();
    ds18WorkingStatus = false;
}

// 开始监听传感器二号板3003端口
bool DS18b20Sensor::listenDS18Add()
{
    short port = dslinkport2.toInt();
    if(!ds18AddServer->listen(QHostAddress(dsHostIp), port))
    {
        qDebug()<<ds18AddServer->errorString();
        return false;
    }

    if(!ds18Dir->exists(dsNo2Dir))
    {
        ds18Dir->mkdir(dsNo2Dir);
    }

    return true;
}

// 当传感器二号板连接到补偿器
void DS18b20Sensor::addNewClientConnection()
{
    ds18AddSocket = ds18AddServer->nextPendingConnection();  // 获取客户端连接
    emit sendMsg(NULL,2);
    connect(ds18AddSocket, &QTcpSocket::readyRead, this, &DS18b20Sensor::readDS18AddData);
    connect(ds18AddSocket, &QTcpSocket::disconnected, this, &DS18b20Sensor::addSocketDisconnected);
}

// 读取传感器二号板发送的数据
void DS18b20Sensor::readDS18AddData()
{
    qDebug()<<"2.2";
    ds18No2WorkStatus = true;                               // 在此判定二号板已连接
    QByteArray buffer;
    buffer = ds18AddSocket->readAll();                      // 读取本次全部数据
    dataAddALL+=buffer;                                     // 存入数据队列
    if(!addNewFullFragment)                                 // 开始接收后,检测有没有“S0,00”这5个字节
    {
        int headerIndex;
        if(dataAddALL.size()<5) return;                     // 如果不够5个字节,退出
        else
        {
            headerIndex = dataAddALL.indexOf("S0,00");      // 检索第一次出现“S0,00”的位置
            if(headerIndex == -1)  return;                  // 还没有收到“S0,00”,退出
            else                                            // 收到了，表明新一轮发送开始
            {
                addNewFullFragment = true;
                dataAddALL = dataAddALL.mid(headerIndex);   // 丢弃“S0,00”之前的部分
            }
        }
    }

    QList<QByteArray> nodeList = dataAddALL.split('\n');    // 按‘\n’拆分
    int itemNum = nodeList.size();                          // 拆分后的项数
    if(itemNum == 1) return;                                // 不足一帧（没有'\n'）,退出，下次再来
    if(itemNum == 2)                                        // 一帧多一点
    {
        processData(nodeList[0],2);
        dataAddALL.clear();
        dataAddALL = nodeList[1];
    }
    if(itemNum > 2)                                         // 多帧
    {
        for(int i=0; i<itemNum-1; i++)
        {
            processData(nodeList[i],2);
        }
        dataAddALL.clear();
        dataAddALL = nodeList[itemNum-1];
    }
}

// 传感器二号板socket连接断开
void DS18b20Sensor::addSocketDisconnected()
{
    emit sendMsg(NULL,-2);
    ds18AddSocket->abort();
    ds18No2WorkStatus = false;
}

// 单节点字符串解析方法  字符串格式示例：S0,00,28ff7eeda0160301,1,0.00\r
void DS18b20Sensor::processData(QByteArray a,int clientNo)
{
    qDebug()<<"2";
    if(a.size()<30 || a.size()>32)                              // 异常帧
    {
        emit sendMsg("数据帧大小不在正常范围内",clientNo);
        return;
    }
    if(a[0]!='S' || a[a.size()-1]!='\r')
    {
        emit sendMsg("不符合规定格式",clientNo);
        return;
    }
    a = a.mid(1);                                               // 去除首部'S'
    QList<QByteArray> paragraph = a.split(',');                 // 按','分割
    QString ID, temperature;								    // ID和温度
    unsigned int channel = 0, indx = 0, sign = 0;				// 通道,序列号，正负号

    channel = paragraph[0].toInt();                             // 通道号:0~7
    indx = paragraph[1].toInt();                                // 序列号:00~08
    ID = paragraph[2];                                          // id号
    sign = paragraph[3].toInt();                                // 正负号
    int signIndex = paragraph[4].indexOf('\r');
    temperature = paragraph[4].left(signIndex);                 // 温度
    if(sign == 0){temperature = "-"+temperature;}               // 此项为0代表负数

    if(((channel >= 0) && (channel <= 7)) && ((indx >= 0) && (indx <= 8)))
    {
        int IDseries = checkDchIDInList(ID, channel,clientNo);
        if (IDseries == -1)  return;                            // 如果数据库中找不到此ID，退出
        else
        {
            if(clientNo == 1)
            {
                DS18B20_ALL_Node[channel][IDseries].temperature = temperature;
                DS18B20_ALL_Node[channel][IDseries].ID = ID;
                recordSingleSensor(1,channel,ID,temperature);
            }
            else if(clientNo == 2)
            {
                if(IDseries==8)   // 记录多出来的那一个，记完就跑
                {
                   recordSingleSensor(2,channel,ID,temperature);
                   return;
                }
                DS18B20_ADD_Node[channel][IDseries].temperature = temperature;
                DS18B20_ADD_Node[channel][IDseries].ID = ID;
                recordSingleSensor(2,channel,ID,temperature);
            }

            double nowdat = temperature.toDouble();
            unsigned int errtype;
            if ( (nowdat<-10) || (nowdat>80) ) 	                // 异常情况
            {
                errDS18B20Cnt++;
                if(clientNo == 1)
                {
                    if(abs(nowdat-DS18B20_ALL_Node[channel][IDseries].temperature.toDouble())>=20)
                    {
                        errtype=2;
                    }
                    else
                    {
                        errtype=1;
                    }
                }
                else if(clientNo == 2)
                {
                    if(abs(nowdat-DS18B20_ADD_Node[channel][IDseries].temperature.toDouble())>=20)
                    {
                        errtype=2;
                    }
                    else
                    {
                        errtype=1;
                    }
                }
                recordErrors(clientNo,channel,IDseries,temperature,ID,errDS18B20Cnt,errtype);
                if (errDS18B20Cnt >= 19941008){ errDS18B20Cnt = 0;}
            }
        }
    }
}

// 迫于大哥(@fjc)威严，被迫为每一个传感器建立一个文件夹
void DS18b20Sensor::recordSingleSensor(int clientNo, unsigned int chan, QString id, QString temper)
{
    QString fileName,content;
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    if(clientNo == 1)
    {
        fileName = dsNo1Dir+"/通道"+QString::number(chan+1,10);
        if(ds18Dir->exists(fileName))
        {
            fileName = fileName+"/"+id+".csv";
            content = currentDate+","+temper;
            writeFile(fileName,content);
        }
        else
        {
            if(ds18Dir->mkdir(fileName))
            {
                fileName = fileName+"/"+id+".csv";
                content = currentDate+","+temper;
                writeFile(fileName,content);
            }
        }
    }
    else if(clientNo == 2)
    {
        fileName = dsNo2Dir+"/通道"+QString::number(chan+1,10);
        if(ds18Dir->exists(fileName))
        {
            fileName = fileName+"/"+id+".csv";
            content = currentDate+","+temper;
            writeFile(fileName,content);
        }
        else
        {
            if(ds18Dir->mkdir(fileName))
            {
                fileName = fileName+"/"+id+".csv";
                content = currentDate+","+temper;
                writeFile(fileName,content);
            }
        }
    }
}

// 记录错误情况
void DS18b20Sensor::recordErrors(int client,unsigned int chan, unsigned int ind, QString temper, QString id, unsigned long count,unsigned int errType)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString errContent; // 这一次的错误内容
    QString errHint;    // 错误提示
    errContent = currentTime+",电类传感器"+QString::number(client)+"号板,"
            +QString::number(chan,10)+","+QString::number(ind,10)
            +","+id+","+temper+",";
    switch (errType)
    {
        case 1: errHint = "温度不在正常范围";
               break;
        case 2: errHint = "温度跳变过大";
        default: break;
    }

    if(client == 1)
    {

        errContent = errContent+DS18B20_ALL_Node[chan][ind].temperature+","
                +QString::number(count,10)+","+errHint;
    }
    if(client == 2)
    {
        errContent = errContent+DS18B20_ADD_Node[chan][ind].temperature+","
                +QString::number(count,10)+","+errHint;
    }
    writeFile(ds18ErrPath,errContent);
}

// 释放TCP内存
void DS18b20Sensor::deleteTcpServer()
{
    ds18WorkingStatus = false;
    ds18No2WorkStatus = false;
    ds18Socket->close();
    ds18Server->close();
    ds18AddSocket->close();
    ds18AddServer->close();
    delete ds18Server;
    delete ds18AddServer;
    delete ds18Dir;
    emit sendMsg("电类温度传感器服务端关闭",0);
}

// 创建新的一天的文件
void DS18b20Sensor::niceNewDay(QString path)
{
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    dailyDir = path+"/WiFi温度数据"+"("+currentDate+")";
    dsNo1Dir = dailyDir+"/WiFi温度数据一号板("+currentDate+")";
    dsNo2Dir = dailyDir+"/WiFi温度数据二号板("+currentDate+")";
    ds18ErrPath = dailyDir +"/DS18b20错误记录"+currentDate+".csv";
    QString errHeader = "时间,设备号,通道号,传感器号,ID号,当前温度,上次温度,错误计数,错误原因";
    // 新建电类传感器总目录
    if(!ds18Dir->exists(dailyDir))  ds18Dir->mkdir(dailyDir);
    // 新建错误记录csv文件
    if(!QFile::exists(ds18ErrPath)) writeFile(ds18ErrPath,errHeader);
    // 新建一号板文件夹
    if(!ds18Dir->exists(dsNo1Dir))  ds18Dir->mkdir(dsNo1Dir);
    // 新建二号板文件夹
    if(!ds18Dir->exists(dsNo2Dir))  ds18Dir->mkdir(dsNo2Dir);
}
