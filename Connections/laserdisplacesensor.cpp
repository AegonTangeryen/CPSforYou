#include "laserdisplacesensor.h"

bool time2ClearDispalcement = false;            // 是时候清零一波位移传感器了
bool laserWorkingStatus = false;
QStringList ccdInfo;

LaserDisplaceSensor::LaserDisplaceSensor() {}

LaserDisplaceSensor::LaserDisplaceSensor(QString path, QString liverpoolIp)
{
    displacementDir = path;                     //  激光位移传感器专属文件夹
    laserDisplaceIP = liverpoolIp;
    time2ReadDispalcement  = false;
    time2CloseDispalcement = false;
    ccdLock = new QMutex();
    ccdTimer = new QTimer(this);
    ccdDir = new QDir();

    ccdTimer->setInterval(100);                 // 高速采集，100ms一次
    ccdTimer->setTimerType(Qt::PreciseTimer);   // 精确的定时器，尽量保持毫秒精度
    connect(ccdTimer,&QTimer::timeout, this,&LaserDisplaceSensor::timeIsUp);
    ccdTimer->start();

    //MultiMediaTimer = new MMTimer(100,this);
    //connect(MultiMediaTimer,&MMTimer::timeout,this,&LaserDisplaceSensor::mmTimeIsUp);
    //MultiMediaTimer->start();
}

LaserDisplaceSensor::~LaserDisplaceSensor()
{
    delete ccdLock;
    delete ccdTimer;
    delete ccdDir;
    //delete MultiMediaTimer;
}

// 连接传感器
bool LaserDisplaceSensor::link2Displacement()
{
    qDebug()<<"5.2";
//    char *ccdIp = laserDisplaceIP.toLocal8Bit().data();
//    LKIF_OPENPARAM_ETHERNET paramEther;
//    paramEther.IPAddress.S_un.S_addr = inet_addr(ccdIp);
//    if (paramEther.IPAddress.S_un.S_addr == INADDR_NONE)
//    {
//        emit sendMsg("Ethernet port open failed!");
//        return false;
//    }
//    RC rc = LKIF2_OpenDeviceETHER(&paramEther);   // 打开网口
    RC rc = LKIF2_OpenDeviceUsb();              // 打开USB口
    rc = LKIF2_StartMeasure();                                        // 开始测量
    if(rc==RC_NAK_INVALID_STATE || rc==RC_OK)
    {
        emit sendMsg("ok",1);
    }
    else
    {
        emit sendMsg("failed",-1);
        return false;
    }

    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    displacementDir = displacementDir+ "/CCD位移数据"+"("+currentDate+")";
    if(!ccdDir->exists(displacementDir))
    {
        ccdDir->mkdir(displacementDir);
    }
    laserWorkingStatus = true;

    return true;
}

// 读取示数
void LaserDisplaceSensor::getDisplaceData()
{
    qDebug()<<"5.1";
    time2ReadDispalcement = false;
    int outNo = 0;      // 轴号
    for(int i=0;i<3;i++)
    {
        outNo = i;
        LKIF_FLOATVALUE_OUT value;
        RC rc = LKIF2_GetCalcDataSingle((outNo),&value);
        if(rc == RC_OK)
        {
            ccdInfo[i] = getStringFromFloatValue(value);
        }
    }
}

// 记录示数
void LaserDisplaceSensor::recordDisplacements(QStringList wyl)
{
    QString currentTime =QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString ccdContent, ccdfilename;
    ccdfilename = displacementDir+"/ccdx.csv";
    ccdContent = currentTime+","+wyl[0];
    writeFile(ccdfilename,ccdContent);

    ccdfilename = displacementDir+"/ccdy.csv";
    ccdContent = currentTime+","+wyl[1];
    writeFile(ccdfilename,ccdContent);

    ccdfilename = displacementDir+"/ccdz.csv";
    ccdContent = currentTime+","+wyl[2];
    writeFile(ccdfilename,ccdContent);
}

// 示数清零
void LaserDisplaceSensor::clearDisplays()
{
    qDebug()<<"5.3";
    int outNo = 0;
    for(int i=0;i<3;i++)
    {
        outNo = i;
        RC rc = LKIF2_SetZeroSingle(outNo,TRUE);
    }
}

// 断开连接
void LaserDisplaceSensor::closeDisplacementSensor()
{
    RC rc = LKIF2_CloseDevice();	// 定义返回代码清单，并且关闭USB设备
    if(rc != RC_OK)			        // 未能成功关闭
    sendMsg("关闭失败!失败代号是:0x"+QString::number(rc,16),2);
}

// 根据读取情况确定返回值
QString LaserDisplaceSensor::getStringFromFloatValue(LKIF_FLOATVALUE_OUT value)
{
    QString result;
    switch(value.FloatResult)
    {
        case LKIF_FLOATRESULT_VALID:
                result = QString::number(value.Value,10,4); // 保留四位小数
            break;
        case LKIF_FLOATRESULT_RANGEOVER_P:
            result = "+FFFFFFF";
            break;
        case LKIF_FLOATRESULT_RANGEOVER_N:
            result = "-FFFFFFF";
            break;
        case LKIF_FLOATRESULT_WAITING:
            result = "--------";
            break;
        case LKIF_FLOATRESULT_ALARM:
            result = "alarm";
            break;
        default:
            result = "Invalid";
    }

    return result;
}

// 定时器中断处理函数
void LaserDisplaceSensor::timeIsUp()
{
    time2ReadDispalcement = true;
}

// 多媒体定时器中断处理函数
void LaserDisplaceSensor::mmTimeIsUp()
{
    //time2ReadDispalcement = true;
}

// 强制退出线程
void LaserDisplaceSensor::forceThread2Quit()
{
    time2CloseDispalcement = true;
}

// 创建新的一天的文件
void LaserDisplaceSensor::niceNewDay(QString pandahi)
{
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    displacementDir = pandahi+ "/CCD位移数据"+"("+currentDate+")";
    if(!ccdDir->exists(displacementDir))
    {
        ccdDir->mkdir(displacementDir);
    }
}

//子线程
void LaserDisplaceSensor::run()
{
    if(!link2Displacement()) return; //连接失败，退出线程
    while(1)
    {
        if(time2ReadDispalcement)
        {
            time2ReadDispalcement =false;
            getDisplaceData();
            recordDisplacements(ccdInfo);
        }
        if(time2ClearDispalcement)
        {
            ccdLock->lock();
            time2ClearDispalcement = false;
            ccdLock->unlock();
            clearDisplays();
        }
        if(time2CloseDispalcement)
        {
            laserWorkingStatus = false;
            emit sendMsg("deleted",0);
            qDebug()<<"laserQuit";
            return;
        }
    }
}
