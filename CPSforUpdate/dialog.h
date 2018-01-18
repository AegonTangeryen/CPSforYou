#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTextCodec>
#include <QFileInfo>
#include <QSettings>
#include <QProcess>
#include <QList>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QObject>
#include <QtNetwork>
#include <QTimer>
#include <QNetworkInterface>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <QImage>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public:
    void startRequest(QUrl url); // 开始请求

private:
    Ui::Dialog *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QUrl exeUrl;
    QUrl iniUrl;
    QFile *file;
    QSettings *updateIniRead;
    QString oldFileName;
    QString newFileName;
    quint16 taskDonwloaded;
    QProcess *mainProcess;
    QImage *cloudPageImg;
    quint8 scrollPicCnt;
    QTimer *earlTimer;

private slots:
    void httpReadyRead();                       // http准备读取数据
    void updateDataReadProgress(qint64,qint64); // 更新进度条
    void httpFinished();                        // http传输完成
    void scrollPicture();
};

#endif // DIALOG_H
