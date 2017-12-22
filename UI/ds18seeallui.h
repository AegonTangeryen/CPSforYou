#ifndef DS18SEEALLUI_H
#define DS18SEEALLUI_H

#include <QDialog>

namespace Ui {
class Ds18SeeAllUi;
}

class Ds18SeeAllUi : public QDialog
{
    Q_OBJECT

public:
    explicit Ds18SeeAllUi(QWidget *parent = 0);
    ~Ds18SeeAllUi();

private:
    Ui::Ds18SeeAllUi *ui;
};

#endif // DS18SEEALLUI_H
