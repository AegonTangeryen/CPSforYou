#ifndef FBGUDPTHREAD_H
#define FBGUDPTHREAD_H

#include "fbgsensos.h"

class FBGUdpThread: public QThread
{
    Q_OBJECT

public:
    FBGUdpThread();
    FBGUdpThread(QString path);
    ~FBGUdpThread();

public:
    void run();
    QString fbgPath;

signals:
    void passUdpInfo(int);
    void sendNewDay(QString);
    void destroyUdp();

public slots:
    void forceThread2Quit();
    void relayUdpInfo(int tywin);
    void newDayforYou(QString davos);
};

#endif // FBGUDPTHREAD_H
