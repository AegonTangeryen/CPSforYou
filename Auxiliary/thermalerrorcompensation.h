#ifndef THERMALERRORCOMPENSATION_H
#define THERMALERRORCOMPENSATION_H

#include "hnc848system.h"
#include "ds18b20sensor.h"
#include "fbgsensos.h"
#include <QSettings>     // 读写ini文件

#define inputNum 4

struct ModelParameter
{
    ModelParameter()
    {
        md_channel = 0;
        md_indx = 0;
        md_para = "";
    }
    ModelParameter(int chan,int idx,QString para)
    {
        md_channel = chan;
        md_indx = idx;
        md_para = para;
    }

    int md_channel;
    int md_indx;
    QString md_para;
};

class ThermalErrorCompensation: public QThread
{
    Q_OBJECT

public:
    ThermalErrorCompensation(QString path);
    ~ThermalErrorCompensation();

    void paraRegister(); // 从ini文件中录入关键点以及参数信息
    double predictionModels();
    void compensationStrategy(double xAxis, double yAxis, double zAxis);
    void run();

    QVector<ModelParameter> paraVector;
    QTimer *duketimer;
    QSettings *parameterIni;
    QString compenPath;
    QVector<double> paraSet;  // 参数集合
    long int compenCnt;
    int paraNum;
    QString sensorType;
    bool compPermission;
    bool time2Quit;
    bool clearFlag;
    bool firstZero;
    bool uAreFree2Comp;

signals:
    void replyPredictionResult(double sansa);
    void replyAcutalCompensation(int);
    void replyInfo(int, QString);

public slots:
    void timeisup();
    void niceNewDay(QString gaintPanda);
    void forceThread2Quit();
};

#endif // THERMALERRORCOMPENSATION_H
