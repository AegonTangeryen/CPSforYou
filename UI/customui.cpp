#include "customui.h"
#include "ui_customui.h"

CustomUi::CustomUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomUi)
{
    ui->setupUi(this);
}

CustomUi::~CustomUi()
{
    delete ui;
}
