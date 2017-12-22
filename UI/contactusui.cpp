#include "contactusui.h"
#include "ui_contactusui.h"

ContactUsUi::ContactUsUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactUsUi)
{
    ui->setupUi(this);
}

ContactUsUi::~ContactUsUi()
{
    delete ui;
}
