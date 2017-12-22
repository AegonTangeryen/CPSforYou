#include "seriesintroductionui.h"
#include "ui_seriesintroductionui.h"

SeriesIntroductionUi::SeriesIntroductionUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeriesIntroductionUi)
{
    ui->setupUi(this);
}

SeriesIntroductionUi::~SeriesIntroductionUi()
{
    delete ui;
}
