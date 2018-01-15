#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFont>
#include <QChart>
#include <QChartView>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>
#include <QtMath>
#include <QPointF>
#include <QDateTimeAxis>
#include <QPieSeries>
#include <QPieSlice>
#include <QAbstractBarSeries>
#include <QPercentBarSeries>
#include <QStackedBarSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QAreaSeries>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QColor>
#include <QSystemTrayIcon>   // 系统托盘
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
#include <QIcon>

#include "ds18tcpthread.h"
#include "fbgudpthread.h"
#include "cloudtcpthread.h"
#include "thermalerrorcompensation.h"
#include "envithread.h"
#include "configurationui.h"            // 参数配置页面
#include "chartthemeoption.h"           // 风格配置页面
#include "customui.h"                   // 自娱自乐页面
#include "fbgalldataui.h"               // fbg全部数据页面
#include "ds18seeallui.h"               // ds18b20全部数据页面
#include "contactusui.h"                // 联系我们页面
#include "aboutcpsui.h"                 // CPS简介页面
#include "animationintroductionui.h"    // 动漫推荐页面
#include "musicintrductionui.h"         // 音乐推荐页面
#include "seriesintroductionui.h"       // 电视剧推荐页面

QT_CHARTS_USE_NAMESPACE  // 此句与头文件<QChart>放在同一文件

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void fbgPageInit();
    void ds18PageInit();
    void laserPageInit();
    void createNewFolderWhenAnotherDay();
    void refreshLaserResult();
    void recordAllFbg();
    void recordAllDs18b20(DS18B20_Node (*a)[DS18B20_Index_Max], int nrow1, DS18B20_Node (*b)[DS18B20_Index_Max], int nrow2);
    void recordNo1Ds18b20(DS18B20_Node (*a)[DS18B20_Index_Max], int nrow);
    void recordNo2Ds18b20(DS18B20_Node (*b)[DS18B20_Index_Max], int nrow);
    void recordAllEnvironmentt(Env_Node *a, int nrow);
    void recordAllCnc(CNCInfoReg CNCInfo);
    void recordAllLaserSensors(QString *gc);
    void rePlotFbg();
    void rePlotDs18No1();
    void rePlotDs18No2();
    void rePlotEnvironment();
    void rePlotLaserSensors();
    void detectConnection();
    void closeEvent(QCloseEvent *event);

private slots:
    void timeisup();         // 主定时器中断处理函数
    void plotTimePoll();     // 定时重新绘图
    void trayIsActived(QSystemTrayIcon::ActivationReason reason); // 单击或双击右下角托盘

    void on_cnclink_pushButton_clicked();
    void on_cncdislink_pushButton_clicked();
    void showCNCMsg(QString msg, bool result);
    void showComp(short _105,short _106,short _107,unsigned int c1,unsigned int c2,unsigned int c3);

    void on_ds18link_pushButton_clicked();
    void on_ds18dislink_pushButton_clicked();
    void showDS18Msg(QString msg, int status);
    void ds18SeeAll();

    void on_linkccd_pushButton_clicked();
    void on_zeroccd_pushButton_clicked();
    void on_closeccd_pushButton_clicked();
    void ccdUiOperation(QString joffery, int tommen);

    void on_FBGlink_pushButton_clicked();
    void on_FBGclose_pushButton_clicked();
    void showFbgResults(int tywin);
    void fbgSeeAll();

    void on_lincloud_pushButton_clicked();
    void on_dislinkcloud_pushButton_clicked();
    void showCloudInfo(QString tully, int blackfish);

    void on_startcomp_pushButton_clicked();
    void clearCompBrowser();
    void on_closecomp_pushButton_clicked();
    void showPreResult(double arya);
    void showCompResult(int robert);
    void showParaInfo(int a, QString kingslayer);

    void on_envlinkpushButton_clicked();
    void showEnvMsg(QString loveU, int loveMe);
    void on_envdislinkpushButton_clicked();

    void on_actionConfigure_triggered();
    void on_actionAppearence_triggered();
    void on_actionContacts_triggered();
    void on_actionAbout_CPS_triggered();
    void on_actionmusic_triggered();
    void on_actionTV_Series_triggered();
    void on_actionAnimation_triggered();
    void on_actionCustom_triggered();
    void on_actionWhut_cloudplatrm_triggered();

signals:
    void closeHncSystem();
    void closeFbgSocket();
    void closeDs18Sensors();
    void closeLaserSensors();
    void closeCloudSocket();
    void closeCompensation();
    void closeEnvironment();
    void createNewDayFolder(QString);

private:
    Ui::MainWindow *ui;

private:
    QDir *lwfdir;
    QString rootPath;
    QString EverydayPath;
    QString originalPath;
    QString samplePath;
    QString FbgAllDataPath;
    QString fbgAllTempPath;
    QString fbgAllStressPath;
    QString ds18AllDataPath;
    QString envAllDataPath;
    QString hncAllDataPath;
    QString laserAllDataPath;
    QString fbgSamplePath;
    QString ds18SamplePath;
    QString ds18No1SamplePath;
    QString ds18No2SamplePath;
    QString dsNo1DataPath;
    QString dsNo2DataPath;
    QString envSamplePath;
    QString hncSamplePath;
    QString laserSamplePath;

    QLabel *statusbarIndicator;
    QString currentday;
    QString currentDate;
    QTimer *kingTimer;          // 主定时器
    qint64 taskTimeCnt;         // 各项任务的周期
    qint16 ds18AllRecordCnt;    // 为防止数据未收齐一轮就抽样
    qint16 ds18No1RecordCnt;
    qint16 ds18No2RecordCnt;
    qint16 envRecordCnt;
    MMTimer *plotTimer;         // 刷新各个图表的定时器
    qint16 plotCnt;             // 绘图计数
    QMutex *globalLock;
    QStringList userInputAll;   // 用户手动输入的信息
    QSystemTrayIcon *systemTray;// 系统托盘
    QAction *restoreAct;        // 恢复窗口操作
    QAction *quitAct;           // 退出操作
    QMenu *trayClickMenu;       // 托盘右键菜单

    QChart *fbgChart;
    QSplineSeries *fbgSeriesCh1601;
    QSplineSeries *fbgSeriesCh1701;
    QSplineSeries *fbgSeriesCh1801;
    QValueAxis *fbgXaxis;
    QValueAxis *fbgYaxis;
    QList<double> fbg1601Data;
    QList<double> fbg1701Data;
    QList<double> fbg1801Data;
    qint16 maxFbgSize;

    QChart *ds18No1Chart;
    QSplineSeries *ds18seriesCh0701;
    QSplineSeries *ds18seriesCh0702;
    QSplineSeries *ds18seriesCh0703;
    QSplineSeries *ds18seriesCh0704;
    QValueAxis *ds18No1Xaxis;
    QValueAxis *ds18No1Yaxis;
    QList<double> ds180701Data;
    QList<double> ds180702Data;
    QList<double> ds180703Data;
    QList<double> ds180704Data;
    qint16 maxds18No1Size;

    QChart *ds18No2Chart;
    QSplineSeries *ds18seriesCh0901;
    QSplineSeries *ds18seriesCh1101;
    QSplineSeries *ds18seriesCh1301;
    QSplineSeries *ds18seriesCh1501;
    QValueAxis *ds18No2Xaxis;
    QValueAxis *ds18No2Yaxis;
    QList<double> ds180901Data;
    QList<double> ds181101Data;
    QList<double> ds181301Data;
    QList<double> ds181501Data;
    qint16 maxds18No2Size;

    QChart *envBarChart;
    QBarSeries *envBarSeries;
    QBarSet *frontSet;
    QBarSet *backSet;
    QBarSet *rightSet;
    QBarSet *leftSet;
    QBarCategoryAxis *envXaxis;
    QValueAxis *envYaxis;

    QChart *laserSensorChart;
    QSplineSeries *laserSensorX;
    QSplineSeries *laserSensorY;
    QSplineSeries *laserSensorZ;
    QValueAxis *laserSensorXaxis;
    QValueAxis *laserSensorYaxis;
    QList<double> laserXData;      // 存储业务数据的list
    QList<double> laserZData;
    qint16 maxLaserSize;
};

#endif // MAINWINDOW_H
