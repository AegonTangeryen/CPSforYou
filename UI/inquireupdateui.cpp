#include "inquireupdateui.h"
#include "ui_inquireupdateui.h"

InquireUpdateUi::InquireUpdateUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InquireUpdateUi)
{
    ui->setupUi(this);
}

InquireUpdateUi::~InquireUpdateUi()
{
    delete ui;
}
