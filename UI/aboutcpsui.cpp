#include "aboutcpsui.h"
#include "ui_aboutcpsui.h"

AboutCpsUi::AboutCpsUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutCpsUi)
{
    ui->setupUi(this);
}

AboutCpsUi::~AboutCpsUi()
{
    delete ui;
}
