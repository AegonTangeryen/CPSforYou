#ifndef FBGSENSOS_H
#define FBGSENSOS_H

#include "tools.h"

#define FBG_Channel_Max 32 				// FBG最大容纳的通道数
#define FBG_Index_Max 20 				// FBG每通道最大容纳的节点数

extern QString FBG_ALL[][FBG_Index_Max];
extern bool fbgWorkingStatus;

class FBGSensos: public QObject
{
    Q_OBJECT

public:
    FBGSensos();
    FBGSensos(QString path);

public:
    QString fbgIp;			                           // FBG解调仪地址
    unsigned int fbgPort;				               // FBG解调仪端口
    QMutex *fbgLock;
    int channelSignal;                                 // 通道标志
    QString fbgPath;
    QString fbgfileDir;
    short int FragmentCnt;
    QUdpSocket *fbgSocket;
    unsigned long errFBGCnt;
    QDir *fbgDir;

    void linkFbg();
    void recordSingleSensor(unsigned int channel, unsigned int index, QString FBGwave);

public slots:
    void readFbgData();
    void deleteUdpSocket();
    void niceNewDay(QString path);

signals:
    void sendPara2Ui(int);
};

#endif // FBGSENSOS_H
