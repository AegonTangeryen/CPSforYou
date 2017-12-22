#ifndef ENVITHREAD_H
#define ENVITHREAD_H

#include "envisensor.h"

class EnviThread: public QThread
{
    Q_OBJECT

public:
    EnviThread();
    ~EnviThread();
    EnviThread(QString filePath);

public:
    void run();
    QString path;

public slots:
     void passEnvMsg2Ui(QString para, int starkstatus);
     void forceThread2Quit();
     void newDayforYou(QString branden);

signals:
     void relayMsg2Ui(QString msg, int starkstatus);
     void destroyTcp();
     void sendNewDay(QString);
};

#endif // ENVITHREAD_H
