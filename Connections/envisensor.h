#ifndef ENVISENSOR_H
#define ENVISENSOR_H

#include "tools.h"

#define Env_Number_Max 4

struct Env_Node
{
    Env_Node() {ID = ""; temperature= "";}
    Env_Node(QString id, QString tp) { ID = id; temperature = tp; }
    QString ID;
    QString temperature;
};

extern Env_Node ENV_ALL_Node[];
extern bool envWorkingStatus;

class EnviSensor: public QObject
{
        Q_OBJECT

public:
    EnviSensor();
    EnviSensor(QString path,QString globalPort);

    QString environmentPath;
    QString envHostIp;
    unsigned int envPort;
    unsigned long errCnt;
    QTcpServer  *envServer;
    QTcpSocket *envSocket;
    QByteArray EnvDataALL;
    bool envNewFullFragment;                             // 是否完整一帧
    QString envErrPath;                                  // 错误记录
    QMutex *envLock;
    QDir *envDir;

    bool listenEnvironment();                            // 监听环境温度传感器
    int checkDchIDInList(QString IdIn);                  // 检查ID合法性
    void processData(QByteArray a);
    void recordSingleSensor(QString id, QString temper);

public slots:
    void newClientConnection();                          // 当传感器连接到了补偿器
    void readEnvData();                                  // 读取传感器数据
    void socketDisconnected();                           // 传感器连接断开
    void deleteEnvServer();
    void niceNewDay(QString path);

signals:
    void sendMsg(QString msg, int status);
};

#endif // ENVISENSOR_H
