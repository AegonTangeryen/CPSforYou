#ifndef CONFIGURATIONUI_H
#define CONFIGURATIONUI_H

#include <QDialog>
#include <QFont>
#include "tools.h"

namespace Ui {
class ConfigurationUI;
}

class ConfigurationUI : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationUI(QWidget *parent = 0);
    ~ConfigurationUI();

    QStringList getUserInputParameters();  // 获取用户输入的所有信息

private:
    Ui::ConfigurationUI *ui;
};

#endif // CONFIGURATIONUI_H
