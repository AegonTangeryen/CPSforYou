#ifndef CLOUDTCPTHREAD_H
#define CLOUDTCPTHREAD_H

#include <QThread>
#include "cloudplatform.h"

extern bool cloudLinkStatus;

class CloudTcpThread: public QThread
{
    Q_OBJECT

public:
    CloudTcpThread();
    ~CloudTcpThread();

public:
    QString path;
    CloudPlatform *cloudForU;
    void run();

signals:
    void passCloudInfo(QString,int);
    void destroyTcpClient();

public slots:
    void relayCloudInfo(QString jamie, int jack);
    void closeThread();
};

#endif // CLOUDTCPTHREAD_H
