#include "animationintroductionui.h"
#include "ui_animationintroductionui.h"

AnimationIntroductionUi::AnimationIntroductionUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationIntroductionUi)
{
    ui->setupUi(this);
}

AnimationIntroductionUi::~AnimationIntroductionUi()
{
    delete ui;
}
