#include "loginui.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    LogInUi normandyLanding;
    normandyLanding.setWindowTitle("登录");
    if(normandyLanding.exec() == QDialog::Accepted)
    {
        w.setWindowTitle("Cyber Physical System @Lannister");
        w.show();
        return a.exec();
    }
    else return 0;
}
