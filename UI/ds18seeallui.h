#ifndef DS18SEEALLUI_H
#define DS18SEEALLUI_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <ds18b20sensor.h>

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
    QTimer *churchTimer;

private slots:
    void refreshTable();
};

#endif // DS18SEEALLUI_H
