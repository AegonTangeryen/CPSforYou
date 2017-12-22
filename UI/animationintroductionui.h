#ifndef ANIMATIONINTRODUCTIONUI_H
#define ANIMATIONINTRODUCTIONUI_H

#include <QDialog>

namespace Ui {
class AnimationIntroductionUi;
}

class AnimationIntroductionUi : public QDialog
{
    Q_OBJECT

public:
    explicit AnimationIntroductionUi(QWidget *parent = 0);
    ~AnimationIntroductionUi();

private:
    Ui::AnimationIntroductionUi *ui;
};

#endif // ANIMATIONINTRODUCTIONUI_H
