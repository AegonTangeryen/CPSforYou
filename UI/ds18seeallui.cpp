#include "ds18seeallui.h"
#include "ui_ds18seeallui.h"

Ds18SeeAllUi::Ds18SeeAllUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ds18SeeAllUi)
{
    ui->setupUi(this);
}

Ds18SeeAllUi::~Ds18SeeAllUi()
{
    delete ui;
}
