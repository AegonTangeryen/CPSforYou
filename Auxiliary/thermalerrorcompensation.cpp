#include "thermalerrorcompensation.h"

ThermalErrorCompensation::ThermalErrorCompensation(QString path)
{
    compenPath = path;
    compenCnt = 0;
    compPermission = false;
    clearFlag = false;
    firstZero = false;
    time2Quit = false;
    uAreFree2Comp = false;

    // 设置关键温度测点
    ModelParameter foryou0(7,1,NULL),foryou1(7,2,NULL),foryou2(7,3,NULL),foryou3(7,4,NULL);
    paraVector.append(foryou0);
    paraVector.append(foryou1);
    paraVector.append(foryou2);
    paraVector.append(foryou3);

    QString currentDate = QDateTime::currentDateTime().toString("yyyyMMdd");
    compenPath = compenPath+"/预测和补偿记录"+currentDate+".csv";
    QString csvHeader = "时间,次数,当前预测值,上一次预测值,当前补偿值";
    if(!QFile::exists(compenPath))
    {
        writeFile(compenPath,csvHeader);
    }

    duketimer = new QTimer(this);
    connect(duketimer,&QTimer::timeout, this,&ThermalErrorCompensation::timeisup);
    duketimer->setInterval(5000);         // 5s计算一次补偿值
    duketimer->setTimerType(Qt::PreciseTimer);
    duketimer->start();
}

ThermalErrorCompensation::~ThermalErrorCompensation()
{
    delete duketimer;
}

void ThermalErrorCompensation::timeisup()
{
    uAreFree2Comp = true;
}

//模型预测
QVector<QString> last_sent_FBG(inputNum);                 // 初次的FBG
QVector<QString> sent_FBG(inputNum);                        // 本次的FBG
double ThermalErrorCompensation::predictionModels()
{
    int columns = inputNum+1;                           // 参数个数
    int i = 0;
    for (i = 0; i < paraVector.size(); i++)             // 读取关键温度测点实时温度数据
    {
        sent_FBG[i] = DS18B20_ALL_Node[paraVector[i].md_channel - 1][paraVector[i].md_indx - 1].temperature;
    }

    QVector<double> delta_FBG(inputNum);					// 本次与初次的FBG差值
    if (last_sent_FBG[0].length() == 0)                 // 如果是初次计算
    {
        for (int i = 0; i<inputNum; i++)
        {
            last_sent_FBG[i] = sent_FBG[i];             // 仅存储当前的FBG，作为下一次计算的基准
        }
        return NULL;                                    // 退出
    }

    for (int i = 0; i<inputNum; i++)                    // 如果不是初次计算，计算FBG增量，并转换为温度
    {
        delta_FBG[i] = sent_FBG[i].toDouble() - last_sent_FBG[i].toDouble();
    }

    double forU[5]={-0.014174801,0.008462905,0.003952930,-0.002877171,0.001796639};
    QVector<double> Answerz(columns);
    for (i = 0; i < columns; i++)
    {
        Answerz[i] = forU[i];
    }
    double Z = Answerz[0];
    for (int i = 0; i<inputNum; i++)
    {
        Z += Answerz[i + 1] * delta_FBG[i];       // 计算预测值，单位：mm
    }
    emit replyPredictionResult(Z);
    compenCnt++;

    return Z;
}

//补偿策略
double LastXPredict,LastYPredict,LastZPredict;
double XSum=0,YSum=0,ZSum=0;
void ThermalErrorCompensation::compensationStrategy(double xAxis,double yAxis,double zAxis)
{
    double xPredict,yPredict,zPredict;
    double xGap=0,yGap=0,zGap=0;        // 前向差分
    unsigned int xComp=0,yComp=0,zComp=0;

    xPredict = xAxis;                // x轴当前预测值
    yPredict = yAxis;                // y轴当前预测值
    zPredict = zAxis;                // Z轴当前预测值

    if(compenCnt == 1)               // 如果是开机之后的第一次补偿运算
    {
        LastXPredict = xPredict;     // 把当前预测值保存为上一次预测值，不做其他操作
        LastYPredict = yPredict;
        LastZPredict = zPredict;
        xComp = 0;
        yComp = 0;
        zComp = 0;
    }
    else
    {
        xGap = xPredict - LastXPredict;
        yGap = yPredict - LastYPredict;
        zGap = zPredict - LastZPredict;

        if(clearFlag)             // 前面的补偿值已经传送，覆盖
        {
            clearFlag=false;
            XSum = xGap;
            YSum = yGap;
            ZSum = zGap;
        }
        else                      // 前面的补偿值没有传送，则累加
        {
            XSum+=xGap;
            YSum+=yGap;
            ZSum+=zGap;
        }

        if(XSum<=0) {xComp = abs(XSum);}   // 计算实际补偿值
        else {xComp = XSum +128;}
        if(YSum<=0) {yComp = abs(YSum);}
        else {yComp = YSum +128;}
        if(ZSum<=0) {zComp = abs(ZSum);}
        else {zComp = ZSum +128;}

        if(XSum<=-25) {xComp = 25;}          // 阈值保护一
        else if(XSum>=25) {xComp = 25+128;}  // 如果累加量超出阈值，按最大阈值算
        if(YSum<=-25) {yComp = 25;}
        else if(YSum>=25) {yComp = 25+128;}  // 阈值是正负25um (2017.9.14)
        if(ZSum<=-25) {zComp = 25;}
        else if(ZSum>=25) {zComp = 25+128;}

        if(xComp>255 || xComp ==128) xComp = 0;            // 阈值保护二
        if(yComp>255 || yComp ==128) yComp = 0;            // 如果累加量超出范围，则此次不补偿
        if(zComp>255 || zComp ==128) zComp = 0;

        compValue[0] = xComp;
        compValue[1] = yComp;
        compValue[2] = zComp;

        LastXPredict = xPredict;
        LastYPredict = yPredict;
        LastZPredict = zPredict;

        compPermission = true;
    }

    QString currentTime =QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString compenContent = currentTime+","+QString::number(compenCnt,10,6)+","+QString::number(LastZPredict,10,6)
            +","+QString::number(zPredict,10,6)+", ";
    writeFile(compenPath,compenContent);
}

// 强制退出线程
void ThermalErrorCompensation::forceThread2Quit()
{
    time2Quit = true;
}

// 创建新的一天的文件夹
void ThermalErrorCompensation::niceNewDay(QString gaintPanda)
{
    QString currentDate = QDateTime::currentDateTime().toString("yyyyMMdd");
    compenPath = gaintPanda+"/预测和补偿记录"+currentDate+".csv";
    QString csvHeader = "时间,次数,当前预测值,上一次预测值,当前补偿值";
    if(!QFile::exists(compenPath))
    {
        writeFile(compenPath,csvHeader);
    }
}

// 子线程
void ThermalErrorCompensation::run()
{
    while (1)
    {
        if(cncWorkingStatus == false || ds18WorkingStatus == false) return;
        if(uAreFree2Comp)                  // 预测，并转化为补偿值
        {
            uAreFree2Comp = false;
            compensationStrategy(0,0,1000*predictionModels());
        }

        if(compPermission && (statusFor1191 == 7)) // 补偿许可+到达补偿G代码段+补偿值未传送
        {
            compPermission = false;
            time2WriteRegisters = 1;                             // 可以写入补偿值
            firstZero = true;                                          // 补偿值已传送，可以清零寄存器
        }
        if(firstZero && (statusFor1191 == 0))            // 可以清零+补偿完毕
        {
            clearFlag = true;                                        // 累加补偿值可以清空
            firstZero = false;
            time2WriteRegisters = 2;                             // 寄存器清零
            emit replyAcutalCompensation(compValue[2]);
            QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
            QString comptext = currentTime+", "+", "+", ,"+QString::number(compValue[2]);
            writeFile(compenPath,comptext);
        }
        if(time2Quit) return;
    }
}
