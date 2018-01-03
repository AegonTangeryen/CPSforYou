#include "loginui.h"
#include "ui_loginui.h"
#include <QMessageBox>

LogInUi::LogInUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInUi)
{
    ui->setupUi(this);

    ui->username->setText("admin");
    ui->password->setText("admin");

//    updateProcess = new QProcess();
//    updateIniRead = new QSettings(QDir::currentPath()+"/update.ini", QSettings::IniFormat);
//    currentVersion = updateIniRead->value("/program/version").toDouble();
//    newVersion = updateIniRead->value("/update/newVersion").toDouble();
//    if(newVersion>currentVersion)
//    {
//        Sleep(1000);
//        QDialog *doUWant2Update = new InquireUpdateUi(this);
//        if(doUWant2Update->exec()==QDialog::Accepted)
//        {
//            updateProcess->start("E:/CPS/CPSforUpdate.exe");
//            delete doUWant2Update;
//            killTask("CPSforU.exe");
//        }
//    }
}

LogInUi::~LogInUi()
{
    delete ui;
}

// 登录按键
void LogInUi::on_pushButton_clicked()
{
    if(ui->username->text().trimmed()== tr("admin") &&
       ui->password->text().trimmed()==tr("admin"))
    {
        accept();
    }
    else if(ui->username->text().trimmed()== tr("lwf") &&
            ui->password->text().trimmed()==tr("123"))
    {
         accept();
    }
    else if(ui->username->text().trimmed()== tr("lannister") &&
            ui->password->text().trimmed()==tr("hearmeroar!"))
    {
         accept();
    }
    else
    {
        QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
        ui->username->clear();
        ui->password->clear();
        ui->username->setFocus();
    }
}

// 取消按键
void LogInUi::on_pushButton_2_clicked()
{
    close();
}

// 注册账号
void LogInUi::on_pushButton_3_clicked()
{
    QMessageBox::about(this,tr("心情不好"),tr("今天不允许注册"));
}

// 忘记密码
void LogInUi::on_pushButton_4_clicked()
{
    QMessageBox::about(this,tr("呵呵"),tr("你忘记密码我能怎么办"));
}

// 隐藏密码
void LogInUi::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()) ui->password->setEchoMode(QLineEdit::Password);
    else ui->password->setEchoMode(QLineEdit::Normal);
}

// 强制结束自身进程
int LogInUi::killTask(const QString& exe)
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
