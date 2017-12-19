#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

/*-------------------------------显示页面初始化------------------- -------------------*/
    // 最下方状态栏初始化配置
    statusbarCNCLabel = new QLabel("数控系统提示");
    statusbarDs18Label = new QLabel("DS18b20未连接  ");
    statusbarFBGLabel = new QLabel("FBG提示  ");
    statusbarCCDLabel = new QLabel("位移传感器提示  ");

    statusbarCNCLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    statusbarCNCLabel->setFont(QFont("Timers",14,QFont::Bold));
    statusbarCNCLabel->setStyleSheet("color:red");
    statusbarDs18Label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    statusbarDs18Label->setFont(QFont("Timers",14,QFont::Bold));
    statusbarDs18Label->setStyleSheet("color:red");
    statusbarFBGLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    statusbarFBGLabel->setFont(QFont("Timers",14,QFont::Bold));
    statusbarFBGLabel->setStyleSheet("color:red");
    statusbarCCDLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    statusbarCCDLabel->setFont(QFont("Timers",14,QFont::Bold));
    statusbarCCDLabel->setStyleSheet("color:red");

    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));// 设置不显示label的边框
    statusBar()->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
    statusBar()->addWidget(statusbarCNCLabel);
    statusBar()->addWidget(statusbarDs18Label);
    statusBar()->addWidget(statusbarFBGLabel);
    statusBar()->addWidget(statusbarCCDLabel);

    // 选项卡“首页”初始化配置
    ui->cncdislink_pushButton->setEnabled(false);
    ui->ds18dislink_pushButton->setEnabled(false);
    ui->FBGclose_pushButton->setEnabled(false);
    ui->closeccd_pushButton->setEnabled(false);
    ui->envdislinkpushButton->setEnabled(false);
    ui->dislinkcloud_pushButton->setEnabled(false);

    // 选项卡“数控系统信息”页面初始化配置

    // 选项卡“FBG传感器”页面初始化配置
    fbgChart = new QChart();
    fbgChart->setTitle("FBG传感器关键点展示");
    fbgChart->legend()->setAlignment(Qt::AlignRight);     // 图例放在右方
    fbgChart->setAnimationOptions(QChart::AllAnimations); // 图形伸缩时有动画效果
    fbgChart->setTheme(QChart::ChartThemeBlueCerulean);

    fbgSeriesCh1600 = new QSplineSeries(fbgChart);
    QPen red(Qt::red);
    red.setWidth(3);
    fbgSeriesCh1600->setPen(red);
    fbgSeriesCh1600->setName("CH16-1");

    fbgXaxis = new QDateTimeAxis();                      // 横轴是时间轴
    fbgXaxis->setTickCount(10);
    fbgXaxis->setFormat("hh:mm:ss");
    fbgXaxis->setLabelsAngle(20);
    fbgXaxis->setTitleFont(QFont("Timers",10,QFont::Bold));
    fbgXaxis->setTitleText("Time(hh:mm:ss)");

    fbgYaxis = new QValueAxis();
    fbgYaxis->setTickCount(10);
    fbgYaxis->setLabelFormat("%g");
    fbgYaxis->setMinorTickCount(5);
    fbgYaxis->setRange(1500,1600);
    fbgYaxis->setTitleText("Wave length(um)");
    fbgYaxis->setTitleFont(QFont("Timers",10,QFont::Bold));

    fbgChart->addSeries(fbgSeriesCh1600);                   // 添加这一条线到图中
    fbgChart->createDefaultAxes();
    fbgChart->setAxisX(fbgXaxis, fbgSeriesCh1600);
    fbgChart->setAxisY(fbgYaxis, fbgSeriesCh1600);

    ui->fbgchartview->setRenderHint(QPainter::Antialiasing); // 抗锯齿
    ui->fbgchartview->setChart(fbgChart);
    connect(ui->FBGseeallpushButton,&QPushButton::clicked,this,&MainWindow::fbgSeeAll);

    // 选项卡“电类温度传感器”页面初始化配置
    connect(ui->ds18seeallpushButton,&QPushButton::clicked,this,&MainWindow::ds18SeeAll);

    // 选项卡“数控系统信息”页面初始化配置

    // 选项卡“位移传感器”页面初始化配置
    laserSensorChart = new QChart();
    laserSensorChart->setTitle("FBG传感器关键点展示");
    laserSensorChart->legend()->setAlignment(Qt::AlignRight);     // 图例放在右方
    laserSensorChart->setAnimationOptions(QChart::AllAnimations); // 图形伸缩时有动画效果
    laserSensorChart->setTheme(QChart::ChartThemeBlueCerulean);

    laserSensorX = new QSplineSeries();
    red.setColor(Qt::red);
    red.setWidth(3);
    laserSensorX->setPen(red);
    laserSensorX->setName("X轴");
    laserSensorY = new QSplineSeries();
    red.setColor(Qt::darkBlue);
    laserSensorY->setPen(red);
    laserSensorY->setName("Y轴");
    laserSensorZ = new QSplineSeries();
    red.setColor(Qt::darkGreen);
    laserSensorZ->setPen(red);
    laserSensorZ->setName("Z轴");

    laserSensorXaxis = new QDateTimeAxis();                      // 横轴是时间轴
    laserSensorXaxis->setTickCount(10);
    laserSensorXaxis->setFormat("hh:mm:ss");
    laserSensorXaxis->setLabelsAngle(20);
    laserSensorXaxis->setTitleFont(QFont("Timers",10,QFont::Bold));
    laserSensorXaxis->setTitleText("Time(hh:mm:ss)");

    laserSensorYaxis = new QValueAxis();
    laserSensorYaxis->setTickCount(10);
    laserSensorYaxis->setLabelFormat("%g");
    laserSensorYaxis->setMinorTickCount(5);
    laserSensorYaxis->setRange(1500,1600);
    laserSensorYaxis->setTitleText("Displacement(mm)");
    laserSensorYaxis->setTitleFont(QFont("Timers",10,QFont::Bold));

    laserSensorChart->addSeries(laserSensorX);
    laserSensorChart->addSeries(laserSensorY);
    laserSensorChart->addSeries(laserSensorZ);
    laserSensorChart->createDefaultAxes();
    laserSensorChart->setAxisX(laserSensorXaxis, laserSensorX);
    laserSensorChart->setAxisY(laserSensorYaxis, laserSensorX);

    ui->laserchartview->setRenderHint(QPainter::Antialiasing); // 抗锯齿
    ui->laserchartview->setChart(laserSensorChart);

    // 选项卡“云服务平台”页面初始化配置

    // 选项卡“热误差补偿”页面初始化配置
    connect(ui->clearcomp_pushButton,&QPushButton::clicked,this,&MainWindow::clearCompBrowser);

/*-------------------------------创建数据存储文件夹-------------------------------------*/
    currentday = QDateTime::currentDateTime().toString("yyyyMMdd");
    currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    lwfdir = new QDir();
    rootPath = lwfdir->currentPath()+"/数据大家族";
    if(lwfdir->exists(rootPath)) qDebug()<<"根目录已存在!";
    else
    {
        if(lwfdir->mkdir(rootPath)) qDebug()<<"根目录创建成功！";
    }

    EverydayPath = rootPath+"/数据家族的日常"+"("+currentDate+")";
    if(lwfdir->exists(EverydayPath)) qDebug()<<"每日数据集已存在！";
    else
    {
        if(lwfdir->mkdir(EverydayPath)) qDebug()<<"每日数据集创建成功！";
    }

    originalPath = EverydayPath+"/数据家族全家福"+"("+currentDate+")";
    if(lwfdir->exists(originalPath)) qDebug()<<"原始数据集已存在！";
    else
    {
        if(lwfdir->mkdir(originalPath)) qDebug()<<"原始数据集创建成功！";
    }

    samplePath = EverydayPath+"/数据家族小可爱"+"("+currentDate+")";
    if(lwfdir->exists(samplePath)) qDebug()<<"抽样数据集已存在！";
    else
    {
        if(lwfdir->mkdir(samplePath)) qDebug()<<"抽样数据集创建成功！";
    }
/*-------------------------------全局变量初始化----------------------------------*/
    for(int gyn=0; gyn<FBG_Channel_Max; gyn++)
    {
        for(int jn=0; jn<FBG_Index_Max; jn++)
        {
            FBG_ALL[gyn][jn] = QString::number(255,10);
        }
    }

    for(int i=0; i<DS18B20_Channel_Max;i++)
    {
        for(int j =0;j<DS18B20_Index_Max;j++)
        {
            DS18B20_ALL_Node[i][j].ID = "0";
            DS18B20_ALL_Node[i][j].temperature = "85";
        }
    }

    for(int i=0; i<DS18B20_Channel_Max;i++)
    {
        for(int j =0;j<DS18B20_Index_Max;j++)
        {
            DS18B20_ADD_Node[i][j].ID = "0";
            DS18B20_ADD_Node[i][j].temperature = "86";
        }
    }

    for(int i=0; i<Env_Number_Max;i++)
    {
        ENV_ALL_Node[i].ID = "0";
        ENV_ALL_Node[i].temperature = "87";
    }

    ccdInfo[0] = "888888";
    ccdInfo[1] = "888888";
    ccdInfo[2] = "888888";

/*-----------------------------主线程成员变量初始化-----------------------------------*/
    taskTimeCnt =0;
    globalLock = new QMutex();
    kingTimer = new QTimer(this);
    connect(kingTimer,&QTimer::timeout, this,MainWindow::timeisup);
    kingTimer->setTimerType(Qt::PreciseTimer);
    kingTimer->setInterval(1000); // 每1s中断一次
    kingTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**********************************************************************************************

                                    0. 软件运行维护相关

***********************************************************************************************/
// 主定时器中断处理函数
void MainWindow::timeisup()
{
    // 又是新的一天，创建新的存储目录
    if(QDateTime::currentDateTime().toString("yyyyMMdd") != currentday)
    {
        currentday = QDateTime::currentDateTime().toString("yyyyMMdd");
        currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
        EverydayPath = rootPath+"/数据家族的日常"+"("+currentDate+")";
        if(lwfdir->exists(EverydayPath))qDebug()<<"新的一天数据集已存在！";
        else
        {
            if(lwfdir->mkdir(EverydayPath)) qDebug()<<"新的一天数据集创建成功！";
        }

        originalPath = EverydayPath+"/数据家族全家福"+"("+currentDate+")";
        if(lwfdir->exists(originalPath)) qDebug()<<"原始数据集已存在！";
        else
        {
            if(lwfdir->mkdir(originalPath)) qDebug()<<"原始数据集创建成功！";
        }

        samplePath = EverydayPath+"/数据家族小可爱"+"("+currentDate+")";
        if(lwfdir->exists(samplePath)) qDebug()<<"抽样数据集已存在！";
        else
        {
            if(lwfdir->mkdir(samplePath)) qDebug()<<"抽样数据集创建成功！";
        }
        emit createNewDayFolder(originalPath); // 发送信号指示各子线程更换文件存储路径

        QString nowTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
        if(fbgWorkingStatus) // 如果FBG传感器正在工作，创建新文件夹
        {
            fbgSamplePath = samplePath+"/FBG波长数据("+nowTime+")";
            if(lwfdir->exists(fbgSamplePath)) qDebug()<<"!rose1";
            else
            {
                if(lwfdir->mkdir(fbgSamplePath)) qDebug()<<"rose1";
            }

            FbgAllDataPath = fbgSamplePath+"/TCH.csv";
            QString csvHeader = "时间";
            for(int channum=1;channum<=32;channum++)
            {
                QString title;
                for(int indexnum=1;indexnum<=20;indexnum++)
                {
                    if(channum<10 && indexnum<10)
                    {
                        title = ",TCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else if(channum<10 && indexnum>=10)
                    {
                        title = ",TCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    else if(channum>=10 &&indexnum<10)
                    {
                        title = ",TCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else
                    {
                        title = ",TCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    csvHeader+=title;
                }
            }
            if(QFile::exists(FbgAllDataPath)) qDebug()<<"dragon1.1";
            else
            {
                if(writeFile(FbgAllDataPath,csvHeader))
                qDebug()<<"dragon1.1";
            }

            fbgAllStressPath = fbgSamplePath+"/TSCH.csv";
            csvHeader = "时间";
            for(int channum=1;channum<=7;channum++)
            {
                QString title;
                for(int indexnum=1;indexnum<=20;indexnum++)
                {
                    if(channum<10 && indexnum<10)
                    {
                        title = ",TCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else if(channum<10 && indexnum>=10)
                    {
                        title = ",TCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    else if(channum>=10 &&indexnum<10)
                    {
                        title = ",TCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else
                    {
                        title = ",TCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    csvHeader+=title;
                }
            }
            if(QFile::exists(fbgAllStressPath)) qDebug()<<"dragon1.2";
            else
            {
                if(writeFile(fbgAllStressPath,csvHeader))
                qDebug()<<"dragon1.2";
            }

            fbgAllTempPath = fbgSamplePath+"/TTCH.csv";
            csvHeader = "时间";
            for(int channum=8;channum<=32;channum++)
            {
                QString title;
                for(int indexnum=1;indexnum<=20;indexnum++)
                {
                    if(channum<10 && indexnum<10)
                    {
                        title = ",TCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else if(channum<10 && indexnum>=10)
                    {
                        title = ",TCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    else if(channum>=10 &&indexnum<10)
                    {
                        title = ",TCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else
                    {
                        title = ",TCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    csvHeader+=title;
                }
            }
            if(QFile::exists(fbgAllTempPath)) qDebug()<<"dragon1.3";
            else
            {
                if(writeFile(fbgAllTempPath,csvHeader))
                qDebug()<<"dragon1.3";
            }
        }
        if(ds18WorkingStatus || ds18No2WorkStatus) // 如果电类传感器正在工作，创建新文件夹
        {
            ds18SamplePath = samplePath+"/WiFi温度数据("+nowTime+")";
            ds18No1SamplePath = ds18SamplePath+"/WiFi温度数据一号板("+nowTime+")";
            ds18No2SamplePath = ds18SamplePath+"/WiFi温度数据二号板("+nowTime+")";
            if(lwfdir->exists(ds18SamplePath)) qDebug()<<"!rose2";
            else
            {
                if(lwfdir->mkdir(ds18SamplePath)) qDebug()<<"rose2";
            }
            if(lwfdir->exists(ds18No1SamplePath)) qDebug()<<"!rose2.1";
            else
            {
                if(lwfdir->mkdir(ds18No1SamplePath)) qDebug()<<"rose2.1";
            }
            if(lwfdir->exists(ds18No2SamplePath)) qDebug()<<"!rose2.2";
            else
            {
                if(lwfdir->mkdir(ds18No2SamplePath)) qDebug()<<"rose2.2";
            }

            ds18AllDataPath = ds18SamplePath+"/DCH.csv";
            QString csvHeader = "时间";
            for(int channum=1;channum<= 16;channum++)
            {
                QString title;
                for(int indexnum=1;indexnum<=8;indexnum++)
                {
                    if(channum<10 && indexnum<10)
                    {
                        title = ",DCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else if(channum<10 && indexnum>=10)
                    {
                        title = ",DCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    else if(channum>=10 &&indexnum<10)
                    {
                        title = ",DCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else
                    {
                        title = ",DCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    csvHeader+=title;
                }
            }
            if(QFile::exists(ds18AllDataPath)) qDebug()<<"dragon2";
            else
            {
                if(writeFile(ds18AllDataPath,csvHeader))
                qDebug()<<"dragon2";
            }

            dsNo1DataPath = ds18No1SamplePath+"/DCH1.csv";
            dsNo2DataPath = ds18No2SamplePath+"/DCH2.csv";
            csvHeader = "时间";
            for(int channum=1;channum<= 8;channum++)
            {
                QString title;
                for(int indexnum=1;indexnum<=8;indexnum++)
                {
                    if(channum<10 && indexnum<10)
                    {
                        title = ",DCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else if(channum<10 && indexnum>=10)
                    {
                        title = ",DCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    else if(channum>=10 &&indexnum<10)
                    {
                        title = ",DCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else
                    {
                        title = ",DCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    csvHeader+=title;
                }
            }
            if(QFile::exists(dsNo1DataPath)) qDebug()<<"dragon2.1";
            else
            {
                if(writeFile(dsNo1DataPath,csvHeader))
                qDebug()<<"dragon2.1";
            }

            csvHeader = "时间";
            for(int channum=9;channum<= 16;channum++)
            {
                QString title;
                for(int indexnum=1;indexnum<=8;indexnum++)
                {
                    if(channum<10 && indexnum<10)
                    {
                        title = ",DCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else if(channum<10 && indexnum>=10)
                    {
                        title = ",DCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    else if(channum>=10 &&indexnum<10)
                    {
                        title = ",DCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
                    }
                    else
                    {
                        title = ",DCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
                    }
                    csvHeader+=title;
                }
            }
            if(QFile::exists(dsNo2DataPath)) qDebug()<<"dragon2.2";
            else
            {
                if(writeFile(dsNo2DataPath,csvHeader))
                qDebug()<<"dragon2.2";
            }
        }

        if(envWorkingStatus) // 如果环境温度传感器正在工作，创建新文件夹
        {
            envSamplePath = samplePath+"/环境温度("+nowTime+")";
            if(lwfdir->exists(envSamplePath)) qDebug()<<"!rose3";
            else
            {
                if(lwfdir->mkdir(envSamplePath)) qDebug()<<"rose3";
            }

            envAllDataPath = envSamplePath+"/EDCH.csv";
            QString csvHeader = "时间,EDCH01-01,EDCH01-02,EDCH02-01,EDCH02-02";
            if(QFile::exists(envAllDataPath)) qDebug()<<"dragon3";
            else
            {
                if(writeFile(envAllDataPath,csvHeader))
                qDebug()<<"dragon3";
            }
        }

        if(cncWorkingStatus) // 如果数控机床正在工作，创建新文件夹(一般不可能)
        {
            hncSamplePath = samplePath+"/CNC机床数据("+nowTime+")";
            if(lwfdir->exists(hncSamplePath)) qDebug()<<"!rose4";
            else
            {
                if(lwfdir->mkdir(hncSamplePath)) qDebug()<<"!rose4";
            }

            hncAllDataPath = hncSamplePath+"/CNC数据值.csv";
            QString csvHeader = "时间,机床通道,X轴坐标,Y轴坐标,Z轴坐标,主轴坐标,进给速度,主轴速度,X轴功率,Y轴功率,Z轴功率,主轴功率,X轴负荷,Y轴负荷,Z轴负荷,主轴负荷,暂停状态";
            if(QFile::exists(hncAllDataPath)) qDebug()<<"dragon4";
            else
            {
                if(writeFile(hncAllDataPath,csvHeader))
                qDebug()<<"dragon4";
            }
        }

        if(laserWorkingStatus) // 如果激光位移传感器正在工作，创建新文件夹
        {
            laserSamplePath = samplePath+"/CCD位移数据("+nowTime+")";
            if(lwfdir->exists(laserSamplePath)) qDebug()<<"!rose5";
            else
            {
                if(lwfdir->mkdir(laserSamplePath)) qDebug()<<"!rose5";
            }

            laserAllDataPath = laserSamplePath+"/CCD数据值.csv";
            QString csvHeader = "时间,X轴位移,Y轴位移,Z轴位移";
            if(QFile::exists(laserAllDataPath)) qDebug()<<"dragon5";
            else
            {
                if(writeFile(laserAllDataPath,csvHeader))
                qDebug()<<"dragon5";
            }
        }
    }

    taskTimeCnt++;
    if(taskTimeCnt %5 == 0)         // 每5s抽样一次
    {
        if(fbgWorkingStatus) recordAllFbg();
        if(ds18WorkingStatus && ds18No2WorkStatus) recordAllDs18b20(DS18B20_ALL_Node,DS18B20_Channel_Max,DS18B20_ADD_Node,DS18B20_Channel_Max);
        if(ds18WorkingStatus) recordNo1Ds18b20(DS18B20_ALL_Node,DS18B20_Channel_Max);
        if(ds18No2WorkStatus) recordNo2Ds18b20(DS18B20_ADD_Node,DS18B20_Channel_Max);
        if(envWorkingStatus) recordAllEnvironmentt(ENV_ALL_Node,Env_Number_Max);
        if(cncWorkingStatus) recordAllCnc(CNCInfo);
        if(laserWorkingStatus) recordAllLaserSensors(ccdInfo);
    }

    ui->_1191_Browserlabel->clear();
    ui->_1191_Browserlabel->setText("1191状态第"+QString::number(taskTimeCnt)+"次："+QString::number(statusFor1191));
    ui->x_lcdNumber->setText(ccdInfo[0]);
    ui->y_lcdNumber->setText(ccdInfo[1]);
    ui->z_lcdNumber->setText(ccdInfo[2]);

    if(taskTimeCnt == 19941008)    // 计数器清零
    {
        taskTimeCnt = 0;
    }
}

// 1.记录光纤光栅传感器全部数据
void MainWindow::recordAllFbg()
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString fbgContent = currentTime;
    for(int i=0;i<FBG_Channel_Max;i++)                               // 写1~32通道总表
    {
        if(FBG_ALL[i][0]=="255") break;                           // 还没有收到数据
        for(int j=0;j<FBG_Index_Max;j++)
        {
            fbgContent = fbgContent+","+FBG_ALL[i][j];
        }
    }
    writeFile(FbgAllDataPath,fbgContent);

    fbgContent.clear();  fbgContent = currentTime;                // 写1~7通道应力传感器总表
    for(int i=0;i<8;i++)
    {
        if(FBG_ALL[i][0]=="255") break;                           // 还没有收到数据
        for(int j=0;j<FBG_Index_Max;j++)
        {
            fbgContent = fbgContent+","+FBG_ALL[i][j];
        }
    }
    writeFile(fbgAllStressPath,fbgContent);

    fbgContent.clear();  fbgContent = currentTime;              // 写8~32通道温度传感器总表
    for(int i=8;i<FBG_Channel_Max;i++)
    {
        if(FBG_ALL[i][0]=="255") break;                           // 还没有收到数据
        for(int j=0;j<FBG_Index_Max;j++)
        {
            fbgContent = fbgContent+","+FBG_ALL[i][j];
        }
    }
    writeFile(fbgAllTempPath,fbgContent);
}

// 2.记录电类温度传感器全部数据
void MainWindow::recordAllDs18b20(DS18B20_Node (*a)[DS18B20_Index_Max], int nrow1,DS18B20_Node (*b)[DS18B20_Index_Max],int nrow2)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString ds18Content;
    ds18Content = currentTime;
    for(int row =0; row < nrow1; row++)
    {
        for(int col = 0;col < DS18B20_Index_Max; col++)
        {
            if(a[row][col].ID=="0") continue;
            ds18Content+=",";
            ds18Content+=a[row][col].temperature;
        }
    }
    for(int row =0; row < nrow2; row++)
    {
        for(int col = 0;col < DS18B20_Index_Max; col++)
        {
            if(b[row][col].ID=="0") continue;
            ds18Content+=",";
            ds18Content+=b[row][col].temperature;
        }
    }
    writeFile(ds18AllDataPath,ds18Content);
}

// 2.1 记录电类温度传感器一号板全部数据
void MainWindow::recordNo1Ds18b20(DS18B20_Node (*a)[DS18B20_Index_Max], int nrow)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString ds18Content;
    ds18Content = currentTime;
    for(int row =0; row < nrow; row++)
    {
        for(int col = 0;col < DS18B20_Index_Max; col++)
        {
            if(a[row][col].ID=="0") continue;
            ds18Content+=",";
            ds18Content+=a[row][col].temperature;
        }
    }
    writeFile(dsNo1DataPath,ds18Content);
}

// 2.2 记录电类温度传感器二号板全部数据
void MainWindow::recordNo2Ds18b20(DS18B20_Node (*b)[DS18B20_Index_Max], int nrow)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString ds18Content;
    ds18Content = currentTime;
    for(int row =0; row < nrow; row++)
    {
        for(int col = 0;col < DS18B20_Index_Max; col++)
        {
            if(b[row][col].ID=="0") continue;
            ds18Content+=",";
            ds18Content+=b[row][col].temperature;
        }
    }
    writeFile(dsNo2DataPath,ds18Content);
}

// 3.记录环境温度传感器全部数据
void MainWindow::recordAllEnvironmentt(Env_Node *a, int nrow)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString content = currentTime;
    for(int row=0; row < nrow; row++)       // 写总表
    {
        if(a[row].ID=="0") continue;             // 某些节点还没有收到数据
        content+=",";
        content+=a[row].temperature;
    }
    writeFile(envAllDataPath,content);
}

// 4.记录华中数控系统全部数据
void MainWindow::recordAllCnc(CNCInfoReg CNCInfo)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString cncContent;
    cncContent = currentTime+","+QString::number(CNCInfo.ch, 10)+","+QString::number(CNCInfo.AXIS_X_POS, 10, 4)+","+QString::number(CNCInfo.AXIS_Y_POS, 10, 4)
            +","+QString::number(CNCInfo.AXIS_Z_POS, 10, 4)+","+QString::number(CNCInfo.AXIS_MA_POS, 10, 4)+","+QString::number(CNCInfo.feedrate, 10, 4)
            +","+QString::number(CNCInfo.speed, 10, 4)+","+QString::number(CNCInfo.AXIS_X_PWR, 10, 4)+","+QString::number(CNCInfo.AXIS_Y_PWR, 10, 4)
            +","+QString::number(CNCInfo.AXIS_Z_PWR, 10, 4)+","+QString::number(CNCInfo.AXIS_MA_PWR, 10, 4)+","+QString::number(CNCInfo.AXIS_X_FUHE, 10, 4)
            +","+QString::number(CNCInfo.AXIS_Y_FUHE, 10, 4)+","+QString::number(CNCInfo.AXIS_Z_FUHE, 10, 4)+","+QString::number(CNCInfo.AXIS_MA_FUHE, 10, 4)
            +","+CNCInfo.PauseStatus;
    writeFile(hncAllDataPath,cncContent);
}

// 5.记录激光位移传感器全部数据
void MainWindow::recordAllLaserSensors(QString *gc)
{
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString ccdContent = currentTime;
    ccdContent = ccdContent+","+gc[0]+","+gc[1]+","+gc[2];
    writeFile(laserAllDataPath,ccdContent);
}

/**********************************************************************************************

                                          1.FBG传感器部分

***********************************************************************************************/
// 连接FBG解调仪
void MainWindow::on_FBGlink_pushButton_clicked()
{
    QString nowTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    fbgSamplePath = samplePath+"/FBG波长数据("+nowTime+")";
    if(lwfdir->exists(fbgSamplePath)) qDebug()<<"!wolf1";
    else
    {
        if(lwfdir->mkdir(fbgSamplePath)) qDebug()<<"wolf1";
    }

    FbgAllDataPath = fbgSamplePath+"/TCH.csv";
    QString csvHeader = "时间";
    for(int channum=1;channum<=32;channum++)
    {
        QString title;
        for(int indexnum=1;indexnum<=20;indexnum++)
        {
            if(channum<10 && indexnum<10)
            {
                title = ",TCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else if(channum<10 && indexnum>=10)
            {
                title = ",TCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            else if(channum>=10 &&indexnum<10)
            {
                title = ",TCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else
            {
                title = ",TCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            csvHeader+=title;
        }
    }
    if(QFile::exists(FbgAllDataPath)) qDebug()<<"dragon1.1";
    else
    {
        if(writeFile(FbgAllDataPath,csvHeader))
        qDebug()<<"dragon1.1";
    }

    fbgAllStressPath = fbgSamplePath+"/TSCH.csv";
    csvHeader = "时间";
    for(int channum=1;channum<=7;channum++)
    {
        QString title;
        for(int indexnum=1;indexnum<=20;indexnum++)
        {
            if(channum<10 && indexnum<10)
            {
                title = ",TCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else if(channum<10 && indexnum>=10)
            {
                title = ",TCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            else if(channum>=10 &&indexnum<10)
            {
                title = ",TCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else
            {
                title = ",TCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            csvHeader+=title;
        }
    }
    if(QFile::exists(fbgAllStressPath)) qDebug()<<"dragon1.2";
    else
    {
        if(writeFile(fbgAllStressPath,csvHeader))
        qDebug()<<"dragon1.2";
    }

    fbgAllTempPath = fbgSamplePath+"/TTCH.csv";
    csvHeader = "时间";
    for(int channum=8;channum<=32;channum++)
    {
        QString title;
        for(int indexnum=1;indexnum<=20;indexnum++)
        {
            if(channum<10 && indexnum<10)
            {
                title = ",TCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else if(channum<10 && indexnum>=10)
            {
                title = ",TCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            else if(channum>=10 &&indexnum<10)
            {
                title = ",TCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else
            {
                title = ",TCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            csvHeader+=title;
        }
    }
    if(QFile::exists(fbgAllTempPath)) qDebug()<<"dragon1.3";
    else
    {
        if(writeFile(fbgAllTempPath,csvHeader))
        qDebug()<<"dragon1.3";
    }

    ui->FBGlink_pushButton->setEnabled(false);
    ui->FBGclose_pushButton->setEnabled(true);
    FBGUdpThread *fbgThread = new FBGUdpThread(originalPath);
    connect(fbgThread,&FBGUdpThread::passUdpInfo,this,&MainWindow::showFbgResults);
    connect(this,&MainWindow::createNewDayFolder,fbgThread,&FBGUdpThread::newDayforYou);
    connect(this,&MainWindow::closeFbgSocket,fbgThread,&FBGUdpThread::forceThread2Quit);
    connect(fbgThread,&FBGUdpThread::finished,fbgThread,&FBGUdpThread::deleteLater);
    fbgThread->start();
}

// 关闭连接
void MainWindow::on_FBGclose_pushButton_clicked()
{
    emit closeFbgSocket();
    ui->FBGlink_pushButton->setEnabled(true);
    ui->FBGclose_pushButton->setEnabled(false);
}

// 显示
void MainWindow::showFbgResults(int tywin)
{
//    switch (tywin)
//    {
//        case -1: ui->FBG_textBrowser->append("FBG线程已关闭，内存释放");
//            break;
//        case 0:  ui->FBG_textBrowser->append("FBG暂时断开");
//            break;
//        case 1:  ui->FBG_textBrowser->append("FBG保持连接");
//            break;
//        default: break;
//    }

}

void MainWindow::fbgSeeAll()
{}

/**********************************************************************************************

                                            2.DS18b20部分

***********************************************************************************************/
// 点击监听电类温度传感器之后
void MainWindow::on_ds18link_pushButton_clicked()
{
    QString nowTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    ds18SamplePath = samplePath+"/WiFi温度数据("+nowTime+")";
    ds18No1SamplePath = ds18SamplePath+"/WiFi温度数据一号板("+nowTime+")";
    ds18No2SamplePath = ds18SamplePath+"/WiFi温度数据二号板("+nowTime+")";
    if(lwfdir->exists(ds18SamplePath)) qDebug()<<"!wolf2";
    else
    {
        if(lwfdir->mkdir(ds18SamplePath)) qDebug()<<"wolf2";
    }
    if(lwfdir->exists(ds18No1SamplePath)) qDebug()<<"!wolf2.1";
    else
    {
        if(lwfdir->mkdir(ds18No1SamplePath)) qDebug()<<"wolf2.1";
    }
    if(lwfdir->exists(ds18No2SamplePath)) qDebug()<<"!wolf2.2";
    else
    {
        if(lwfdir->mkdir(ds18No2SamplePath)) qDebug()<<"wolf2.2";
    }

    ds18AllDataPath = ds18SamplePath+"/DCH.csv";
    QString csvHeader = "时间";
    for(int channum=1;channum<= 16;channum++)
    {
        QString title;
        for(int indexnum=1;indexnum<=8;indexnum++)
        {
            if(channum<10 && indexnum<10)
            {
                title = ",DCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else if(channum<10 && indexnum>=10)
            {
                title = ",DCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            else if(channum>=10 &&indexnum<10)
            {
                title = ",DCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else
            {
                title = ",DCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            csvHeader+=title;
        }
    }
    if(QFile::exists(ds18AllDataPath)) qDebug()<<"dragon2";
    else
    {
        if(writeFile(ds18AllDataPath,csvHeader))
        qDebug()<<"dragon2";
    }

    dsNo1DataPath = ds18No1SamplePath+"/DCH1.csv";
    dsNo2DataPath = ds18No2SamplePath+"/DCH2.csv";
    csvHeader = "时间";
    for(int channum=1;channum<= 8;channum++)
    {
        QString title;
        for(int indexnum=1;indexnum<=8;indexnum++)
        {
            if(channum<10 && indexnum<10)
            {
                title = ",DCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else if(channum<10 && indexnum>=10)
            {
                title = ",DCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            else if(channum>=10 &&indexnum<10)
            {
                title = ",DCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else
            {
                title = ",DCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            csvHeader+=title;
        }
    }
    if(QFile::exists(dsNo1DataPath)) qDebug()<<"dragon2.1";
    else
    {
        if(writeFile(dsNo1DataPath,csvHeader))
        qDebug()<<"dragon2.1";
    }

    csvHeader = "时间";
    for(int channum=9;channum<= 16;channum++)
    {
        QString title;
        for(int indexnum=1;indexnum<=8;indexnum++)
        {
            if(channum<10 && indexnum<10)
            {
                title = ",DCH0"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else if(channum<10 && indexnum>=10)
            {
                title = ",DCH0"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            else if(channum>=10 &&indexnum<10)
            {
                title = ",DCH"+QString::number(channum,10)+"-0"+QString::number(indexnum,10);
            }
            else
            {
                title = ",DCH"+QString::number(channum,10)+"-"+QString::number(indexnum,10);
            }
            csvHeader+=title;
        }
    }
    if(QFile::exists(dsNo2DataPath)) qDebug()<<"dragon2.2";
    else
    {
        if(writeFile(dsNo2DataPath,csvHeader))
        qDebug()<<"dragon2.2";
    }

    Ds18TcpThread *ds18Thread = new Ds18TcpThread(originalPath);
    connect(ds18Thread, &Ds18TcpThread::relayMsg2Ui,this,&MainWindow::showDS18Msg);
    connect(this,&MainWindow::closeDs18Sensors,ds18Thread,&Ds18TcpThread::forceThread2Quit);
    connect(this,&MainWindow::createNewDayFolder,ds18Thread,&Ds18TcpThread::newDayforYou);
    connect(ds18Thread, &Ds18TcpThread::finished, ds18Thread, &QObject::deleteLater);
    ds18Thread->start();
    ui->ds18link_pushButton->setEnabled(false);
    ui->ds18dislink_pushButton->setEnabled(true);
}

// 返回提示信息
void MainWindow::showDS18Msg(QString msg, int status)
{
    if(status == 1)             // 一号板已连接
    {
        ui->ds18No1linklabel->setText("已连接");
    }
    else if(status == -1)       // 一号板已断开
    {
        ui->ds18No1linklabel->setText("连接断开");
    }
    else if(status == 2)
    {
        ui->ds18No2linklabel->setText("已连接");
    }
    else if(status == -2)
    {
        ui->ds18No2linklabel->setText("连接断开");
    }
}

// 显示全部数据
void MainWindow::ds18SeeAll()
{

}

// 关闭此线程
void MainWindow::on_ds18dislink_pushButton_clicked()
{
    emit closeDs18Sensors();
    ui->ds18link_pushButton->setEnabled(true);
    ui->ds18dislink_pushButton->setEnabled(true);
}

/**********************************************************************************************

                                            3.环境温度部分

***********************************************************************************************/
// 监听
void MainWindow::on_envlinkpushButton_clicked()
{
    QString nowTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    envSamplePath = samplePath+"/环境温度("+nowTime+")";
    if(lwfdir->exists(envSamplePath)) qDebug()<<"!wolf1";
    else
    {
        if(lwfdir->mkdir(envSamplePath)) qDebug()<<"wolf1";
    }

    envAllDataPath = envSamplePath+"/EDCH.csv";
    QString csvHeader = "时间,EDCH01-01,EDCH01-02,EDCH02-01,EDCH02-02";
    if(QFile::exists(envAllDataPath)) qDebug()<<"dragon3";
    else
    {
        if(writeFile(envAllDataPath,csvHeader))
        qDebug()<<"dragon3";
    }

    EnviThread *airEnv = new EnviThread(originalPath);
    connect(airEnv, &EnviThread::relayMsg2Ui,this,&MainWindow::showEnvMsg);
    connect(this,&MainWindow::closeEnvironment,airEnv,&EnviThread::forceThread2Quit);
    connect(this,&MainWindow::createNewDayFolder,airEnv,&EnviThread::newDayforYou);
    connect(airEnv, &EnviThread::finished, airEnv, &QObject::deleteLater);
    airEnv->start();
    ui->envlinkpushButton->setEnabled(false);
    ui->envdislinkpushButton->setEnabled(true);
}

// 断开
void MainWindow::on_envdislinkpushButton_clicked()
{
    emit closeEnvironment();
    ui->envlinkpushButton->setEnabled(true);
    ui->envdislinkpushButton->setEnabled(false);
}

void MainWindow::showEnvMsg(QString loveU, int loveMe)
{
    if(loveMe == 1)
    {
        ui->ds18Envlinklabel->setText("已连接");
    }
    else if(loveMe == -1)
    {
        ui->ds18Envlinklabel->setText("连接断开");
    }
}

/**********************************************************************************************

                                            4.数控机床部分

***********************************************************************************************/
// 点击"连接机床"
void MainWindow::on_cnclink_pushButton_clicked()
{
    QString nowTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    hncSamplePath = samplePath+"/CNC机床数据("+nowTime+")";
    if(lwfdir->exists(hncSamplePath)) qDebug()<<"数控机床抽样目录已存在";
    else
    {
        if(lwfdir->mkdir(hncSamplePath)) qDebug()<<"数控机床抽样目录创建成功";
    }

    hncAllDataPath = hncSamplePath+"/CNC数据值.csv";
    QString csvHeader = "时间,机床通道,X轴坐标,Y轴坐标,Z轴坐标,主轴坐标,进给速度,主轴速度,X轴功率,Y轴功率,Z轴功率,主轴功率,X轴负荷,Y轴负荷,Z轴负荷,主轴负荷,暂停状态";
    if(QFile::exists(hncAllDataPath)) qDebug()<<"dragon4";
    else
    {
        if(writeFile(hncAllDataPath,csvHeader))
        qDebug()<<"dragon4";
    }

    Hnc848System *hnc848c = new Hnc848System(originalPath); // 将每日数据集路径送入对象
    connect(hnc848c, &Hnc848System::sendMsg, this, &MainWindow::showCNCMsg);
    connect(hnc848c,&Hnc848System::sendPara,this,&MainWindow::showComp);
    connect(this,&MainWindow::createNewDayFolder,hnc848c,&Hnc848System::niceNewDay);
    connect(this,&MainWindow::closeHncSystem,hnc848c,&Hnc848System::forceThreadtoQuit);
    connect(hnc848c, &Hnc848System::finished, hnc848c, &QObject::deleteLater);
    hnc848c->start(); // 启动数控系统子线程
}

//点击"断开机床"
void MainWindow::on_cncdislink_pushButton_clicked()
{
    emit closeHncSystem();
}

//返回对数控系统页面的操作提示信息
void MainWindow::showCNCMsg(QString msg, bool result)
{
    if(result == true)   // 连接成功
    {
        ui->cnclink_pushButton->setEnabled(false);
        ui->cncdislink_pushButton->setEnabled(true);
        ui->cnclink_label_2->setText("已连接\r\n数控机床");
        ui->cnclink_label_2->setStyleSheet("color:blue");
    }
    else                    // 连接失败
    {
        ui->cnclink_pushButton->setEnabled(true);
        ui->cncdislink_pushButton->setEnabled(false);
        ui->cnclink_label_2->setText("未连接\r\n数控机床");
        ui->cnclink_label_2->setStyleSheet("color:red");
    }
}

//  显示补偿进行状态
void MainWindow::showComp(short _105, short _106, short _107, unsigned int c1, unsigned int c2, unsigned int c3)
{
    ui->comp_textBrowser->clear();
    if(_105 == 0)
    {
        ui->comp_textBrowser->append("X105写入成功，写入值是"+QString::number(c1));
    }
    else
    {
        ui->comp_textBrowser->append("X105写入失败");
    }
    if(_106 == 0)
    {
        ui->comp_textBrowser->append("X106写入成功，写入值是"+QString::number(c2));
    }
    else
    {
        ui->comp_textBrowser->append("X106写入失败");
    }
    if(_107 == 0)
    {
        ui->comp_textBrowser->append("X107写入成功，写入值是"+QString::number(c3));
    }
    else
    {
        ui->comp_textBrowser->append("X107写入失败");
    }
}

/**********************************************************************************************

                                            5.激光位移传感器部分

***********************************************************************************************/
// 点击连接激光位移传感器之后
void MainWindow::on_linkccd_pushButton_clicked()
{
    QString nowTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    laserSamplePath = samplePath+"/CCD位移数据("+nowTime+")";
    if(lwfdir->exists(laserSamplePath)) qDebug()<<"!wolf5";
    else
    {
        if(lwfdir->mkdir(laserSamplePath)) qDebug()<<"wolf5";
    }

    laserAllDataPath = laserSamplePath+"/CCD数据值.csv";
    QString csvHeader = "时间,X轴位移,Y轴位移,Z轴位移";
    if(QFile::exists(laserAllDataPath)) qDebug()<<"dragon5";
    else
    {
        if(writeFile(laserAllDataPath,csvHeader))
        qDebug()<<"dragon5";
    }

    LaserDisplaceSensor *ccdSensor = new LaserDisplaceSensor(originalPath);
    connect(this,&MainWindow::closeLaserSensors,ccdSensor,&LaserDisplaceSensor::forceThread2Quit);
    connect(ccdSensor, &LaserDisplaceSensor::sendMsg,this,&MainWindow::ccdUiOperation);
    connect(this,&MainWindow::createNewDayFolder,ccdSensor,&LaserDisplaceSensor::niceNewDay);
    connect(ccdSensor, &LaserDisplaceSensor::finished, ccdSensor, &QObject::deleteLater);
    ccdSensor->start();
    ui->linkccd_pushButton->setEnabled(false);
    ui->closeccd_pushButton->setEnabled(false);
}

// 点击位移传感器示数归零之后
void MainWindow::on_zeroccd_pushButton_clicked()
{
    time2ClearDispalcement = true;
}

// 显示位移传感器测量结果
void MainWindow::showCCDResults(QString *yt)
{
    ui->x_lcdNumber->setText(yt[0]);
    ui->y_lcdNumber->setText(yt[1]);
    ui->z_lcdNumber->setText(yt[2]);
}

// 关闭位移传感器
void MainWindow::on_closeccd_pushButton_clicked()
{
    emit closeLaserSensors();
    ui->linkccd_pushButton->setEnabled(true);
}

// 显示返回信息
void MainWindow::ccdUiOperation(QString joffery)
{
    if(joffery == "连接成功")
    {
        ui->linkccd_pushButton->setEnabled(false);
        ui->closeccd_pushButton->setEnabled(true);
    }
    if(joffery == "连接失败")
    {
        ui->linkccd_pushButton->setEnabled(true);
        ui->closeccd_pushButton->setEnabled(false);
    }
}

/**********************************************************************************************

                                                6.云服务平台部分

***********************************************************************************************/
// 点击连接
void MainWindow::on_lincloud_pushButton_clicked()
{
    CloudTcpThread *cloudThread = new CloudTcpThread();
    cloudThread->start();
    connect(cloudThread,&CloudTcpThread::passCloudInfo,this,&MainWindow::showCloudInfo);
    connect(this,&MainWindow::closeCloudSocket,cloudThread,&CloudTcpThread::closeThread);
    connect(cloudThread,&CloudTcpThread::finished,cloudThread,&CloudTcpThread::deleteLater);
    ui->lincloud_pushButton->setEnabled(false);
    ui->dislinkcloud_pushButton->setEnabled(true);
}

// 显示
void MainWindow::showCloudInfo(QString tully,int blackfish)
{
    ui->cloud_textBrowser->append(tully);
}

//断开
void MainWindow::on_dislinkcloud_pushButton_clicked()
{
    emit closeCloudSocket();
    ui->lincloud_pushButton->setEnabled(true);
    ui->dislinkcloud_pushButton->setEnabled(false);
}

/**********************************************************************************************

                                                7.热误差补偿部分

***********************************************************************************************/
//开始补偿
void MainWindow::on_startcomp_pushButton_clicked()
{
    ui->comp_textBrowser->clear();
    if(!cncWorkingStatus)
    {
        ui->comp_textBrowser->append("请连接数控系统");
        return;
    }
    if(!ds18WorkingStatus)
    {
        ui->comp_textBrowser->append("请连接电类温度传感器");
        return;
    }
//    if(!fbgWorkingStatus)
//    {
//        ui->comp_textBrowser->append("请连接FBG解调仪");
//        return;
//    }
    if(cncWorkingStatus && ds18WorkingStatus)
    {
        ThermalErrorCompensation *reduceError = new ThermalErrorCompensation(originalPath);
        reduceError->start();
        connect(reduceError,&ThermalErrorCompensation::replyPredictionResult,
                this,&MainWindow::showPreResult);
        connect(reduceError,&ThermalErrorCompensation::replyAcutalCompensation,
                this,&MainWindow::showCompResult);
        connect(this,&MainWindow::closeCompensation,reduceError,&ThermalErrorCompensation::forceThread2Quit);
        connect(this,&MainWindow::createNewDayFolder,reduceError,&ThermalErrorCompensation::niceNewDay);
        connect(reduceError,&ThermalErrorCompensation::finished,
                reduceError,&ThermalErrorCompensation::deleteLater);
        ui->startcomp_pushButton->setEnabled(false);
    }
}

//关闭补偿
void MainWindow::on_closecomp_pushButton_clicked()
{
    emit closeCompensation();
    ui->startcomp_pushButton->setEnabled(true);
}

//清空显示
void MainWindow::clearCompBrowser()
{
    ui->comp_textBrowser->clear();
}

//显示预测或补偿结果
void MainWindow::showPreResult(double arya)
{
    ui->comp_textBrowser->append("预测结果："+QString::number(1000*arya,10,4)+"um");
}

void MainWindow::showCompResult(int robert)
{
    ui->comp_textBrowser->append("实际补偿："+QString::number(robert,10));
}

