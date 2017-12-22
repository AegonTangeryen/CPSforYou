#ifndef CONTACTUSUI_H
#define CONTACTUSUI_H

#include <QDialog>

namespace Ui {
class ContactUsUi;
}

class ContactUsUi : public QDialog
{
    Q_OBJECT

public:
    explicit ContactUsUi(QWidget *parent = 0);
    ~ContactUsUi();

private:
    Ui::ContactUsUi *ui;
};

#endif // CONTACTUSUI_H
