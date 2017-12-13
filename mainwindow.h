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
    void recordAllDs18b20(DS18B20_Node (*a)[DS18B20_Index_Max], int nrow, DS18B20_Node (*b)[DS18B20_Index_Max], int nrow2);
    void recordAllEnvironmentt(Env_Node *a, int nrow);
    void recordAllCnc(CNCInfoReg CNCInfo);
    void recordAllLaserSensors(QString *gc);

private slots:
    void timeisup();

    void on_cnclink_pushButton_clicked();
    void on_cncdislink_pushButton_clicked();
    void showCNCMsg(QString msg, bool result);
    void showComp(short _105,short _106,short _107,unsigned int c1,unsigned int c2,unsigned int c3);
    void showCNCInfo(long cnc_ch,double x_pos,double y_pos,double z_pos,double speed,
                     double x_pwr,double y_pwr,double z_pwr,double main_pwr,QString cncstatu);

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
    void showFbgResults(QString);
    void fbgSeeAll();

    void on_lincloud_pushButton_clicked();
    void on_dislinkcloud_pushButton_clicked();
    void showCloudInfo(QString tully);

    void on_startcomp_pushButton_clicked();
    void clearCompBrowser();

    void on_closecomp_pushButton_clicked();
    void showPreCompResult(double arya);

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
};

#endif // MAINWINDOW_H
