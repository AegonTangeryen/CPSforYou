#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIconText("失败总比遗憾好");
    w.setWindowTitle("Cyber Physical System @Lannister");
    w.show();

    return a.exec();
}
