#include "laserdisplacesensor.h"

bool time2ClearDispalcement = false; //是时候清零一波位移传感器了
bool laserWorkingStatus = false;
QString ccdInfo[3];

LaserDisplaceSensor::LaserDisplaceSensor() {}

LaserDisplaceSensor::LaserDisplaceSensor(QString path)
{
    displacementDir = path;                                     //  激光位移传感器专属文件夹
    time2ReadDispalcement  = false;
    time2CloseDispalcement = false;
    ccdLock = new QMutex();
    ccdTimer = new QTimer(this);
    ccdDir = new QDir();
    initSeialPort();
    openSerial = false;
    connect(ccdTimer,&QTimer::timeout, this,&LaserDisplaceSensor::timeIsUp);
    ccdTimer->setInterval(100); // 高速采集，100ms一次
    ccdTimer->start();
}

LaserDisplaceSensor::~LaserDisplaceSensor()
{
    delete ccdLock;
    delete ccdTimer;
    delete ccdDir;
    qDebug()<<"退出ccd线程,完成位移传感器析构函数";
}

// 连接传感器
bool LaserDisplaceSensor::link2Displacement()
{
    char ccdIp[20] = "192.168.0.53";
    LKIF_OPENPARAM_ETHERNET paramEther;
    paramEther.IPAddress.S_un.S_addr = inet_addr(ccdIp);
    if (paramEther.IPAddress.S_un.S_addr == INADDR_NONE)
    {
        qDebug()<<endl<<"Ethernet port open failed!";
        return false;
    }
    //RC rc = LKIF2_OpenDeviceETHER(&paramEther);   // 打开网口
    RC rc = LKIF2_OpenDeviceUsb();              // 打开USB口
    rc = LKIF2_StartMeasure();                                        // 开始测量
    if(rc==RC_NAK_INVALID_STATE || rc==RC_OK)
    {
        qDebug()<<"连接成功";
    }
    else
    {
        qDebug("位移传感器连接错误！错误号：%X",rc);
        emit sendMsg("连接失败");
        return false;
    }

    QDateTime current_date_time = QDateTime::currentDateTime();
    QString currentDate = current_date_time.toString("yyyy-MM-dd hh：mm：ss");
    displacementDir = displacementDir+ "/CCD位移数据"+"("+currentDate+")";
    if(ccdDir->exists(displacementDir)) qDebug()<<"根目录已存在!";
    else
    {
        if(ccdDir->mkdir(displacementDir)) qDebug()<<"根目录创建成功！";
    }

    laserWorkingStatus = true;
    emit sendMsg("连接成功");

    return true;
}

// 读取示数
void LaserDisplaceSensor::getDisplaceData()
{
    time2ReadDispalcement = false;
    int outNo = 0;      //轴号
    for(int i=0;i<3;i++)
    {
        outNo = i;
        LKIF_FLOATVALUE_OUT value;
        RC rc = LKIF2_GetCalcDataSingle((outNo),&value);
        if((outNo)!=value.OutNo) qDebug()<<endl<<"位移传感器读取错误！轴号对不上啊大兄弟！";
        if(rc == RC_OK)
        {
            ccdInfo[i] = getStringFromFloatValue(value);
        }
    }
}

// 记录示数
void LaserDisplaceSensor::recordDisplacements(QString *wyl)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString currentTime =current_date_time.toString("yyyy-MM-dd-hh:mm:ss");
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
    int outNo = 0;
    for(int i=0;i<3;i++)
    {
        outNo = i;
        RC rc = LKIF2_SetZeroSingle(outNo,TRUE);
    }
}

void LaserDisplaceSensor::closeDisplacementSensor()
{
    RC rc = LKIF2_CloseDevice();	// 定义返回代码清单，并且关闭USB设备
    if(rc == RC_OK)			        // 测试关闭是否成功
    {
        qDebug("位移传感器关闭成功!成功代码是：0x%X",rc);
    }
    else
    {
        qDebug("位移传感器关闭成功!成功代码是：0x%X",rc);
    }
}

// 定时器中断处理函数
void LaserDisplaceSensor::timeIsUp()
{
    time2ReadDispalcement = true;
}

// 强制退出线程
void LaserDisplaceSensor::forceThread2Quit()
{
    time2CloseDispalcement = true;
}

// 创建新的一天的文件
void LaserDisplaceSensor::niceNewDay(QString pandahi)
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString currentDate = current_date_time.toString("yyyy-MM-dd hh：mm：ss");
    displacementDir = pandahi+ "/CCD位移数据"+"("+currentDate+")";
    if(ccdDir->exists(displacementDir)) qDebug()<<"根目录已存在!";
    else
    {
        if(ccdDir->mkdir(displacementDir)) qDebug()<<"根目录创建成功！";
    }
}

// 根据读取情况确定返回值
QString LaserDisplaceSensor::getStringFromFloatValue(LKIF_FLOATVALUE_OUT value)
{
    QString result;
    switch(value.FloatResult)
    {
        case LKIF_FLOATRESULT_VALID:
                result = QString::number(value.Value,10,6);
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

// 初始化串口
void LaserDisplaceSensor::initSeialPort()
{
    connect(&serial,SIGNAL(readyRead()),this,&LaserDisplaceSensor::serialRead);   //连接槽
    QList<QSerialPortInfo>  infos = QSerialPortInfo::availablePorts();
    if(infos.isEmpty())
    {
        return;
    }
}

bool LaserDisplaceSensor::serialPortLink()
{
    if(openSerial)
    {
        return true;
    }
    else
    {
        QString selectSerialName = ui->comboBox->currentText();
        QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
        QSerialPortInfo info;
        int i = 0;
        foreach(info, infos)
        {
            if(info.portName() == selectSerialName)
            {
                break;
            }
            i++;
        }
        serial.setPort(info);
        serial.open(QIODevice::ReadWrite);         //读写打开
        openSerial = true;
    }
}

//子线程
void LaserDisplaceSensor::run()
{
    //if(!link2Displacement()) return; //连接失败，退出线程
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
            return;
        }
    }
}
