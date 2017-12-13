#ifndef HNC848SYSTEM_H
#define HNC848SYSTEM_H

extern "C" { //华中数控api相关头文件
#include "hncnet.h"
#include "hncsys.h"
#include "hncaxis.h"
#include "hncchan.h"
#include "hncalarm.h"
#include "hncsys.h"
#include "hncreg.h"
}

#include <QString>
#include <QVector>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include <QMutexLocker>
#include <QTimer>
#include "tools.h"

enum HNC_AXIS_SELECT					// 机床数据轴选择
{
    HNC_AXIS_X=0,HNC_AXIS_Y=1,HNC_AXIS_Z=2,HNC_AXIS_Z1=3,HNC_AXIS_C=4,HNC_AXIS_MAIN=5
};

struct CNCAlarmReg				// 机床报警包
{
    CNCAlarmReg() { alarmNo = 0; errTxt = ""; } //构造函数
    CNCAlarmReg(long aNo,QString erT) { alarmNo = aNo; errTxt = erT; }
    long alarmNo;				// 报警号
    QString errTxt;				// 报警文本
};

struct CNCHisAlarmReg			// 机床历史报警包
{
    CNCHisAlarmReg() { alarmNo = 0; beginStr = ""; endStr = ""; errTxt = ""; }
    CNCHisAlarmReg(long aNo,QString bStr,QString eStr, QString erT)
    {
        alarmNo = aNo; beginStr = bStr; endStr = eStr; errTxt = erT;
    }
    long alarmNo;				// 报警号
    QString beginStr;			// 开始时间
    QString endStr;				// 结束时间
    QString errTxt;				// 报警文本
};

struct CNCInfoReg				// 机床信息集合
{
    CNCInfoReg() //构造函数
    {
        ch=0;moveunit=0;turnunit=0;
        AXIS_X_POS=-1234.4314;AXIS_Y_POS=0;AXIS_Z_POS=0;AXIS_MA_POS=0;
        AXIS_X_PWR=0;AXIS_Y_PWR=0;AXIS_Z_PWR=0;AXIS_MA_PWR=0;
        AXIS_X_RATED=0;AXIS_Y_RATED=0;AXIS_Z_RATED=0;AXIS_MA_RATED=0;
        AXIS_X_FUHE=0;AXIS_Y_FUHE=0;AXIS_Z_FUHE=0;AXIS_MA_FUHE=0;
        feedrate=0;speed=0;
        PauseStatus=QObject::tr("Paused");
    }
    long ch;					            // 通道号
    long moveunit;				            // 长度分辨率
    long turnunit;				            // 角度分辨率

    double AXIS_X_POS;			            // x坐标
    double AXIS_Y_POS;			            // y坐标
    double AXIS_Z_POS;			            // z坐标
    double AXIS_MA_POS;			            // 主轴坐标

    double AXIS_X_PWR;						// x轴负载电流（功率）
    double AXIS_Y_PWR;						// y轴负载电流（功率）
    double AXIS_Z_PWR;						// z轴负载电流（功率）
    double AXIS_MA_PWR;						// 主轴负载电流（功率）

    double AXIS_X_RATED;					// x轴额定电流
    double AXIS_Y_RATED;					// y轴额定电流
    double AXIS_Z_RATED;					// z轴额定电流
    double AXIS_MA_RATED;				    // 主轴额定电流

    double AXIS_X_FUHE;						// x轴负荷
    double AXIS_Y_FUHE;						// y轴负荷
    double AXIS_Z_FUHE;						// z轴负荷
    double AXIS_MA_FUHE;					// 主轴负荷

    double feedrate;						// 进给速度
    double speed;							// 主轴速度(测)

    QString PauseStatus;					// 暂停状态

    /*定义了一个CNCAlarmReg类型的名叫nowAlarmPack的qvector变量
     QVector类是一个提供动态数组的模板类，保存对象的向量容器*/
    QVector<CNCAlarmReg> nowAlarmPack;		// 当前报警信息
    QVector<CNCHisAlarmReg> hisAlarmPack;	    // 历史报警信息
};

extern CNCInfoReg CNCInfo;
extern bool cncWorkingStatus;
extern int statusFor1191;
extern unsigned int compValue[];
extern char time2WriteRegisters;

class Hnc848System: public QThread
{
    Q_OBJECT

public:
    Hnc848System();
    Hnc848System(QString cncpath);
    ~Hnc848System();

private:
    short clientNo;                                           // 机床通信的网络号
    long alarmHisRecCnt;
    QString cncFileDir;                                  // 机床数据csv文件存放路径
    QString cncAllPath;                                   // 总表
    QString cncAlarmPath;                              // 机床报警信息CSV文件存放路径
    QMutex *cncLock;                                   // 互斥锁
    QTimer *cncTimer;
    QDir *cncDir;
    bool time2ReadCNCData;
    bool quitThread;

public:
    bool connect2CNC();                                // 连接到机床
    bool getCNCData();                                 // 采集数控系统参数
    QString getAlarmTimetoStr(nctime_t t);             // 转换报警记录的时间为字符串
    void recordCNC(CNCInfoReg CNCInfo);                // 记录数据到csv文件
    short setHncReg(unsigned short reg, Bit8 value, short client_num);    // 将数值写入寄存器中
    Bit8 readHncReg(unsigned short reg, short client_num);                // 读取指定的寄存器
    void run();                                        //子线程

public slots:
    void timeIsup();
    void niceNewDay(QString panda);
    void forceThreadtoQuit();

signals:
    // 显示提示消息
    void sendMsg(QString msg, bool result);
    // 返回信息，依次是通道号，X坐标，Y坐标，Z坐标，主轴转速，X功率，Y功率，Z功率，工作状态
    void sendInfo(long,double,double,double,double,double,double,double,double,QString);
    void sendPara(short,short,short,unsigned int,unsigned int,unsigned int);
};

#endif // HNC848SYSTEM_H
