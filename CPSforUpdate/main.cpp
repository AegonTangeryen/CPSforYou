#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.resize(800,500);
    w.setWindowTitle("应用更新");
    w.show();

    return a.exec();
}
