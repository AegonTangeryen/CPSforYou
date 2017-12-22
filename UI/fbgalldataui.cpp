#include "fbgalldataui.h"
#include "ui_fbgalldataui.h"

fbgAllDataUi::fbgAllDataUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fbgAllDataUi)
{
    ui->setupUi(this);
}

fbgAllDataUi::~fbgAllDataUi()
{
    delete ui;
}
