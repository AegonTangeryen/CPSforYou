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
    void packageData();
    void linkOnceAgain();

private:
    QString cloudServerIP;
    unsigned int cloudServerPort;
    QTcpSocket *cloudSocket;
    QTimer *cloudTimer;
    QString xmlInStr;
    bool userOperation;
    unsigned int ticToc;

signals:
    void sendMsg(QString msg,int rosemary);

public slots:
    void receiveFromCloud();
    void afterConnected();
    void afterDisconnected();
    void onTimeIsUp();
    void deleteTcpClient();
};

#endif // CLOUDPLATFORM_H
