#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    cloudPageImg = new QImage;
    cloudPageImg->load(":/img/wuzhong1.jpg");
    ui->picturelabel->setPixmap(QPixmap::fromImage(*cloudPageImg));

    scrollPicCnt=0;
    earlTimer = new QTimer(this);
    earlTimer->setInterval(2000);
    earlTimer->setTimerType(Qt::PreciseTimer);
    connect(earlTimer,&QTimer::timeout,this,&Dialog::scrollPicture);

    mainProcess = new QProcess(this); // 用于打开主程序CPSforU
    manager = new QNetworkAccessManager(this);
    updateIniRead = new QSettings(QDir::currentPath()+"/update.ini",
                                  QSettings::IniFormat,this);
    exeUrl = updateIniRead->value("/update/exeUrl").toString(); // 新版exe的url
    iniUrl = updateIniRead->value("/update/iniUrl").toString(); // 新版ini文件的url

    taskDonwloaded = 0; // 下载任务编号，准备下载exe
    QFileInfo info(exeUrl.path());
    newFileName = info.fileName();
    oldFileName = QDir::currentPath()+"/CPSforU3.exe";  // 正式使用中的名称
    file = new QFile(newFileName);                     // file指向新下载的文件
    if(!file->open(QIODevice::WriteOnly))
    {
        delete file;
        file = 0;
        return;
    }
    startRequest(exeUrl);
    ui->label->setText("正在下载新版exe文件：");
    ui->progressBar->setValue(0);
    earlTimer->start();
}

Dialog::~Dialog()
{
    delete ui;
}

// 开始请求下载
void Dialog::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply,SIGNAL(readyRead()),this,SLOT(httpReadyRead()));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateDataReadProgress(qint64,qint64)));
    connect(reply,SIGNAL(finished()),this,SLOT(httpFinished()));
}

// 如果创建了文件，将http传输来的数据写入到文件中
void Dialog::httpReadyRead()
{
    if(file) file->write(reply->readAll());
}

// 持续更新进度条
void Dialog::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

//完成下载后将进度条隐藏，将缓冲数据刷新到文件中，然后删除掉file和reply的对象
void Dialog::httpFinished()
{
    file->flush();
    file->close();

    if(taskDonwloaded == 0)   // exe下载完成，改名后下载ini文件
    {
        taskDonwloaded = 1;
        file->setFileName(oldFileName);   // 删除旧版EXE
        if(file->exists()) file->remove();
        file->setFileName(newFileName);   // 修改文件名
        file->rename(newFileName,"CPSforU3.exe"); // 一定要在文件关闭之后改名字

        QFileInfo info(iniUrl.path());
        newFileName = info.fileName();
        oldFileName = QDir::currentPath()+"/QQconfig.exe";  // 正式使用中的名称
        file->setFileName(newFileName);                  // file指向ini文件
        if(!file->open(QIODevice::WriteOnly))
        {
            delete file;
            file = 0;
            return;
        }
        startRequest(iniUrl);
        ui->label->setText("正在下载新版ini文件：");
        ui->progressBar->setValue(0);
    }
    else if(taskDonwloaded == 1) // ini下载完成
    {
        taskDonwloaded = 0;
        file->setFileName(oldFileName);   // 删除旧版ini文件
        if(file->exists()) file->remove();
        file->setFileName(newFileName);   // 修改文件名
        file->rename(newFileName,"QQconfig.exe");

        ui->progressBar->hide();
        reply->deleteLater();
        reply = 0;
        delete file;
        file = 0;

        // 下载完毕，准备启动主程序CPSforU
        double latestVersion = updateIniRead->value("/update/newVersion").toDouble();
        updateIniRead->setValue("/program/version",latestVersion);
        updateIniRead->setValue("/program/userAction",0);
        ui->label->setText("正在启动CPSforU.exe......");
        Sleep(2000);
        if(mainProcess->startDetached("./CPSforU.exe"))
        {
            QApplication::quit();
        }
        else
        {
            ui->label->setText("启动失败，请关闭本程序并手动开启CPSforU");
        }
    }
}

// 图片滚动播放
void Dialog::scrollPicture()
{
    switch (scrollPicCnt) {
    case 0:
        cloudPageImg->load(":/img/whut1.jpg");
        ui->picturelabel->setPixmap(QPixmap::fromImage(*cloudPageImg));
        break;
    case 1:
        cloudPageImg->load(":/img/whut2.jpg");
        ui->picturelabel->setPixmap(QPixmap::fromImage(*cloudPageImg));
        break;
    case 2:
        cloudPageImg->load(":/img/whut6.jpg");
        ui->picturelabel->setPixmap(QPixmap::fromImage(*cloudPageImg));
        break;
    case 3:
        cloudPageImg->load(":/img/whut3.jpg");
        ui->picturelabel->setPixmap(QPixmap::fromImage(*cloudPageImg));
        break;
    case 4:
        cloudPageImg->load(":/img/whut4.jpg");
        ui->picturelabel->setPixmap(QPixmap::fromImage(*cloudPageImg));
        break;
    case 5:
        cloudPageImg->load(":/img/pikachu.jpg");
        ui->picturelabel->setPixmap(QPixmap::fromImage(*cloudPageImg));
        break;
    default:
        break;
    }
    scrollPicCnt++;
    if(scrollPicCnt==5) scrollPicCnt=0;
}
