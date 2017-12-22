#ifndef THERMALERRORCOMPENSATION_H
#define THERMALERRORCOMPENSATION_H

#include "hnc848system.h"
#include "ds18b20sensor.h"
#include "fbgsensos.h"

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
    double predictionModels();
    bool time2Quit;
    void compensationStrategy(double xAxis, double yAxis, double zAxis);
    void run();

    QVector<ModelParameter> paraVector;
    QTimer *duketimer;
    QString compenPath;
    long int compenCnt;
    bool compPermission;
    bool clearFlag;
    bool firstZero;
    bool uAreFree2Comp;

signals:
    void replyPredictionResult(double sansa);
    void replyAcutalCompensation(int);

public slots:
    void timeisup();
    void niceNewDay(QString gaintPanda);
    void forceThread2Quit();
};

#endif // THERMALERRORCOMPENSATION_H
