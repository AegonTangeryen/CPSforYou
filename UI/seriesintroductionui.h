#ifndef SERIESINTRODUCTIONUI_H
#define SERIESINTRODUCTIONUI_H

#include <QDialog>

namespace Ui {
class SeriesIntroductionUi;
}

class SeriesIntroductionUi : public QDialog
{
    Q_OBJECT

public:
    explicit SeriesIntroductionUi(QWidget *parent = 0);
    ~SeriesIntroductionUi();

private:
    Ui::SeriesIntroductionUi *ui;
};

#endif // SERIESINTRODUCTIONUI_H
