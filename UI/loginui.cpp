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
