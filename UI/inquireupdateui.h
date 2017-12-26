#ifndef INQUIREUPDATEUI_H
#define INQUIREUPDATEUI_H

#include <QDialog>

namespace Ui {
class InquireUpdateUi;
}

class InquireUpdateUi : public QDialog
{
    Q_OBJECT

public:
    explicit InquireUpdateUi(QWidget *parent = 0);
    ~InquireUpdateUi();

private:
    Ui::InquireUpdateUi *ui;
};

#endif // INQUIREUPDATEUI_H
