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
    statusBar()->setSizeGripEnabled(true); //设置是否显示右边的大小控制点
    statusBar()->addWidget(statusbarCNCLabel);
    statusBar()->addWidget(statusbarDs18Label);
    statusBar()->addWidget(statusbarFBGLabel);
    statusBar()->addWidget(statusbarCCDLabel);

    // 选项卡“首页”初始化配置
    ui->FBGclose_pushButton->setEnabled(false);
    ui->ds18dislink_pushButton->setEnabled(false);
    ui->envdislinkpushButton->setEnabled(false);
    ui->cncdislink_pushButton->setEnabled(false);
    ui->closeccd_pushButton->setEnabled(false);
    ui->dislinkcloud_pushButton->setEnabled(false);

    QPalette wordColor; QFont wordFont;
    wordColor.setColor(QPalette::WindowText,Qt::white);
    wordFont.setPointSize(16); wordFont.setBold(true); wordFont.setItalic(true);
    ui->fbglinklabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->fbglinklabel->setFont(wordFont);
    ui->fbglinklabel->setPalette(wordColor);

    ui->ds18No1linklabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->ds18No1linklabel->setFont(wordFont);
    ui->ds18No1linklabel->setPalette(wordColor);

    ui->ds18No2linklabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->ds18No2linklabel->setFont(wordFont);
    ui->ds18No2linklabel->setPalette(wordColor);

    ui->ds18Envlinklabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->ds18Envlinklabel->setFont(wordFont);
    ui->ds18Envlinklabel->setPalette(wordColor);

    ui->hnclink_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->hnclink_label->setFont(wordFont);
    ui->hnclink_label->setPalette(wordColor);

    ui->ccdlinklabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->ccdlinklabel->setFont(wordFont);
    ui->ccdlinklabel->setPalette(wordColor);

    ui->cloudlinklabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->cloudlinklabel->setFont(wordFont);
    ui->cloudlinklabel->setPalette(wordColor);

    // 1.选项卡“FBG传感器”页面初始化配置
    fbgChart = new QChart();     //  fbg传感器关键点温度变化折线图
    fbgChart->legend()->setAlignment(Qt::AlignRight);          // 图例放在右方
    fbgChart->setAnimationOptions(QChart::GridAxisAnimations); // 图形伸缩时有动画效果
    fbgChart->setTheme(QChart::ChartThemeDark);
    fbgChart->setTitle("FBG传感器关键点展示");
    fbgChart->setTitleFont(QFont("Timers",12,QFont::Bold));

    QPen lineType;   // 画笔，可设置线条颜色和粗细，此变量重复使用
    lineType.setWidth(3);
    fbgSeriesCh1601 = new QSplineSeries(fbgChart);
    lineType.setColor(Qt::white);
    fbgSeriesCh1601->setPen(lineType);
    fbgSeriesCh1601->setUseOpenGL(true);
    fbgSeriesCh1601->setName("CH16-1");

    fbgSeriesCh1701 = new QSplineSeries(fbgChart);
    lineType.setColor(Qt::cyan);
    fbgSeriesCh1701->setPen(lineType);
    fbgSeriesCh1701->setUseOpenGL(true);
    fbgSeriesCh1701->setName("CH17-1");

    fbgSeriesCh1801 = new QSplineSeries(fbgChart);
    lineType.setColor(Qt::red);
    fbgSeriesCh1801->setPen(lineType);
    fbgSeriesCh1801->setUseOpenGL(true);
    fbgSeriesCh1801->setName("CH18-1");

    fbgXaxis = new QValueAxis();
    fbgXaxis->setTickCount(10);
    fbgXaxis->setLabelFormat("g");
    fbgXaxis->setLabelsAngle(20);
    fbgXaxis->setTitleFont(QFont("Timers",10,QFont::Bold));
    fbgXaxis->setTitleText("时间轴还没有研究清楚");

    fbgYaxis = new QValueAxis();
    fbgYaxis->setTickCount(10);
    fbgYaxis->setLabelFormat("%g");
    fbgYaxis->setMinorTickCount(5);
    fbgYaxis->setRange(1520,1580);
    fbgYaxis->setTitleText("Wave length(um)");
    fbgYaxis->setTitleFont(QFont("Timers",10,QFont::Bold));

    fbgChart->addSeries(fbgSeriesCh1601);                   // 添加这一条线到图中
    fbgChart->addSeries(fbgSeriesCh1701);
    fbgChart->addSeries(fbgSeriesCh1801);
    fbgChart->createDefaultAxes();
    fbgChart->setAxisX(fbgXaxis, fbgSeriesCh1601);
    fbgChart->setAxisY(fbgYaxis, fbgSeriesCh1601);
    fbgChart->setAxisX(fbgXaxis, fbgSeriesCh1701);
    fbgChart->setAxisY(fbgYaxis, fbgSeriesCh1701);
    fbgChart->setAxisX(fbgXaxis, fbgSeriesCh1801);
    fbgChart->setAxisY(fbgYaxis, fbgSeriesCh1801);

    maxFbgSize=50;
    ui->fbgchartview->setRenderHint(QPainter::Antialiasing); // 抗锯齿
    ui->fbgchartview->setChart(fbgChart);
    connect(ui->FBGseeallpushButton,&QPushButton::clicked,this,&MainWindow::fbgSeeAll); // 点击查看全部可以看到全部数据

    // 2-3.选项卡“电类温度传感器”页面初始化配置
    ds18No1Chart = new QChart(); // (1)电类传感器一号板第七通道温度变化曲线图
    ds18No1Chart->legend()->setAlignment(Qt::AlignRight);           // 图例放在右方
    ds18No1Chart->setAnimationOptions(QChart::GridAxisAnimations);  // 图形伸缩时有动画效果
    ds18No1Chart->setTheme(QChart::ChartThemeBrownSand);
    ds18No1Chart->setTitle("电类传感器第1~8通道关键点温度变化展示");
    ds18No1Chart->setTitleFont(QFont("Timers",8,QFont::Bold));

    ds18seriesCh0701 = new QSplineSeries(ds18No1Chart);
    ds18seriesCh0701->setUseOpenGL(true);
    ds18seriesCh0701->setName("CH07-01");

    ds18seriesCh0702 = new QSplineSeries(ds18No1Chart);
    ds18seriesCh0702->setUseOpenGL(true);
    ds18seriesCh0702->setName("CH07-02");

    ds18seriesCh0703 = new QSplineSeries(ds18No1Chart);
    ds18seriesCh0703->setUseOpenGL(true);
    ds18seriesCh0703->setName("CH07-03");

    ds18seriesCh0704 = new QSplineSeries(ds18No1Chart);
    ds18seriesCh0704->setUseOpenGL(true);
    ds18seriesCh0704->setName("CH07-04");

    ds18No1Xaxis = new QValueAxis();
    ds18No1Xaxis->setTickCount(10);
    ds18No1Xaxis->setLabelFormat("g");
    ds18No1Xaxis->setLabelsAngle(20);
    ds18No1Xaxis->setRange(0,100);
    ds18No1Xaxis->setTitleFont(QFont("Timers",8,QFont::Bold));
    ds18No1Xaxis->setTitleText("时间轴还没有研究清楚");

    ds18No1Yaxis = new QValueAxis();
    ds18No1Yaxis->setTickCount(10);
    ds18No1Yaxis->setLabelFormat("%g");
    ds18No1Yaxis->setMinorTickCount(5);
    ds18No1Yaxis->setRange(-5,40);
    ds18No1Yaxis->setTitleText("摄氏温度(℃)");
    ds18No1Yaxis->setTitleFont(QFont("Timers",8,QFont::Bold));

    ds18No1Chart->addSeries(ds18seriesCh0701); // 添加4条线到图中
    ds18No1Chart->addSeries(ds18seriesCh0702);
    ds18No1Chart->addSeries(ds18seriesCh0703);
    ds18No1Chart->addSeries(ds18seriesCh0704);
    ds18No1Chart->createDefaultAxes();
    ds18No1Chart->setAxisX(ds18No1Xaxis, ds18seriesCh0701);
    ds18No1Chart->setAxisY(ds18No1Yaxis, ds18seriesCh0701);
    ds18No1Chart->setAxisX(ds18No1Xaxis, ds18seriesCh0702);
    ds18No1Chart->setAxisY(ds18No1Yaxis, ds18seriesCh0702);
    ds18No1Chart->setAxisX(ds18No1Xaxis, ds18seriesCh0703);
    ds18No1Chart->setAxisY(ds18No1Yaxis, ds18seriesCh0703);
    ds18No1Chart->setAxisX(ds18No1Xaxis, ds18seriesCh0704);
    ds18No1Chart->setAxisY(ds18No1Yaxis, ds18seriesCh0704);
    maxds18No1Size = 50;
    ui->ds18no1chartview->setRenderHint(QPainter::Antialiasing);
    ui->ds18no1chartview->setChart(ds18No1Chart);

    ds18No2Chart = new QChart(); // (2)电类传感器二号板关键点温度变化曲线图
    ds18No2Chart->legend()->setAlignment(Qt::AlignRight);
    ds18No2Chart->setAnimationOptions(QChart::GridAxisAnimations);
    ds18No2Chart->setTheme(QChart::ChartThemeBrownSand);
    ds18No2Chart->setTitle("电类传感器第9~16通道关键点温度变化展示");
    ds18No2Chart->setTitleFont(QFont("Timers",8,QFont::Bold));

    ds18seriesCh0901 = new QSplineSeries(ds18No1Chart);
    ds18seriesCh0901->setUseOpenGL(true);
    ds18seriesCh0901->setName("CH09-01");

    ds18seriesCh1101 = new QSplineSeries(ds18No1Chart);
    ds18seriesCh1101->setUseOpenGL(true);
    ds18seriesCh1101->setName("CH11-01");

    ds18seriesCh1301 = new QSplineSeries(ds18No1Chart);
    ds18seriesCh1301->setUseOpenGL(true);
    ds18seriesCh1301->setName("CH13-01");

    ds18seriesCh1501 = new QSplineSeries(ds18No1Chart);
    ds18seriesCh1501->setUseOpenGL(true);
    ds18seriesCh1501->setName("CH15-01");

    ds18No2Xaxis = new QValueAxis();
    ds18No2Xaxis->setTickCount(10);
    ds18No2Xaxis->setLabelFormat("g");
    ds18No2Xaxis->setLabelsAngle(20);
    ds18No2Xaxis->setRange(0,100);
    ds18No2Xaxis->setTitleFont(QFont("Timers",8,QFont::Bold));
    ds18No2Xaxis->setTitleText("时间轴还没有研究清楚");

    ds18No2Yaxis = new QValueAxis();
    ds18No2Yaxis->setTickCount(10);
    ds18No2Yaxis->setLabelFormat("%g");
    ds18No2Yaxis->setMinorTickCount(5);
    ds18No2Yaxis->setRange(-5,40);
    ds18No2Yaxis->setTitleText("摄氏温度(℃)");
    ds18No2Yaxis->setTitleFont(QFont("Timers",8,QFont::Bold));

    ds18No2Chart->addSeries(ds18seriesCh0901); // 添加4条线到图中
    ds18No2Chart->addSeries(ds18seriesCh1101);
    ds18No2Chart->addSeries(ds18seriesCh1301);
    ds18No2Chart->addSeries(ds18seriesCh1501);
    ds18No2Chart->createDefaultAxes();
    ds18No2Chart->setAxisX(ds18No2Xaxis, ds18seriesCh0901);
    ds18No2Chart->setAxisY(ds18No2Yaxis, ds18seriesCh0901);
    ds18No2Chart->setAxisX(ds18No2Xaxis, ds18seriesCh1101);
    ds18No2Chart->setAxisY(ds18No2Yaxis, ds18seriesCh1101);
    ds18No2Chart->setAxisX(ds18No2Xaxis, ds18seriesCh1301);
    ds18No2Chart->setAxisY(ds18No2Yaxis, ds18seriesCh1301);
    ds18No2Chart->setAxisX(ds18No2Xaxis, ds18seriesCh1501);
    ds18No2Chart->setAxisY(ds18No2Yaxis, ds18seriesCh1501);
    maxds18No2Size = 50;
    ui->ds18no2chartview->setRenderHint(QPainter::Antialiasing);
    ui->ds18no2chartview->setChart(ds18No2Chart);

    envBarChart = new QChart(); // (3) 环境温度柱状图
    envBarChart->legend()->setAlignment(Qt::AlignRight);
    envBarChart->setAnimationOptions(QChart::GridAxisAnimations);
    envBarChart->setTheme(QChart::ChartThemeBrownSand);
    envBarChart->setTitle("环境温度柱状图对比展示");
    envBarChart->setTitleFont(QFont("Timers",8,QFont::Bold));

    frontSet = new QBarSet("前方");
    backSet  = new QBarSet("后方");
    rightSet = new QBarSet("右方");
    leftSet  = new QBarSet("左方");

    *frontSet << 7.00;
    *backSet << 8.52;
    *rightSet << 10.6;
    *leftSet << 9.8;
    envBarSeries = new QBarSeries(envBarChart);
    envBarSeries->append(frontSet);
    envBarSeries->append(backSet);
    envBarSeries->append(rightSet);
    envBarSeries->append(leftSet);

    QStringList categories;
    categories << "当前时刻";
    envXaxis = new QBarCategoryAxis();
    envXaxis->append(categories);

    envYaxis = new QValueAxis();
    envYaxis->setTickCount(10);
    envYaxis->setRange(0,40);

    envBarChart->addSeries(envBarSeries);
    envBarChart->createDefaultAxes();
    envBarChart->setAxisX(envXaxis,envBarSeries);
    envBarChart->setAxisY(envYaxis,envBarSeries);
    ui->envchartview->setRenderHint(QPainter::Antialiasing);
    ui->envchartview->setChart(envBarChart);

    connect(ui->ds18seeallpushButton,&QPushButton::clicked,this,&MainWindow::ds18SeeAll);

    // 3.选项卡“数控系统信息”页面初始化配置

    // 4.选项卡“位移传感器”页面初始化配置
    ui->x_lcdNumber->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->x_lcdNumber->setFont(QFont("Timers",20,QFont::ExtraBold|QFont::StyleItalic));
    ui->y_lcdNumber->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->y_lcdNumber->setFont(QFont("Timers",20,QFont::Bold));
    ui->z_lcdNumber->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->z_lcdNumber->setFont(QFont("Timers",20,QFont::Bold));

    laserSensorChart = new QChart();
    laserSensorChart->setTitle("位移传感器三轴变化趋势图");
    laserSensorChart->legend()->setAlignment(Qt::AlignRight);
    laserSensorChart->setAnimationOptions(QChart::GridAxisAnimations);
    laserSensorChart->setTheme(QChart::ChartThemeBlueCerulean);
    laserSensorChart->setTitleFont(QFont("Timers",12,QFont::Bold));

    laserSensorX = new QSplineSeries(laserSensorChart);
    lineType.setColor(Qt::red);
    laserSensorX->setPen(lineType);
    laserSensorX->setUseOpenGL(true);
    laserSensorX->setName("X轴");
    laserSensorY = new QSplineSeries(laserSensorChart);
    lineType.setColor(Qt::cyan);
    laserSensorY->setPen(lineType);
    laserSensorY->setUseOpenGL(true);
    laserSensorY->setName("Y轴");
    laserSensorZ = new QSplineSeries(laserSensorChart);
    lineType.setColor(Qt::black);
    laserSensorZ->setPen(lineType);
    laserSensorZ->setUseOpenGL(true);
    laserSensorZ->setName("Z轴");

    laserSensorXaxis = new QValueAxis();
    laserSensorXaxis->setTickCount(10);
    laserSensorXaxis->setMinorTickCount(3);
    laserSensorXaxis->setLabelFormat("g");
    laserSensorXaxis->setRange(0,100);
    laserSensorXaxis->setTitleFont(QFont("Timers",10,QFont::Bold));
    laserSensorXaxis->setTitleText("横轴原本设想应该是时间，但是时间轴没有处理好，现在横轴代表什么我也不知道");

    laserSensorYaxis = new QValueAxis();
    laserSensorYaxis->setTickCount(10);
    laserSensorYaxis->setLabelFormat("%g");
    laserSensorYaxis->setMinorTickCount(3);
    laserSensorYaxis->setRange(-0.05,0.05);
    laserSensorYaxis->setTitleText("位移(mm)");
    laserSensorYaxis->setTitleFont(QFont("Timers",10,QFont::Bold));

    laserSensorChart->addSeries(laserSensorX);
    laserSensorChart->addSeries(laserSensorY);
    laserSensorChart->addSeries(laserSensorZ);
    laserSensorChart->createDefaultAxes();
    laserSensorChart->setAxisX(laserSensorXaxis, laserSensorZ);
    laserSensorChart->setAxisY(laserSensorYaxis, laserSensorZ);
    laserSensorChart->setAxisX(laserSensorXaxis, laserSensorX);
    laserSensorChart->setAxisY(laserSensorYaxis, laserSensorX);
    maxLaserSize = 50;
    ui->laserchartview->setRenderHint(QPainter::Antialiasing); // 抗锯齿
    ui->laserchartview->setChart(laserSensorChart);

    // 选项卡“云服务平台”页面初始化配置

    // 选项卡“热误差补偿”页面初始化配置
    connect(ui->clearcomp_pushButton,&QPushButton::clicked,this,&MainWindow::clearCompBrowser);

/*-------------------------------创建数据存储文件夹-------------------------------------*/
    currentday = QDateTime::currentDateTime().toString("yyyyMMdd");
    currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    lwfdir = new QDir();
    rootPath = QDir::currentPath()+"/数据大家族";
    qDebug()<<rootPath;
    if(!lwfdir->exists(rootPath))
    {
        lwfdir->mkdir(rootPath);
    }

    EverydayPath = rootPath+"/数据家族的日常"+"("+currentDate+")";
    if(!lwfdir->exists(EverydayPath))
    {
        lwfdir->mkdir(EverydayPath);
    }

    originalPath = EverydayPath+"/数据家族全家福"+"("+currentDate+")";
    if(!lwfdir->exists(originalPath))
    {
        lwfdir->mkdir(originalPath);
    }

    samplePath = EverydayPath+"/数据家族小可爱"+"("+currentDate+")";
    if(!lwfdir->exists(samplePath))
    {
        lwfdir->mkdir(samplePath);
    }
/*-------------------------------全局变量初始化----------------------------------*/
    for(int gyn=0; gyn<FBG_Channel_Max; gyn++)
    {
        for(int jn=0; jn<FBG_Index_Max; jn++)
        {
            FBG_ALL[gyn][jn] = "255";
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

    ccdInfo[0] = "0";
    ccdInfo[1] = "0";
    ccdInfo[2] = "0";

/*-----------------------------主线程成员变量初始化-----------------------------------*/
    taskTimeCnt =0;
    globalLock = new QMutex();
    kingTimer = new QTimer(this);
    connect(kingTimer,&QTimer::timeout, this,MainWindow::timeisup);
    kingTimer->setTimerType(Qt::PreciseTimer);
    kingTimer->setInterval(1000); // 每1s中断一次
    kingTimer->start();

    plotCnt = 0;
    plotTimer = new MMTimer(1000,this);
    connect(plotTimer,&MMTimer::timeout,this,&MainWindow::plotTimePoll);
    plotTimer->start();
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

    // 以下语句目的是每秒刷新位移传感器的显示示数
    bool convertion;
    ccdInfo[0].toDouble(&convertion);
    if(convertion)
    {
        ui->x_lcdNumber->setStyleSheet("color:green");
    }
    else
    {
        ui->x_lcdNumber->setStyleSheet("color:red");
    }
    ui->x_lcdNumber->setText(ccdInfo[0]);

    ccdInfo[1].toDouble(&convertion);
    if(convertion)
    {
        ui->y_lcdNumber->setStyleSheet("color:green");
    }
    else
    {
        ui->y_lcdNumber->setStyleSheet("color:red");
    }
    ui->y_lcdNumber->setText(ccdInfo[1]);

    ccdInfo[2].toDouble(&convertion);
    if(convertion)
    {
        ui->z_lcdNumber->setStyleSheet("color:green");
    }
    else
    {
        ui->z_lcdNumber->setStyleSheet("color:red");
    }
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

// 图形动态更新定时器
void MainWindow::plotTimePoll()
{    
    plotCnt++;
    switch (plotCnt)
    {
        case 1:
            if(fbgWorkingStatus) rePlotFbg(); break;
        case 2:
            if(ds18WorkingStatus) rePlotDs18No1(); break;
        case 3:
            if(ds18No2WorkStatus) rePlotDs18No2(); break;
        case 4:
            if(envWorkingStatus) rePlotEnvironment();
            if(cncWorkingStatus) rePlotHnc();
            break;
        case 5:
            if(laserWorkingStatus) rePlotLaserSensors(); plotCnt=0; break;
        default: break;
    }
}

// 1.重新绘制光纤光栅传感器图表
void MainWindow::rePlotFbg()
{
    fbg1601Data << FBG_ALL[15][0].toDouble();    // 将当前最新值添加到list末尾
    while (fbg1601Data.size() > maxFbgSize)      // 如果超过最大容量，删除第一个
    {
        fbg1601Data.removeFirst();
    }

    fbg1701Data << FBG_ALL[16][0].toDouble();
    while (fbg1701Data.size() > maxFbgSize)
    {
        fbg1701Data.removeFirst();
    }

    fbg1801Data << FBG_ALL[17][0].toDouble();
    while (fbg1801Data.size() > maxFbgSize)
    {
        fbg1801Data.removeFirst();
    }

    if (isVisible()) // 界面被隐藏后就没有必要绘制数据的曲线了
    {
        int dx = 100 / (maxFbgSize-1);
        int less = maxFbgSize - fbg1601Data.size();
        fbgSeriesCh1601->clear();
        for (int i = 0; i < fbg1601Data.size(); ++i)
        {
            fbgSeriesCh1601->append(less*dx+i*dx, fbg1601Data.at(i));
        }

        less = maxFbgSize - fbg1701Data.size();
        fbgSeriesCh1701->clear();
        for (int i = 0; i < fbg1701Data.size(); ++i)
        {
            fbgSeriesCh1701->append(less*dx+i*dx, fbg1701Data.at(i));
        }

        less = maxFbgSize - fbg1801Data.size();
        fbgSeriesCh1801->clear();
        for (int i = 0; i < fbg1801Data.size(); ++i)
        {
            fbgSeriesCh1801->append(less*dx+i*dx, fbg1801Data.at(i));
        }
    }
}

// 2.1. 重新绘制电类传感器一号板图表
void MainWindow::rePlotDs18No1()
{
    ds180701Data << DS18B20_ALL_Node[6][0].temperature.toDouble(); // 第七通道第1号点
    while (ds180701Data.size() > maxds18No1Size)
    {
        ds180701Data.removeFirst();
    }

    ds180702Data << DS18B20_ALL_Node[6][1].temperature.toDouble(); // 第七通道第2号点
    while (ds180702Data.size() > maxds18No1Size)
    {
        ds180702Data.removeFirst();
    }

    ds180703Data << DS18B20_ALL_Node[6][2].temperature.toDouble(); // 第七通道第3号点
    while (ds180703Data.size() > maxds18No1Size)
    {
        ds180703Data.removeFirst();
    }

    ds180704Data << DS18B20_ALL_Node[6][4].temperature.toDouble(); // 第七通道第4号点
    while (ds180704Data.size() > maxds18No1Size)
    {
        ds180704Data.removeFirst();
    }

    if (isVisible()) // 界面被隐藏后就没有必要绘制数据的曲线了
    {
        int dx = 100 / (maxds18No1Size-1);
        int less = maxds18No1Size - ds180701Data.size();
        ds18seriesCh0701->clear();
        for (int i = 0; i < ds180701Data.size(); ++i)
        {
            ds18seriesCh0701->append(less*dx+i*dx, ds180701Data.at(i));
        }

        less = maxds18No1Size - ds180702Data.size();
        ds18seriesCh0702->clear();
        for (int i = 0; i < ds180702Data.size(); ++i)
        {
            ds18seriesCh0702->append(less*dx+i*dx, ds180702Data.at(i));
        }

        less = maxds18No1Size - ds180703Data.size();
        ds18seriesCh0703->clear();
        for (int i = 0; i < ds180703Data.size(); ++i)
        {
            ds18seriesCh0703->append(less*dx+i*dx, ds180703Data.at(i));
        }

        less = maxds18No1Size - ds180704Data.size();
        ds18seriesCh0704->clear();
        for (int i = 0; i < ds180704Data.size(); ++i)
        {
            ds18seriesCh0704->append(less*dx+i*dx, ds180704Data.at(i));
        }
    }
}

// 2.2. 重新绘制电类传感器二号板图表
void MainWindow::rePlotDs18No2()
{
    ds180901Data << DS18B20_ADD_Node[0][0].temperature.toDouble(); // 第9通道第1号点
    while (ds180901Data.size() > maxds18No2Size)
    {
        ds180901Data.removeFirst();
    }

    ds181101Data << DS18B20_ADD_Node[2][0].temperature.toDouble(); // 第11通道第1号点
    while (ds181101Data.size() > maxds18No2Size)
    {
        ds181101Data.removeFirst();
    }

    ds181301Data << DS18B20_ADD_Node[4][0].temperature.toDouble(); // 第13通道第1号点
    while (ds181301Data.size() > maxds18No2Size)
    {
        ds181301Data.removeFirst();
    }

    ds181501Data << DS18B20_ADD_Node[6][0].temperature.toDouble(); // 第15通道第1号点
    while (ds181501Data.size() > maxds18No2Size)
    {
        ds181501Data.removeFirst();
    }

    if (isVisible()) // 界面被隐藏后就没有必要绘制数据的曲线了
    {
        int dx = 100 / (maxds18No2Size-1);
        int less = maxds18No2Size - ds180901Data.size();
        ds18seriesCh0901->clear();
        for (int i = 0; i < ds180901Data.size(); ++i)
        {
            ds18seriesCh0901->append(less*dx+i*dx, ds180901Data.at(i));
        }

        less = maxds18No2Size - ds181101Data.size();
        ds18seriesCh1101->clear();
        for (int i = 0; i < ds181101Data.size(); ++i)
        {
            ds18seriesCh1101->append(less*dx+i*dx, ds181101Data.at(i));
        }

        less = maxds18No2Size - ds181301Data.size();
        ds18seriesCh1301->clear();
        for (int i = 0; i < ds181301Data.size(); ++i)
        {
            ds18seriesCh1301->append(less*dx+i*dx, ds181301Data.at(i));
        }

        less = maxds18No2Size - ds181501Data.size();
        ds18seriesCh1501->clear();
        for (int i = 0; i < ds181501Data.size(); ++i)
        {
            ds18seriesCh1501->append(less*dx+i*dx, ds181501Data.at(i));
        }
    }
}

// 3.重新绘制环境温度图表
void MainWindow::rePlotEnvironment()
{
    frontSet->replace(0,ENV_ALL_Node[0].temperature.toDouble());
    backSet->replace(0,ENV_ALL_Node[1].temperature.toDouble());
    rightSet->replace(0,ENV_ALL_Node[2].temperature.toDouble());
    leftSet->replace(0,ENV_ALL_Node[3].temperature.toDouble());

    qDebug()<<"lwf";
    envBarSeries->append(frontSet);
    envBarSeries->append(backSet);
    envBarSeries->append(rightSet);
    envBarSeries->append(leftSet);
}

// 4.重新绘制数控信息图表
void MainWindow::rePlotHnc()
{
    qDebug()<<"你让我画啥";
}

// 5.重新绘制激光位移传感器图表
void MainWindow::rePlotLaserSensors()
{
    laserXData << ccdInfo[0].toDouble();
    while (laserXData.size() > maxLaserSize)
    {
        laserXData.removeFirst();
    }

    laserZData << ccdInfo[1].toDouble();
    while (laserZData.size() > maxLaserSize)
    {
        laserZData.removeFirst();
    }

    if (isVisible()) // 界面被隐藏后就没有必要绘制数据的曲线了
    {
        int dx = 100 / (maxLaserSize-1);
        int less = maxLaserSize - laserXData.size();
        laserSensorX->clear();
        for (int i = 0; i < laserXData.size(); ++i)
        {
            laserSensorX->append(less*dx+i*dx, laserXData.at(i));
        }

        laserSensorZ->clear();
        less = maxLaserSize - laserZData.size();
        for (int i = 0; i < laserZData.size(); ++i)
        {
            laserSensorZ->append(less*dx+i*dx, laserZData.at(i));
        }
    }
}
/**********************************************************************************************

                                          1.FBG传感器部分

***********************************************************************************************/
// 连接FBG解调仪
void MainWindow::on_FBGlink_pushButton_clicked()
{
    QString nowTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh：mm：ss");
    fbgSamplePath = samplePath+"/FBG波长数据("+nowTime+")";
    if(!lwfdir->exists(fbgSamplePath))
    {
        lwfdir->mkdir(fbgSamplePath);
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
    if(!QFile::exists(FbgAllDataPath))
    {
        writeFile(FbgAllDataPath,csvHeader);
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
    if(!QFile::exists(fbgAllStressPath))
    {
        writeFile(fbgAllStressPath,csvHeader);
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
    if(!QFile::exists(fbgAllTempPath))
    {
        writeFile(fbgAllTempPath,csvHeader);
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
    switch (tywin)
    {
        case -1: ui->fbglinklabel->setText("FBG线程已关闭");
            break;
        case 0:  ui->fbglinklabel->setText("FBG暂时断开");
            break;
        case 1:  ui->fbglinklabel->setText("FBG保持连接");
            break;
        default: break;
    }
}

// 点击按钮，查看fbg详细数据
void MainWindow::fbgSeeAll()
{
   fbgAllDataUi *iWantSeeAllFbg = new fbgAllDataUi(this);
   iWantSeeAllFbg->setWindowTitle("光纤光栅传感器全部数据展示");
   if(iWantSeeAllFbg->exec() == QDialog::Accepted) {}
   delete iWantSeeAllFbg;
}

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
    if(!lwfdir->exists(ds18SamplePath))
    {
        lwfdir->mkdir(ds18SamplePath);
    }
    if(!lwfdir->exists(ds18No1SamplePath))
    {
        lwfdir->mkdir(ds18No1SamplePath);
    }
    if(!lwfdir->exists(ds18No2SamplePath))
    {
        lwfdir->mkdir(ds18No2SamplePath);
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
    if(!QFile::exists(ds18AllDataPath))
    {
        writeFile(ds18AllDataPath,csvHeader);
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
    if(!QFile::exists(dsNo1DataPath))
    {
        writeFile(dsNo1DataPath,csvHeader);
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
    if(!QFile::exists(dsNo2DataPath))
    {
        writeFile(dsNo2DataPath,csvHeader);
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
        ui->ds18No1linklabel->setText("未连接");
    }
    else if(status == 2)
    {
        ui->ds18No2linklabel->setText("已连接");
    }
    else if(status == -2)
    {
        ui->ds18No2linklabel->setText("未连接");
    }
}

// 显示全部数据
void MainWindow::ds18SeeAll()
{
    Ds18SeeAllUi *iWant2SeeYou = new Ds18SeeAllUi(this);
    iWant2SeeYou->setWindowTitle("电类温度传感器全部数据展示");
    if(iWant2SeeYou->exec() == QDialog::Accepted) {}
    delete iWant2SeeYou;
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
    if(!lwfdir->exists(envSamplePath))
    {
        lwfdir->mkdir(envSamplePath);
    }

    envAllDataPath = envSamplePath+"/EDCH.csv";
    QString csvHeader = "时间,EDCH01-01,EDCH01-02,EDCH02-01,EDCH02-02";
    if(!QFile::exists(envAllDataPath))
    {
        writeFile(envAllDataPath,csvHeader);
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
        ui->ds18Envlinklabel->setText("未连接");
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
    if(!lwfdir->exists(hncSamplePath))
    {
        lwfdir->mkdir(hncSamplePath);
    }

    hncAllDataPath = hncSamplePath+"/CNC数据值.csv";
    QString csvHeader = "时间,机床通道,X轴坐标,Y轴坐标,Z轴坐标,主轴坐标,进给速度,主轴速度,X轴功率,Y轴功率,Z轴功率,主轴功率,X轴负荷,Y轴负荷,Z轴负荷,主轴负荷,暂停状态";
    if(!QFile::exists(hncAllDataPath))
    {
        writeFile(hncAllDataPath,csvHeader);
    }

    Hnc848System *hnc848c = new Hnc848System(originalPath); // 将每日数据集路径送入对象
    connect(hnc848c, &Hnc848System::sendMsg, this, &MainWindow::showCNCMsg);
    connect(hnc848c,&Hnc848System::sendPara,this,&MainWindow::showComp);
    connect(this,&MainWindow::createNewDayFolder,hnc848c,&Hnc848System::niceNewDay);
    connect(this,&MainWindow::closeHncSystem,hnc848c,&Hnc848System::forceThreadtoQuit);
    connect(hnc848c, &Hnc848System::finished, hnc848c, &QObject::deleteLater);
    hnc848c->start(); // 启动数控系统子线程
}

// 点击"断开机床"
void MainWindow::on_cncdislink_pushButton_clicked()
{
    emit closeHncSystem();
}

// 返回对数控系统页面的操作提示信息
void MainWindow::showCNCMsg(QString msg, bool result)
{
    if(result == true)   // 连接成功
    {
        ui->cnclink_pushButton->setEnabled(false);
        ui->cncdislink_pushButton->setEnabled(true);
        ui->hnclink_label->setText("已连接");
        ui->hnclink_label->setStyleSheet("color:green");
    }
    else                    // 连接失败
    {
        ui->cnclink_pushButton->setEnabled(true);
        ui->cncdislink_pushButton->setEnabled(false);
        ui->hnclink_label->setText("未连接");
        ui->hnclink_label->setStyleSheet("color:red");
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
    if(!lwfdir->exists(laserSamplePath))
    {
        lwfdir->mkdir(laserSamplePath);
    }

    laserAllDataPath = laserSamplePath+"/CCD数据值.csv";
    QString csvHeader = "时间,X轴位移,Y轴位移,Z轴位移";
    if(!QFile::exists(laserAllDataPath))
    {
        writeFile(laserAllDataPath,csvHeader);
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

// 关闭位移传感器
void MainWindow::on_closeccd_pushButton_clicked()
{
    emit closeLaserSensors();
}

// 显示返回信息
void MainWindow::ccdUiOperation(QString joffery,int tommen)
{
    switch (tommen)
    {
        case -1:    // 连接失败
        {
            ui->linkccd_pushButton->setEnabled(true);
            ui->closeccd_pushButton->setEnabled(false);
        }
            break;
        case  0:    // 用户手动断开连接
        {
            ui->linkccd_pushButton->setEnabled(true);
            ui->closeccd_pushButton->setEnabled(false);
            ui->ccdlinklabel->setText("未连接");
        }
            break;
        case  1:    // 连接成功
        {
            ui->linkccd_pushButton->setEnabled(false);
            ui->closeccd_pushButton->setEnabled(true);
            ui->ccdlinklabel->setText("已连接");
        }
            break;
        case  2:    // 异常情况
        {
        }
            break;
        default:    break;
    }
}

/**********************************************************************************************

                                                6.云服务平台部分

***********************************************************************************************/
// 点击连接
void MainWindow::on_lincloud_pushButton_clicked()
{
    CloudTcpThread *cloudThread = new CloudTcpThread();
    connect(cloudThread,&CloudTcpThread::passCloudInfo,this,&MainWindow::showCloudInfo);
    connect(this,&MainWindow::closeCloudSocket,cloudThread,&CloudTcpThread::closeThread);
    connect(cloudThread,&CloudTcpThread::finished,cloudThread,&CloudTcpThread::deleteLater);
    cloudThread->start();
    ui->lincloud_pushButton->setEnabled(false);
    ui->dislinkcloud_pushButton->setEnabled(true);
}

// 显示
void MainWindow::showCloudInfo(QString tully,int blackfish)
{
    switch (blackfish)
    {
        case -1:      // 连接断开
        {
            ui->cloudlinklabel->setText("与云端的连接断开");
        }
            break;
        case  0:      // 用户手动断开
        {
            ui->lincloud_pushButton->setEnabled(true);
            ui->dislinkcloud_pushButton->setEnabled(false);
            ui->cloudlinklabel->setText("未连接");
        }
            break;
        case  1:      // 连接成功
        {
            ui->cloudlinklabel->setText("已连接云端");
        }
            break;
        case  2:      // 本次连接尝试失败
        {
            ui->cloudlinklabel->setText("本次连接尝试失败");
        }
            break;
        default:    break;
    }
}

//断开
void MainWindow::on_dislinkcloud_pushButton_clicked()
{
    emit closeCloudSocket();
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

/**********************************************************************************************

                                                8.菜单栏显示界面部分

***********************************************************************************************/

// 点击菜单栏“设置”->“Configure”,弹出配置页面，可以手动输入相关参数
void MainWindow::on_actionConfigure_triggered()
{
    ConfigurationUI *config = new ConfigurationUI(this);
    config->setWindowTitle("设置");
    if(config->exec() == QDialog::Accepted)  // 点击确认
    {
        userInputAll = config->getUserInputParameters();
    }
    delete config;
}

// 点击菜单栏“设置”->“Appearence”,弹出图表主题页面，可以修改图表主题
void MainWindow::on_actionAppearence_triggered()
{
    int index;
    ChartThemeOption *trendMaker = new ChartThemeOption(this);
    trendMaker->setWindowTitle("主题颜色");
    if(trendMaker->exec() == QDialog::Accepted)  // 点击确认
    {
        index = trendMaker->getCurrentTheme();
        switch (index)
        {
        case 0:
        {
            fbgChart->setTheme(QChart::ChartThemeLight);
            ds18No1Chart->setTheme(QChart::ChartThemeBlueCerulean);
            ds18No2Chart->setTheme(QChart::ChartThemeBlueCerulean);
            envBarChart->setTheme(QChart::ChartThemeBlueCerulean);
            laserSensorChart->setTheme(QChart::ChartThemeDark);
        }
            break;
        case 1:
        {
            fbgChart->setTheme(QChart::ChartThemeDark);
            ds18No1Chart->setTheme(QChart::ChartThemeBrownSand);
            ds18No2Chart->setTheme(QChart::ChartThemeBrownSand);
            envBarChart->setTheme(QChart::ChartThemeBrownSand);
            laserSensorChart->setTheme(QChart::ChartThemeBlueCerulean);
        }
            break;
        case 2:
        {
            fbgChart->setTheme(QChart::ChartThemeDark);
            ds18No1Chart->setTheme(QChart::ChartThemeBrownSand);
            ds18No2Chart->setTheme(QChart::ChartThemeBrownSand);
            envBarChart->setTheme(QChart::ChartThemeBrownSand);
            laserSensorChart->setTheme(QChart::ChartThemeHighContrast);
        }
            break;
        case 3:
        {
            fbgChart->setTheme(QChart::ChartThemeBrownSand);
            ds18No1Chart->setTheme(QChart::ChartThemeHighContrast);
            ds18No2Chart->setTheme(QChart::ChartThemeHighContrast);
            envBarChart->setTheme(QChart::ChartThemeHighContrast);
            laserSensorChart->setTheme(QChart::ChartThemeLight);
        }
            break;
        case 4:
        {
            fbgChart->setTheme(QChart::ChartThemeHighContrast);
            ds18No1Chart->setTheme(QChart::ChartThemeLight);
            ds18No2Chart->setTheme(QChart::ChartThemeLight);
            envBarChart->setTheme(QChart::ChartThemeLight);
            laserSensorChart->setTheme(QChart::ChartThemeBlueCerulean);
        }
            break;
        default: break;
        }
    }
    delete trendMaker;
}

// 点击“帮助”->“Contact us”，弹出联系页面，可访问云平台
void MainWindow::on_actionContacts_triggered()
{
    ContactUsUi *giveMeMoney = new ContactUsUi(this);
    giveMeMoney->setWindowTitle("联系我们");
    if(giveMeMoney->exec() == QDialog::Accepted)
    delete giveMeMoney;
}

// 点击“帮助”->“About CPS”，弹出介绍页面，简介什么是CPS
void MainWindow::on_actionAbout_CPS_triggered()
{
    AboutCpsUi *whatIsCps = new AboutCpsUi(this);
    whatIsCps->setWindowTitle("CPS简介");
    if(whatIsCps->exec() == QDialog::Accepted)
    delete whatIsCps;
}

// 点击“推荐”->“Music”，弹出音乐推荐页面
void MainWindow::on_actionmusic_triggered()
{
    MusicIntrductionUi *sheSingsMeaSong = new MusicIntrductionUi(this);
    sheSingsMeaSong->setWindowTitle("音乐推荐");
    if(sheSingsMeaSong->exec() == QDialog::Accepted)
    delete sheSingsMeaSong;
}

// 点击“推荐”->“TV Series”，弹出美国和英国电视剧推荐页面
void MainWindow::on_actionTV_Series_triggered()
{
    SeriesIntroductionUi *gameOfThrone = new SeriesIntroductionUi(this);
    gameOfThrone->setWindowTitle("电视剧推荐");
    if(gameOfThrone->exec() == QDialog::Accepted)
    delete gameOfThrone;
}

// 点击“推荐”->“Animation & Comic”，弹出动漫推荐页面
void MainWindow::on_actionAnimation_triggered()
{
    AnimationIntroductionUi *onePiece = new AnimationIntroductionUi(this);
    onePiece->setWindowTitle("动漫推荐");
    if(onePiece->exec() == QDialog::Accepted)
    delete onePiece;
}
