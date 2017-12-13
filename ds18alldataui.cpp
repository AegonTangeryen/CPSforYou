#include "ds18alldataui.h"
#include "ui_ds18alldataui.h"

Ds18AllDataUI::Ds18AllDataUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ds18AllDataUI)
{
    ui->setupUi(this);
}

Ds18AllDataUI::~Ds18AllDataUI()
{
    delete ui;
}
