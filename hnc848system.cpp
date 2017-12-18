#include "hnc848system.h"

bool cncWorkingStatus = false;          // 机床工作状态
char time2WriteRegisters = 0;
int statusFor1191 = 0;                  // #1191的数值
CNCInfoReg CNCInfo;                     // 机床信息集合变量
unsigned int compValue[3]={0,0,0};      // 补偿值

Hnc848System::Hnc848System() {}

Hnc848System::~Hnc848System()
{
    HNC_NetExit();
    delete cncLock;
    delete cncTimer;
    delete cncDir;
}

Hnc848System::Hnc848System(QString cncpath)
{
   cncFileDir = cncpath;
   clientNo = 256;
   CNCPORT_Init = 5555;
   hncIp = "192.168.0.113";
   alarmHisRecCnt = 0;
   time2ReadCNCData = false;
   quitThread = false;
   cncLock = new QMutex();
   cncTimer = new QTimer(this);
   cncDir = new QDir();

   connect(cncTimer,&QTimer::timeout, this,&Hnc848System::timeIsup);
   cncTimer->setInterval(1000);  // 每1s中断一次
   cncTimer->start();
}

// 调整报警时间的格式
QString Hnc848System::getAlarmTimetoStr(nctime_t t)
{
    QString text;
    if (t.year > 0)
    {
        text= QString::number(t.year,10)+"-"+QString::number(t.month,10)+"-"+QString::number(t.day,10)+
                "-"+QString::number(t.hour,10)+":"+QString::number(t.minute)+":"+QString::number(t.second);
    }
    return text;
}

// 写寄存器：可选X105，X106，X107，X108。reg:寄存器号 client_num：设备连接号
// 返回0：写入成功；返回其他：失败
short Hnc848System::setHncReg(unsigned short reg, Bit8 value, short client_num)
{

    short ret = HNC_RegSetValue(REG_TYPE_X, reg, &value, client_num);
    return ret;
}

// 读取寄存器：可选Y100。reg:寄存器号 client_num：设备连接号
// 成功返回读取的内容；失败返回-1
Bit8 Hnc848System::readHncReg(unsigned short reg, short client_num)
{
    Bit8 temp = 0;
    Bit32 ret = HNC_RegGetValue(REG_TYPE_Y, reg, &temp, client_num);
    if(ret == 0)  return temp; // 读取成功
    else return -1;
}


// 连接机床：成功返回true，失败返回false
bool Hnc848System::connect2CNC()
{
    short ret = 0;
    QString hostIp = getHostIpAddress();
    ret = HNC_NetInit(hostIp.toLocal8Bit().data(), CNCPORT_Init);
    if (ret != 0) // 重新初始化
    {
        ret = HNC_NetInit(hostIp.toLocal8Bit().data(), CNCPORT_Init);
    }
    if (ret != 0)
    {
        emit sendMsg("数控系统网络初始化失败",false);
        return false;
    }

    char connect_ip[20] = "192.168.0.113";       //获得输入的连接IP地址
    clientNo = HNC_NetConnect(connect_ip, CNCPORT_Init);
    if (clientNo >= 0 && clientNo < 256)   // 连接成功
    {
        emit sendMsg("数控系统连接成功", true);
    }
    else
    {
        HNC_NetExit();
        emit sendMsg("数控系统连接失败",false);
        return false;
    }

    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    cncFileDir = cncFileDir+"/CNC机床数据"+"("+currentDate+")";    // cnc专属文件夹
    cncAlarmPath = cncFileDir+"/报警历史"+".csv";
    QString alarmHeader = "出现时间,报警号,报警文本内容";

    if(!cncDir->exists(cncFileDir))
    {
        cncDir->mkdir(cncFileDir);
    }
    if(!QFile::exists(cncAlarmPath))
    {
        writeFile(cncAlarmPath,alarmHeader);
    }

    return true;
}

// 从数控系统中获取数据：成功返回1，失败返回0
bool Hnc848System::getCNCData()
{
    int ret = 0;
    ret = HNC_NetIsConnect(clientNo);   //是否保持连接
    if(ret != 0)                        // 非正常状态下连接中断,重连
    {
        clientNo = HNC_NetConnect(hncIp.toLocal8Bit().data(), CNCPORT_Init);
        if (clientNo < 0)       // 连接失败
        {
            HNC_NetExit();
            emit sendMsg("数控系统连接中断，读取数据失败",false);
            return false;
        }
    }

    ret = HNC_SystemGetValue(HNC_SYS_ACTIVE_CHAN, &CNCInfo.ch, clientNo);							// 获取通道号
    ret = HNC_SystemGetValue(HNC_SYS_MOVE_UNIT, &CNCInfo.moveunit, clientNo);						// 长度分辨率
    ret = HNC_SystemGetValue(HNC_SYS_TURN_UNIT, &CNCInfo.turnunit, clientNo);						// 角度分辨率
    ret = HNC_ChannelGetValue(HNC_CHAN_ACT_FEEDRATE, CNCInfo.ch, 0, &CNCInfo.feedrate, clientNo);	// 获取进给速度
    ret = HNC_ChannelGetValue(HNC_CHAN_CMD_SPDL_SPEED, CNCInfo.ch, 0, &CNCInfo.speed, clientNo);	// 主轴速度
    CNCInfo.speed = CNCInfo.speed * (-1.0); //根据实际调整转速方向
    long xVal = 0;
    long yVal = 0;
    long zVal = 0;
    long maVal = 0;

    ret = HNC_AxisGetValue(HNC_AXIS_ACT_POS, HNC_AXIS_X, &xVal, clientNo);			// 获取轴x脉冲
    ret = HNC_AxisGetValue(HNC_AXIS_ACT_POS, HNC_AXIS_Y, &yVal, clientNo);			// 获取轴y脉冲
    ret = HNC_AxisGetValue(HNC_AXIS_ACT_POS, HNC_AXIS_Z, &zVal, clientNo);			// 获取轴z脉冲
    ret = HNC_AxisGetValue(HNC_AXIS_ACT_POS, HNC_AXIS_MAIN, &maVal, clientNo);		// 获取轴主轴脉冲

    CNCInfo.AXIS_X_POS=(double)xVal / CNCInfo.moveunit;								// 记录X轴的坐标值
    CNCInfo.AXIS_Y_POS=(double)yVal / CNCInfo.moveunit;								// 记录Y轴的坐标值
    CNCInfo.AXIS_Z_POS=(double)zVal / CNCInfo.moveunit;								// 记录Z轴的坐标值
    CNCInfo.AXIS_MA_POS=(double)maVal / CNCInfo.turnunit;							// 记录主轴的坐标值

    #define EPSILON 0.0001
    long status = 0;
    long cycle = 0;
    double value_load = 0;
    double value_rated = 0;

    HNC_AxisGetValue(HNC_AXIS_LOAD_CUR, HNC_AXIS_X, &value_load, clientNo);		// 获取X轴负载电流
    HNC_AxisGetValue(HNC_AXIS_RATED_CUR, HNC_AXIS_X, &value_rated, clientNo);	// 获取X轴额定电流
    CNCInfo.AXIS_X_PWR = value_load;											// 记录X轴负载电流
    CNCInfo.AXIS_X_RATED = value_rated;											// 记录X轴额定电流
    if ((value_rated <= -EPSILON) || (value_rated >= EPSILON))
        CNCInfo.AXIS_X_FUHE = value_load / value_rated * 100;					// 记录X轴百分比负荷
    else
        CNCInfo.AXIS_X_FUHE=0.0;

    HNC_AxisGetValue(HNC_AXIS_LOAD_CUR, HNC_AXIS_Y, &value_load, clientNo);		// 获取Y轴负载电流
    HNC_AxisGetValue(HNC_AXIS_RATED_CUR, HNC_AXIS_Y, &value_rated, clientNo);	// 获取Y轴额定电流
    CNCInfo.AXIS_Y_PWR = value_load;											// 记录Y轴负载电流
    CNCInfo.AXIS_Y_RATED = value_rated;											// 记录Y轴额定电流
    if ((value_rated <= -EPSILON) || (value_rated >= EPSILON))
        CNCInfo.AXIS_Y_FUHE = value_load / value_rated * 100;					// 记录Y轴百分比负荷
    else
        CNCInfo.AXIS_Y_FUHE=0.0;

    HNC_AxisGetValue(HNC_AXIS_LOAD_CUR, HNC_AXIS_Z, &value_load, clientNo);		// 获取Z轴负载电流
    HNC_AxisGetValue(HNC_AXIS_RATED_CUR, HNC_AXIS_Z, &value_rated, clientNo);	// 获取Z轴额定电流
    CNCInfo.AXIS_Z_PWR = value_load;											// 记录Z轴负载电流
    CNCInfo.AXIS_Z_RATED = value_rated;											// 记录Z轴额定电流
    if ((value_rated <= -EPSILON) || (value_rated >= EPSILON))
        CNCInfo.AXIS_Z_FUHE = value_load / value_rated * 100;					// 记录Z轴百分比负荷
    else
        CNCInfo.AXIS_Z_FUHE=0.0;

    HNC_AxisGetValue(HNC_AXIS_LOAD_CUR, HNC_AXIS_MAIN, &value_load, clientNo);	// 获取主轴负载电流
    HNC_AxisGetValue(HNC_AXIS_RATED_CUR, HNC_AXIS_MAIN, &value_rated, clientNo);// 获取主轴额定电流
    CNCInfo.AXIS_MA_PWR = value_load;											// 记录主轴负载电流
    CNCInfo.AXIS_MA_RATED = value_rated;										// 记录主轴额定电流
    if ((value_rated <= -EPSILON) || (value_rated >= EPSILON))
        CNCInfo.AXIS_MA_FUHE = value_load / value_rated * 100;					// 记录主轴百分比负荷
    else
        CNCInfo.AXIS_MA_FUHE=0.0;

    HNC_ChannelGetValue(HNC_CHAN_HOLD, CNCInfo.ch, HNC_AXIS_MAIN, &status, 0);
    if (status == 1)
    {
        CNCInfo.PauseStatus = "Pause";
    }
    else if (status == 0)
    {
        CNCInfo.PauseStatus = "Working";
    }

    long alarmNum = 0;													// 当前报警数目
    long alarmNo = 0;													// 当前报警号
    HNC_AlarmGetNum(ALARM_TYPE_ALL, ALARM_ERR, &alarmNum, clientNo);	// 获得所有报警类型
    Bit8 errTxt[128] = "\0";											// 报警文本
    CNCInfo.nowAlarmPack.clear();						// 清除上次的报警信息

    for (int i = 0; i < alarmNum; i++)
    {
        ret = HNC_AlarmGetData(ALARM_TYPE_ALL, ALARM_ERR, i, &alarmNo, errTxt, clientNo);
        CNCInfo.nowAlarmPack.push_back(CNCAlarmReg(alarmNo, QString::fromLocal8Bit(errTxt,128)));
    }

    long hisNum = 0;													// 历史报警数目
    AlarmHisData alrmHis[ALARM_HISTORY_MAX_NUM];						// 历史报警信息集
    HNC_AlarmGetHistoryNum(&hisNum, clientNo);
    memset(alrmHis, 0, sizeof(alrmHis));
    CNCInfo.hisAlarmPack = QVector<CNCHisAlarmReg>();
    HNC_AlarmGetHistoryData(0, &hisNum, alrmHis, clientNo);				// 查询索引从0开始的几个历史告警
    for (int i = hisNum - 1; i >= 0; i--)
    {
        if (alrmHis[i].alarmNo == 0) {continue;}

        long hisalarmNo = alrmHis[i].alarmNo;
        QString beginStr = getAlarmTimetoStr(alrmHis[i].timeBegin);
        QString endStr = getAlarmTimetoStr(alrmHis[i].timeEnd);
        QString errHisTxt = QString::fromLocal8Bit(alrmHis[i].text);
        CNCInfo.hisAlarmPack.push_back(CNCHisAlarmReg(hisalarmNo,beginStr,endStr,errHisTxt));
    }

    return true;
}

//记录数据到CSV文件
void Hnc848System::recordCNC(CNCInfoReg CNCInfo)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    // 把各个参数分别写入对应的文件
    QString paraFileName, paraContent;
    paraFileName = cncFileDir+"/通道.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.ch, 10, 6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/X轴坐标.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_X_POS,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/Y轴坐标.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_Y_POS,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/Z轴坐标.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_Z_POS,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/主轴坐标.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_MA_POS,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/进给速度.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.feedrate, 10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/主轴速度.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.speed,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/X轴功率.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_X_PWR,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/Y轴功率.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_Y_PWR,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/Z轴功率.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_Z_PWR,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/主轴功率.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_MA_PWR,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/X轴负荷.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_X_FUHE,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/Y轴负荷.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_Y_FUHE,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/Z轴负荷.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_Z_FUHE,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/主轴负荷.csv";
    paraContent = currentTime+","+QString::number(CNCInfo.AXIS_MA_FUHE,10,6);
    writeFile(paraFileName,paraContent);

    paraFileName = cncFileDir+"/暂停状态.csv";
    paraContent = currentTime+","+CNCInfo.PauseStatus;
    writeFile(paraFileName,paraContent);

    if (alarmHisRecCnt == 0)
    {
        for (unsigned int i = 0; i < CNCInfo.hisAlarmPack.size(); i++)
        {
            long hisalarmNo = CNCInfo.hisAlarmPack[i].alarmNo;
            QString beginStr(CNCInfo.hisAlarmPack[i].beginStr);
            QString endStr(CNCInfo.hisAlarmPack[i].endStr);
            QString errHisTxt(CNCInfo.hisAlarmPack[i].errTxt);
            QString alarmstr = beginStr+"至"+endStr+"出现："+","+QString::number(hisalarmNo,10, 6)+","+errHisTxt;
            writeFile(cncAlarmPath,alarmstr); //写入CSV文件
        }
        alarmHisRecCnt++;
    }
    else if (alarmHisRecCnt == 7200) 	alarmHisRecCnt = 0; // 每两个小时记录一次
    else alarmHisRecCnt++;
}

// 定时器中断处理函数
void Hnc848System::timeIsup()
{
    time2ReadCNCData = true;
}

// 手动退出线程
void Hnc848System::forceThreadtoQuit()
{
    quitThread = true;
}

// 创建新的一天的文件
void Hnc848System::niceNewDay(QString panda)
{
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    cncFileDir = panda+"/CNC机床数据"+"("+currentDate+")";                                  // cnc专属文件夹
    cncAlarmPath = cncFileDir+"/报警历史"+".csv";
    QString alarmHeader = "出现时间,报警号,报警文本内容";

    if(!cncDir->exists(cncFileDir))
    {
        cncDir->mkdir(cncFileDir);
    }

    if(!QFile::exists(cncAlarmPath))
    {
        writeFile(cncAlarmPath,alarmHeader);
    }
}

//数控机床的子线程
void Hnc848System::run()
{
    short writeStatus105 = 0,writeStatus106 = 0,writeStatus107 = 0;
    if(!connect2CNC()) return;             // 连接不成功，退出线程
    cncWorkingStatus = true;
    while(1)
    {
        if(time2ReadCNCData)               // 定时采集数据
        {
            time2ReadCNCData = false;
            if(!getCNCData())              // 连接非正常中断，退出线程
            {
                cncWorkingStatus = false;
                return;
            }
            recordCNC(CNCInfo);            // 记录数据到CSV文件中
        }

        if(time2WriteRegisters)              // 补偿线程要求写入数控系统寄存器
        {
            if(time2WriteRegisters == 1)  // 写入补偿值
            {
                writeStatus105 = setHncReg(105,compValue[0],clientNo);
                writeStatus106 = setHncReg(106,compValue[1],clientNo);
                writeStatus107 = setHncReg(107,compValue[2],clientNo);
                emit sendPara(writeStatus105,writeStatus106,writeStatus107,compValue[0],compValue[1],compValue[2]);
            }
            if(time2WriteRegisters == 2)  // 清零
            {
                writeStatus105 = setHncReg(105,0,clientNo);
                writeStatus106 = setHncReg(106,0,clientNo);
                writeStatus107 = setHncReg(107,0,clientNo);
                emit sendPara(writeStatus105,writeStatus106,writeStatus107,0,0,0);
            }
            time2WriteRegisters = 0;
        }
        statusFor1191 = readHncReg(100,clientNo); // 时刻更新Y100的示数

        if(quitThread)
        {
            cncWorkingStatus = false;
            emit sendMsg("退出hnc线程",false);
            return;
        }
    }
}
