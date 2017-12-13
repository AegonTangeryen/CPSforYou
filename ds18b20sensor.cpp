#include "ds18b20sensor.h"

DS18B20_Node DS18B20_ALL_Node[DS18B20_Channel_Max][DS18B20_Index_Max];//DS18B20一号板数据集合
DS18B20_Node DS18B20_ADD_Node[DS18B20_Channel_Max][DS18B20_Index_Max];//DS18B20二号板数据集合
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

QString dsNo2Map[8][8] =            // 二号板ID列表
{
    {								// 通道1
        "",
        "",
        "28ffd8ea53170406",
        "28ff65f153170409",
        "28ff1600541704ae",
        "28ff77325417043d",
        "28ff01d8531704e4",
        "28ff0048531704c8"
    },
    {								// 通道2
        "28ffa64754170487",
        "28ffb6d35317046e",
        "28ff4045541704c6",
        "28ffd41c54170425",
        "28ff2deb531704fd",
        "28ff66da531704a3",
        "28ff48da531704f9",
        "28ff643354170480"
    },
    {								// 通道3
        "28ffe44b53170485",
        "28ffed1054170440",
        "28ffda43541704c5",
        "28ff50f15317045f",
        "28fffa4754170433",
        "28ff16ee53170488",
        "28ffe9d7601704a0",
        "28ff0a1a541704d0"
    },
    {								// 通道4
        "28ffbb46531704e2",
        "28ff011f54170421",
        "28fff1495317042c",
        "28ffade553170423",
        "28ff62d8531704bb",
        "28ff8631541704de",
        "28ff3bff5317042b",
        "28ff90d85317049e"
    },
    {								// 通道5
        "28ff041a54170472",
        "28fff1d853170442",
        "28ffe0fa53170484",
        "28fff1125417041a",
        "28ff971f5417040a",
        "28ffa22654170487",
        "28ff3c1b54170447",
        "28ff2f3c54170483"
    },
    {								// 通道6
        "28fff7d953170451",
        "28ff5af1531704e2",
        "28ffe04e54170461",
        "28ff6f33541704f0",
        "28ff6524541704f3",
        "28ff582554170414",
        "28ff56ef531704ee",
        "28ff59025417042f"
    },
    {								// 通道7
        "28ffcded5317042e",
        "28ff533f5317043d",
        "28fffa01541704da",
        "28ff7331541704aa",
        "28ff07ff5317048e",
        "28ffd61d54170429",
        "28ff942054170496",
        "28ff1a2154170470"
    },
    {								// 通道8
        "28ffae4e5417042a",
        "28ffc83c54170408",
        "28ff6fde5317045e",
        "28ffe0d753170469",
        "28fffd46541704ed",
        "28ff393254170476",
        "28ffe37053170408",
        "28ff4fd953170420"
    }
};

DS18b20Sensor::DS18b20Sensor()  {}
DS18b20Sensor::~DS18b20Sensor() {}

DS18b20Sensor::DS18b20Sensor(QString ds18path)
{
    processCnt = 0;
    errDS18B20Cnt = 0;
    processCntNo2 = 0;
    dslinkport1 = "1001";
    dslinkport2 = "3003";
    //dsHostIp = "192.168.0.50";
    dsHostIp = "10.141.51.70";
    dataALL.clear();
    dataAddALL.clear();
    ds18Dir = new QDir();
    newFullFragment = false;
    addNewFullFragment = false;
    ds18Server = new QTcpServer(this);
    ds18Socket = new QTcpSocket(this);
    ds18AddServer = new QTcpServer(this);
    ds18AddSocket = new QTcpSocket(this);

    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    dailyDir = ds18path+ "/WiFi温度数据"+"("+currentDate+")";
    dsNo1Dir = dailyDir+"/WiFi温度数据一号板"+"("+currentDate+")";
    dsNo2Dir = dailyDir+"/WiFi温度数据二号板"+"("+currentDate+")";

    if(ds18Dir->exists(dailyDir)) qDebug()<<"根目录已存在!";
    else
    {
        if(ds18Dir->mkdir(dailyDir)) qDebug()<<"根目录创建成功！";
    }

    ds18ErrPath = dailyDir +"/DS18b20错误记录"+currentDate+".csv";
    QString errHeader = "时间,设备号,通道号,传感器号,ID号,当前温度,上次温度,错误计数,错误原因";
    if(QFile::exists(ds18ErrPath)) qDebug()<<"文件已存在！";
    else
    {
        if(writeFile(ds18ErrPath,errHeader))
        qDebug()<<"DS18b20错误记录文件创建成功";
    }

    if(listenDS18b20()) qDebug()<<endl<<"1001端口监听成功";
    if(listenDS18Add()) qDebug()<<endl<<"3003端口监听成功";
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
        for (int i = 0; i < DS18B20_Index_Max; i++)
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

    if(ds18Dir->exists(dsNo1Dir)) qDebug()<<"电类传感器一号板目录已存在!";
    else
    {
        if(ds18Dir->mkdir(dsNo1Dir)) qDebug()<<"电类传感器一号板目录创建成功！";
    }

    return true;
}

// 当传感器一号板连接到补偿器
void DS18b20Sensor::newClientConnection()
{
    ds18Socket = ds18Server->nextPendingConnection();  //获取客户端连接
    ds18WorkingStatus = true;
    qDebug() << "DS18b20一号板已连接!";
    emit sendMsg("DS18b20一号板已连接",1);
    connect(ds18Socket, &QTcpSocket::readyRead, this, &DS18b20Sensor::readDS18Data);
    connect(ds18Socket, &QTcpSocket::disconnected, this, &DS18b20Sensor::socketDisconnected);
}

// 读取传感器一号板发送的数据
void DS18b20Sensor::readDS18Data()
{
    QByteArray buffer;
    buffer = ds18Socket->readAll();                  // 读取本次全部数据
    qDebug()<<"一号板收到:"<<endl<<buffer;

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
          }
        }
    }

    QList<QByteArray> nodeList = dataALL.split('\n');// 按‘\n’拆分
    int itemNum = nodeList.size();                   // 拆分后的项数
    if(itemNum == 1) return;                         // 不足一帧（没有'\n'）,退出，下次再来
    if(itemNum == 2)                                 // 一帧多一点
    {
        processData(nodeList[0],1);
        dataALL.clear();
        dataALL = nodeList[1];
        processCnt+=1;                               // 处理一次
    }
    if(itemNum > 2)                                  // 多帧
    {
        for(int i=0; i<itemNum-1; i++)
        {
            processData(nodeList[i],1);
        }
        dataALL.clear();
        dataALL = nodeList[itemNum-1];
        processCnt+=(itemNum-1);
    }

    if(processCnt >= 52)
    {
        processCnt =0;
    }
}

// 传感器一号板socket连接断开
void DS18b20Sensor::socketDisconnected()
{
    qDebug() << "DS18b20一号板连接断开!";
    emit sendMsg("DS18b20一号板连接断开",-1);
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

    if(ds18Dir->exists(dsNo2Dir)) qDebug()<<"电类传感器2号板目录已存在!";
    else
    {
        if(ds18Dir->mkdir(dsNo2Dir)) qDebug()<<"电类传感器2号板目录创建成功！";
    }

    return true;
}

// 当传感器二号板连接到补偿器
void DS18b20Sensor::addNewClientConnection()
{
    ds18AddSocket = ds18AddServer->nextPendingConnection();  //获取客户端连接
    ds18No2WorkStatus = true;
    qDebug() << "DS18b20二号板已连接!";
    emit sendMsg("DS18b20二号板已连接",2);
    connect(ds18AddSocket, &QTcpSocket::readyRead, this, &DS18b20Sensor::readDS18AddData);
    connect(ds18AddSocket, &QTcpSocket::disconnected, this, &DS18b20Sensor::addSocketDisconnected);
}

// 读取传感器二号板发送的数据
void DS18b20Sensor::readDS18AddData()
{
    QByteArray buffer;
    buffer = ds18AddSocket->readAll();                  // 读取本次全部数据
    qDebug()<<"二号板收到:"<<endl<<buffer;

    dataAddALL+=buffer;                                 // 存入数据队列
    if(!addNewFullFragment)                             // 开始接收后,检测有没有“S0,00”这5个字节
    {
        int headerIndex;
        if(dataAddALL.size()<5) return;                 // 如果不够5个字节,退出
        else
        {
          headerIndex = dataAddALL.indexOf("S0,00");    // 检索第一次出现“S0,00”的位置
          if(headerIndex == -1)  return;             // 还没有收到“S0,00”,退出
          else                                       // 收到了，表明新一轮发送开始
          {
              addNewFullFragment = true;
              dataAddALL = dataAddALL.mid(headerIndex);    // 丢弃“S0,00”之前的部分
          }
        }
    }
    QList<QByteArray> nodeList = dataAddALL.split('\n');// 按‘\n’拆分
    int itemNum = nodeList.size();                   // 拆分后的项数
    if(itemNum == 1) return;                         // 不足一帧（没有'\n'）,退出，下次再来
    if(itemNum == 2)                                 // 一帧多一点
    {
        processData(nodeList[0],2);
        dataAddALL.clear();
        dataAddALL = nodeList[1];
        processCntNo2+=1;                               // 处理一次
    }
    if(itemNum > 2)                                  // 多帧
    {
        for(int i=0; i<itemNum-1; i++)
        {
            processData(nodeList[i],2);
        }
        dataAddALL.clear();
        dataAddALL = nodeList[itemNum-1];
        processCntNo2+=(itemNum-1);
    }
    if(processCntNo2 >= 64)
    {
        processCntNo2 = 0;
    }
}

// 传感器二号板socket连接断开
void DS18b20Sensor::addSocketDisconnected()
{
    qDebug() << "DS18b20二号板连接断开!";
    emit sendMsg("DS18b20二号板连接断开",-2);
    ds18AddSocket->abort();
    ds18No2WorkStatus = false;
}

// 解析每个通道
void DS18b20Sensor::processData(QByteArray a,int clientNo)
{
    //字符串格式示例：S0,00,28ff7eeda0160301,1,0.00\r
    if(a.size()<30 || a.size()>32)                              // 异常帧
    {
        qDebug()<<"数据帧大小不在正常范围内";
        return;
    }
    if(a[0]!='S' || a[a.size()-1]!='\r')
    {
        qDebug()<<"不符合规定格式";
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
    temperature = paragraph[4].left(signIndex);                  // 温度
    if(sign == 0){temperature = "-"+temperature;}

    if(((channel >= 0) && (channel <= 7)) && ((indx >= 0) && (indx <= 7)))
    {
        int IDseries = checkDchIDInList(ID, channel,clientNo);
        if (IDseries == -1)  return;            // 如果数据库中找不到ID，退出
        else
        {
            double nowdat = temperature.toDouble();
            if (nowdat >= -10 && nowdat <= 80) 	                    // 正常情况
            {
                if(clientNo == 1)
                {
                    DS18B20_ALL_Node[channel][IDseries].temperature = temperature;
                    DS18B20_ALL_Node[channel][IDseries].ID = ID;
                    recordSingleSensor(1,channel,ID,temperature);
                }
                else if(clientNo == 2)
                {
                    DS18B20_ADD_Node[channel][IDseries].temperature = temperature;
                    DS18B20_ADD_Node[channel][IDseries].ID = ID;
                    recordSingleSensor(2,channel,ID,temperature);
                }
            }
            else                                                    // 异常情况
            {
                errDS18B20Cnt++;
                if (errDS18B20Cnt >= 100000){ errDS18B20Cnt = 0;}
                recordErrors(clientNo,channel,IDseries,temperature,ID,errDS18B20Cnt);
                temperature = QString::number(85,10,6);            // 异常值默认为85度
                if(clientNo == 1)
                {
                    DS18B20_ALL_Node[channel][IDseries].temperature = temperature;
                }
                else if(clientNo == 2)
                {
                    DS18B20_ADD_Node[channel][IDseries].temperature = temperature;
                }
            }
        }
    }
}

// 迫于大哥(@fjc)威严，被迫为每一个传感器建立一个文件夹
void DS18b20Sensor::recordSingleSensor(int clientNo, unsigned int chan, QString id, QString temper)
{
    QString fileName,content;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString currentDate = current_date_time.toString("yyyy-MM-dd-hh:mm:ss");
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
        fileName = dsNo2Dir+"/通道"+QString::number(chan,10);
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
void DS18b20Sensor::recordErrors(int client,unsigned int chan, unsigned int ind, QString temper, QString id, unsigned long count)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString currentTime =current_date_time.toString("yyyy-MM-dd-hh:mm:ss"); //当前时间
    QString errContent; //这一次的错误内容
    errContent = currentTime+",传感器"+QString::number(client)+"号板,"
            +QString::number(chan,10)+","+QString::number(ind,10)
            +","+id+","+temper+",";
    if(client == 1)
    {
        errContent = errContent+DS18B20_ALL_Node[chan][ind].temperature+","
                +QString::number(count,10)+",温度不在正常范围";
    }
    if(client == 2)
    {
        errContent = errContent+DS18B20_ADD_Node[chan][ind].temperature+","
                +QString::number(count,10)+",温度不在正常范围";
    }
    writeFile(ds18ErrPath,errContent);
}

// 释放TCP内存
void DS18b20Sensor::deleteTcpServer()
{
    ds18WorkingStatus = false;
    ds18No2WorkStatus = false;
    ds18Server->close();
    ds18Socket->close();
    ds18AddServer->close();
    ds18AddSocket->close();
    delete ds18Server;
    delete ds18AddServer;
    qDebug() << "DS18b20传感器一号板和二号板TCP server关闭";
}

// 创建新的一天的文件
void DS18b20Sensor::niceNewDay(QString path)
{
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    dailyDir = path+"/WiFi温度数据"+"("+currentDate+")";
    dsNo1Dir = dailyDir+"/WiFi温度数据一号板("+currentDate+")";
    dsNo2Dir = dailyDir+"/WiFi温度数据二号板("+currentDate+")";
    if(ds18Dir->exists(dailyDir)) qDebug()<<"最美的不是下雨天";
    else
    {
        if(ds18Dir->mkdir(dailyDir)) qDebug()<<"而是与你一起躲雨的屋檐";
    }
    ds18ErrPath = dailyDir +"/DS18b20错误记录"+currentDate+".csv";
    QString errHeader = "时间,设备号,通道号,传感器号,ID号,当前温度,上次温度,错误计数,错误原因";
    if(QFile::exists(ds18ErrPath)) qDebug()<<"文件已存在！";
    else
    {
        if(writeFile(ds18ErrPath,errHeader))
        qDebug()<<"DS18b20错误记录文件创建成功";
    }
    if(ds18Dir->exists(dsNo1Dir)) qDebug()<<"最美的不是下雨天";
    else
    {
        if(ds18Dir->mkdir(dsNo1Dir)) qDebug()<<"而是与你一起躲雨的屋檐";
    }
    if(ds18Dir->exists(dsNo2Dir)) qDebug()<<"最美的不是下雨天";
    else
    {
        if(ds18Dir->mkdir(dsNo2Dir)) qDebug()<<"而是与你一起躲雨的屋檐";
    }
}
