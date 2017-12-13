#ifndef DS18ALLDATAUI_H
#define DS18ALLDATAUI_H

#include <QMainWindow>

namespace Ui {
class Ds18AllDataUI;
}

class Ds18AllDataUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ds18AllDataUI(QWidget *parent = 0);
    ~Ds18AllDataUI();

private:
    Ui::Ds18AllDataUI *ui;
};

#endif // DS18ALLDATAUI_H
