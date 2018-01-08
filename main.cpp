#include "loginui.h"
#include "mainwindow.h"
#include <QApplication>

// 打印程序运行信息
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1)").arg(QString(context.file));
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3").arg(current_date).arg(context_info).arg(msg);

    QFile file("cpslog.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();
}

// 主函数
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(outputMessage); // 注册MessageHandler
    LogInUi normandyLanding;
    normandyLanding.setWindowTitle("登录");
    if(normandyLanding.exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.setWindowTitle("Whut Cyber Physical System for Heavy-duty machine tool");
        w.show();
        return a.exec();
    }
    else return 0;
}
