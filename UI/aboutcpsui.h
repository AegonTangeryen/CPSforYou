#ifndef ABOUTCPSUI_H
#define ABOUTCPSUI_H

#include <QDialog>

namespace Ui {
class AboutCpsUi;
}

class AboutCpsUi : public QDialog
{
    Q_OBJECT

public:
    explicit AboutCpsUi(QWidget *parent = 0);
    ~AboutCpsUi();

private:
    Ui::AboutCpsUi *ui;
};

#endif // ABOUTCPSUI_H
