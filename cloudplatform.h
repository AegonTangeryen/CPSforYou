#ifndef CLOUDPLATFORM_H
#define CLOUDPLATFORM_H

#include "ds18b20sensor.h"
#include "fbgsensos.h"
#include "hnc848system.h"
#include "laserdisplacesensor.h"
#include "dataxml.h"
#include "envisensor.h"

class CloudPlatform: public QObject
{
    Q_OBJECT

public:
    CloudPlatform();
    ~CloudPlatform();
    void packageData();

    QString cloudServerIP;
    unsigned int cloudServerPort;
    QTcpSocket *cloudSocket;
    QTimer *cloudTimer;
    QString xmlInStr;                          // 接收的xml格式的数据包
    bool userOperation;
    unsigned int ticToc;
    void linkOnceAgain();

signals:
    void sendMsg(QString msg);                 // 发送到Ui界面的信息

public slots:
    void receiveFromCloud();
    void afterConnected();
    void afterDisconnected();
    void onTimeIsUp();
    void deleteTcpClient();
};

#endif // CLOUDPLATFORM_H
