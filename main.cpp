#include "loginui.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
