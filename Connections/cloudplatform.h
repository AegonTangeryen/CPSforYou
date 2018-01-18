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
    CloudPlatform(QString skyIP,QString sunPort);
    ~CloudPlatform();

public:
    void linkOnceAgain();      // 断线重连
    void packageHncData();     // 单独打包数控系统信息，提供给虚拟机床
    void packageSensorsData(); // 打包所有传感器信息

private:
    QString cloudServerIP;
    unsigned int cloudServerPort;
    QTcpSocket *cloudSocket;
    QTimer *cloudTimer;
    QTimer *hncPrivateTimer;
    QSettings *updateIni;
    QString xmlInStr;
    bool userOperation;
    quint16 ticToc;

signals:
    void sendMsg(QString msg,int rosemary);

public slots:
    void onTimeIsUp();
    void onPrivateTimeUp();
    void afterConnected();
    void receiveFromCloud();
    void afterDisconnected();
    void deleteTcpClient();
};

#endif // CLOUDPLATFORM_H
