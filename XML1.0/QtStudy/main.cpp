#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    static MainWindow w;
    w.setWindowTitle("XML转换工具");
    w.show();
    return a.exec();
}
