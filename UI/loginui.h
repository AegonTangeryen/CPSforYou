#ifndef LOGINUI_H
#define LOGINUI_H

#include <QDialog>
#include <QProcess>
#include <QString>
#include <QTextCodec>
#include <QFileInfo>
#include <QSettings>
#include "tools.h"
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include "inquireupdateui.h"

namespace Ui {
class LogInUi;
}

class LogInUi : public QDialog
{
    Q_OBJECT

public:
    explicit LogInUi(QWidget *parent = 0);
    ~LogInUi();

public:
    int killTask(const QString& exe);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_checkBox_clicked();

private:
    Ui::LogInUi *ui;
    QProcess *updateProcess;
    QSettings *updateIniRead;
    double currentVersion;
    double newVersion;
};

#endif // LOGINUI_H
