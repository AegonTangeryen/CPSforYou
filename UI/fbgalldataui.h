#ifndef FBGALLDATAUI_H
#define FBGALLDATAUI_H

#include <QDialog>
#include "fbgsensos.h"
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class fbgAllDataUi;
}

class fbgAllDataUi : public QDialog
{
    Q_OBJECT

public:
    explicit fbgAllDataUi(QWidget *parent = 0);
    ~fbgAllDataUi();

private slots:
    void refreshTable();

private:
    Ui::fbgAllDataUi *ui;
    QTimer *marquessTimer;
};

#endif // FBGALLDATAUI_H
