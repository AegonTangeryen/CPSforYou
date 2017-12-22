#ifndef FBGALLDATAUI_H
#define FBGALLDATAUI_H

#include <QDialog>

namespace Ui {
class fbgAllDataUi;
}

class fbgAllDataUi : public QDialog
{
    Q_OBJECT

public:
    explicit fbgAllDataUi(QWidget *parent = 0);
    ~fbgAllDataUi();

private:
    Ui::fbgAllDataUi *ui;
};

#endif // FBGALLDATAUI_H
