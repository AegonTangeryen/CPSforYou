#ifndef LOGINUI_H
#define LOGINUI_H

#include <QDialog>

namespace Ui {
class LogInUi;
}

class LogInUi : public QDialog
{
    Q_OBJECT

public:
    explicit LogInUi(QWidget *parent = 0);
    ~LogInUi();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_checkBox_clicked();

private:
    Ui::LogInUi *ui;
};

#endif // LOGINUI_H
