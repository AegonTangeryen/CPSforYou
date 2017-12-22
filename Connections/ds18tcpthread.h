#ifndef DS18TCPTHREAD_H
#define DS18TCPTHREAD_H

#include "ds18b20sensor.h"

class Ds18TcpThread: public QThread
{
    Q_OBJECT

public:
    Ds18TcpThread();
    ~Ds18TcpThread();
    Ds18TcpThread(QString dspath);

public:
    void run();                                              // 专属于DS18b20的tcp socket子线程
    QString path;                                            // 文件存放路径

public slots:
     void passDS18Msg2Ui(QString para, int starkstatus);    // 从子线程发送消息到主界面
     void forceThread2Quit();
     void newDayforYou(QString seaworth);

signals:
     void relayMsg2DS18(QString msg);
     void relayMsg2Ui(QString msg, int starkstatus);
     void destroyTcp();
     void sendNewDay(QString);
};

#endif // DS18TCPTHREAD_H
