#include "chartthemeoption.h"
#include "ui_chartthemeoption.h"

ChartThemeOption::ChartThemeOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartThemeOption)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Light");
    ui->comboBox->addItem("BlueCerulean");
    ui->comboBox->addItem("Dark");
    ui->comboBox->addItem("BrownSand");
    ui->comboBox->addItem("HighContrast");
}

ChartThemeOption::~ChartThemeOption()
{
    delete ui;
}

int ChartThemeOption::getCurrentTheme()
{
    return ui->comboBox->currentIndex();
}
