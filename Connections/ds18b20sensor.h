#ifndef DS18B20SENSOR_H
#define DS18B20SENSOR_H

#include "tools.h"

#define DS18B20_Channel_Max 8			// DS18B20最大容纳的通道数
#define DS18B20_Index_Max 8 			// DS18B20每通道最大容纳的节点数

// ds18b20存储结构
struct DS18B20_Node
{
    DS18B20_Node() {ID = ""; temperature= "";}
    DS18B20_Node(QString id, QString tp) { ID = id; temperature = tp; }
    QString ID;
    QString temperature;
};

extern DS18B20_Node DS18B20_ALL_Node[][DS18B20_Index_Max];
extern DS18B20_Node DS18B20_ADD_Node[][DS18B20_Index_Max];
extern bool ds18WorkingStatus;
extern bool ds18No2WorkStatus;

class DS18b20Sensor: public QObject
{
    Q_OBJECT

public:
    DS18b20Sensor();
    ~DS18b20Sensor();
    DS18b20Sensor(QString ds18path);

private:
    QString dailyDir;                                     // 当天数据文件存放路径
    unsigned long errDS18B20Cnt;                          // 错误计数
    QString dslinkport1;                                  // 监听端口1
    QString dslinkport2;                                  // 监听端口2
    QString dsHostIp;                                     // 本机IP地址
    QTcpServer *ds18Server;
    QTcpSocket *ds18Socket;
    QTcpServer *ds18AddServer;
    QTcpSocket *ds18AddSocket;
    QByteArray dataALL;
    QByteArray dataAddALL;
    bool newFullFragment;                                 // 是否完整一帧
    bool addNewFullFragment;
    QString dsNo1Dir,dsNo2Dir;
    QString ds18ErrPath;                                  // 错误记录
    QMutex *ds18Lock;
    QDir *ds18Dir;

public:
    bool listenDS18b20();                                 // 监听传感器一号板
    bool listenDS18Add();                                 // 监听传感器二号板
    int checkDchIDInList(QString IdIn, int channel, int clientNo); // 检查ID合法性
    void processData(QByteArray a, int clientNo);
    void recordSingleSensor(int clientNo, unsigned int chan, QString id, QString temper);
    void recordErrors(int client, unsigned int, unsigned int, QString, QString, unsigned long, unsigned int errType);

public slots:
    void newClientConnection();                           // 当传感器一号板连接到了补偿器
    void addNewClientConnection();                        // 当传感器二号板连接到了补偿器
    void readDS18Data();                                  // 读取传感器一号板数据
    void readDS18AddData();                               // 读取传感器二号板数据
    void socketDisconnected();                            // 传感器一号板socket连接断开
    void addSocketDisconnected();                         // 传感器二号板socket连接断开
    void deleteTcpServer();
    void niceNewDay(QString path);

signals:
    void sendMsg(QString msg, int status);
};

#endif // DS18B20SENSOR_H
