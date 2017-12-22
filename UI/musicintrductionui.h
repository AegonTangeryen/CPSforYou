#ifndef MUSICINTRDUCTIONUI_H
#define MUSICINTRDUCTIONUI_H

#include <QDialog>

namespace Ui {
class MusicIntrductionUi;
}

class MusicIntrductionUi : public QDialog
{
    Q_OBJECT

public:
    explicit MusicIntrductionUi(QWidget *parent = 0);
    ~MusicIntrductionUi();

private:
    Ui::MusicIntrductionUi *ui;
};

#endif // MUSICINTRDUCTIONUI_H
