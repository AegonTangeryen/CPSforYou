#ifndef CUSTOMUI_H
#define CUSTOMUI_H

#include <QDialog>

namespace Ui {
class CustomUi;
}

class CustomUi : public QDialog
{
    Q_OBJECT

public:
    explicit CustomUi(QWidget *parent = 0);
    ~CustomUi();

private:
    Ui::CustomUi *ui;
};

#endif // CUSTOMUI_H
