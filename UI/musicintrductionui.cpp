#include "musicintrductionui.h"
#include "ui_musicintrductionui.h"

MusicIntrductionUi::MusicIntrductionUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicIntrductionUi)
{
    ui->setupUi(this);
}

MusicIntrductionUi::~MusicIntrductionUi()
{
    delete ui;
}
