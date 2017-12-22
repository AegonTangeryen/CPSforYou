#ifndef CHARTTHEMEOPTION_H
#define CHARTTHEMEOPTION_H

#include <QDialog>
#include <QFont>
#include <QComboBox>
#include "tools.h"

namespace Ui {
class ChartThemeOption;
}

class ChartThemeOption : public QDialog
{
    Q_OBJECT

public:
    explicit ChartThemeOption(QWidget *parent = 0);
    ~ChartThemeOption();

    int getCurrentTheme();    // 获取当前用户选择的风格

private:
    Ui::ChartThemeOption *ui;
};

#endif // CHARTTHEMEOPTION_H
