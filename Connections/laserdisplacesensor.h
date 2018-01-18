#ifndef LASERDISPLACESENSOR_H
#define LASERDISPLACESENSOR_H

#include "LKIF2.h"
#include "tools.h"

extern bool time2ClearDispalcement;
extern bool laserWorkingStatus;
extern QStringList ccdInfo;

class LaserDisplaceSensor: public QThread
{
    Q_OBJECT

public:
    LaserDisplaceSensor();
    LaserDisplaceSensor(QString path,QString liverpoolIp);
    ~LaserDisplaceSensor();

public:
    QString displacementPath;
    QString displacementDir;
    QString laserDisplaceIP;
    QMutex *ccdLock;
    QTimer *ccdTimer;
    MMTimer *MultiMediaTimer;
    QDir *ccdDir;
    bool time2ReadDispalcement;
    bool time2CloseDispalcement;

    bool link2Displacement();
    void getDisplaceData();
    void recordDisplacements(QStringList wyl);
    void clearDisplays();
    void closeDisplacementSensor();
    QString getStringFromFloatValue(LKIF_FLOATVALUE_OUT value);
    void run();

public slots:
    void timeIsUp();
    void mmTimeIsUp();
    void niceNewDay(QString pandahi);
    void forceThread2Quit();

signals:
    void sendMsg(QString,int);
};

#endif // LASERDISPLACESENSOR_H
