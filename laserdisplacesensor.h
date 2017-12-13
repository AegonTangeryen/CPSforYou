#ifndef LASERDISPLACESENSOR_H
#define LASERDISPLACESENSOR_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QMutexLocker>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "LKIF2.h"
#include "tools.h"

extern bool time2ClearDispalcement;
extern bool laserWorkingStatus;
extern QString ccdInfo[];

class LaserDisplaceSensor: public QThread
{
    Q_OBJECT

public:
    LaserDisplaceSensor();
    LaserDisplaceSensor(QString path);
    ~LaserDisplaceSensor();

public:
    QString displacementPath;
    QString displacementDir;
    QMutex *ccdLock;
    QTimer *ccdTimer;
    QDir *ccdDir;
    bool time2ReadDispalcement;
    bool time2CloseDispalcement;
    QSerialPort serial;
    bool openSerial;

    void initSeialPort();                            // 初始化串口
    bool serialPortLink();
    bool link2Displacement();
    void getDisplaceData();
    void recordDisplacements(QString *wyl);
    void clearDisplays();
    void closeDisplacementSensor();
    QString getStringFromFloatValue(LKIF_FLOATVALUE_OUT value);
    void run();

public slots:
    void timeIsUp();
    void niceNewDay(QString pandahi);
    void forceThread2Quit();
    void sendOrder2Sensor();                        // 发送数据到串口
    void serialRead();                              // 串口收到数据

signals:
    void sendMsg(QString);
    void sendPara(QString*);                        //返回三轴示数
};

#endif // LASERDISPLACESENSOR_H
