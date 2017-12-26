#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    mainProcess = new QProcess();
    manager = new QNetworkAccessManager(this);
    QString dirPath = QDir::currentPath();
    updateIniRead = new QSettings(dirPath+"/update.ini", QSettings::IniFormat);
    dllUrl = updateIniRead->value("/update/dllUrl").toString(); // 下载新版dll的网址
    iniUrl = updateIniRead->value("/update/iniUrl").toString(); // 下载新版ini文件的网址

    taskDonwloaded = 0; // 准备下载dll
    QFileInfo info(dllUrl.path());
    newFileName = info.fileName();
    oldFileName = QDir::currentPath()+"/data_wuzhong7.exe";  // 正式使用中的名称
    file = new QFile(newFileName);                           // file指向新下载的文件
    if(!file->open(QIODevice::WriteOnly))
    {
        delete file;    file = 0;
        return;
    }
    startRequest(dllUrl);
    ui->label->setText("正在下载dll文件：");
    ui->progressBar->setValue(0);
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
    if(taskDonwloaded == 0)   // dll下载完成，准备下载ini文件
    {
        taskDonwloaded = 1;
        file->setFileName(oldFileName);   // 删除旧版dll
        if(file->exists()) file->remove();
        file->setFileName(newFileName);   // 修改文件名
        file->rename(newFileName,"data_wuzhong7.exe"); // 一定要在文件关闭之后改名字

        QFileInfo info(iniUrl.path());
        newFileName = info.fileName();
        oldFileName = QDir::currentPath()+"/QQconfig.exe";  // 正式使用中的名称
        file->setFileName(newFileName);                  // file指向ini文件
        if(!file->open(QIODevice::WriteOnly))
        {
            delete file;    file = 0;
            return;
        }
        startRequest(iniUrl);
        ui->label->setText("正在下载ini文件：");
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
        ui->label->setText("下载完毕,有缘再见");
        reply->deleteLater();
        reply = 0;
        delete file;
        file = 0;
        double newVersion = updateIniRead->value("/update/newVersion").toDouble();
        updateIniRead->setValue("/program/version",newVersion);
        updateIniRead->setValue("/program/autoStart",1);
        ui->label->setText("正在启动CPSforU.exe......");
        Sleep(3000);
        mainProcess->startDetached("E:/CPS/CPSforU.exe");
        killTask("CPSforUpdate.exe");
    }
}

// 强制结束自身进程
int Dialog::killTask(const QString& exe)
{
    //1、根据进程名称找到PID
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return -1;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return -1;
    }
    BOOL    bRet = FALSE;
    DWORD dwPid = -1;
    while (Process32Next(hProcessSnap, &pe32)) // 将WCHAR转成const char*
    {
        int iLn = WideCharToMultiByte (CP_UTF8, 0, const_cast<LPWSTR> (pe32.szExeFile), static_cast<int>(sizeof(pe32.szExeFile)), NULL, 0, NULL, NULL);
        std::string result (iLn, 0);
        WideCharToMultiByte (CP_UTF8, 0, pe32.szExeFile, static_cast<int>(sizeof(pe32.szExeFile)), const_cast<LPSTR> (result.c_str()), iLn, NULL, NULL);
        if (0 == strcmp(exe.toStdString().c_str(), result.c_str ()))
        {
            dwPid = pe32.th32ProcessID;
            bRet = TRUE;
            break;
        }
    }
    CloseHandle(hProcessSnap);
    //2、根据PID杀死进程
    HANDLE hProcess=NULL;
    hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,dwPid); // 打开目标进程
    if (hProcess==NULL) {
        qDebug()<<"Open Process fAiled ,error:"<<GetLastError();
        return -1;
    }
    DWORD ret=TerminateProcess(hProcess,0); // 结束目标进程
    if(ret==0) {
        qDebug()<<"kill task faild,error:"<<GetLastError();
        return -1;
    }

    return 0;
}
