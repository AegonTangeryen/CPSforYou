#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFont>
#include "ds18tcpthread.h"
#include "fbgudpthread.h"
#include "cloudtcpthread.h"
#include "thermalerrorcompensation.h"
#include "envithread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void recordAllFbg();
    void recordAllDs18b20(DS18B20_Node (*a)[DS18B20_Index_Max], int nrow1, DS18B20_Node (*b)[DS18B20_Index_Max], int nrow2);
    void recordNo1Ds18b20(DS18B20_Node (*a)[DS18B20_Index_Max], int nrow);
    void recordNo2Ds18b20(DS18B20_Node (*b)[DS18B20_Index_Max], int nrow);
    void recordAllEnvironmentt(Env_Node *a, int nrow);
    void recordAllCnc(CNCInfoReg CNCInfo);
    void recordAllLaserSensors(QString *gc);

private slots:
    void timeisup();

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
    void showCCDResults(QString *yt);
    void ccdUiOperation(QString joffery);

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

    void on_envlinkpushButton_clicked();
    void showEnvMsg(QString loveU, int loveMe);
    void on_envdislinkpushButton_clicked();

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
    QString EverydayPath;    // 每日数据集的路径
    QString originalPath;
    QString samplePath;
    QString FbgAllDataPath;
    QString fbgAllTempPath;
    QString fbgAllStressPath;
    QString ds18AllDataPath;
    QString envAllDataPath;
    QString hncAllDataPath;
    QString laserAllDataPath;
    QString currentDate;
    QString currentday;
    QTimer *kingTimer;       // 主定时器
    long int taskTimeCnt;    // 各项任务的周期
    QMutex *globalLock;
    QLabel *statusbarCNCLabel,*statusbarDs18Label,*statusbarFBGLabel,*statusbarCCDLabel;
    QString fbgSamplePath;
    QString ds18SamplePath;
    QString ds18No1SamplePath;
    QString ds18No2SamplePath;
    QString dsNo1DataPath;
    QString dsNo2DataPath;
    QString envSamplePath;
    QString hncSamplePath;
    QString laserSamplePath;
};

#endif // MAINWINDOW_H
