#include "configurationui.h"
#include "ui_configurationui.h"

ConfigurationUI::ConfigurationUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationUI)
{
    ui->setupUi(this);

    QPalette wordColor; QFont wordFont;
    wordColor.setColor(QPalette::WindowText,Qt::white);
    wordFont.setPointSize(16); wordFont.setBold(true); wordFont.setItalic(true);
    ui->fbgipconfigure->setText("192.168.0.119");
    ui->fbgipconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->fbgipconfigure->setFont(wordFont);;
    ui->fbgipconfigure->setPalette(wordColor);

    ui->fbgportconfigure->setText("4010");
    ui->fbgportconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->fbgportconfigure->setFont(wordFont);;
    ui->fbgportconfigure->setPalette(wordColor);

    ui->dsno1portconfigure->setText("1001");
    ui->dsno1portconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->dsno1portconfigure->setFont(wordFont);;
    ui->dsno1portconfigure->setPalette(wordColor);

    ui->dsno2portconfigure->setText("3003");
    ui->dsno2portconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->dsno2portconfigure->setFont(wordFont);;
    ui->dsno2portconfigure->setPalette(wordColor);

    ui->envportconfigure->setText("2002");
    ui->envportconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->envportconfigure->setFont(wordFont);;
    ui->envportconfigure->setPalette(wordColor);

    ui->hncipconfigure->setText("192.168.0.113");
    ui->hncipconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->hncipconfigure->setFont(wordFont);;
    ui->hncipconfigure->setPalette(wordColor);

    ui->hncportconfigure->setText("5555");
    ui->hncportconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->hncportconfigure->setFont(wordFont);;
    ui->hncportconfigure->setPalette(wordColor);

    ui->laseripconfigure->setText("192.168.0.53");
    ui->laseripconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->laseripconfigure->setFont(wordFont);;
    ui->laseripconfigure->setPalette(wordColor);

    ui->cloudipconfigure->setText("59.69.101.206");
    ui->cloudipconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->cloudipconfigure->setFont(wordFont);;
    ui->cloudipconfigure->setPalette(wordColor);

    ui->cloudportconfigure->setText("3690");
    ui->cloudportconfigure->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    ui->cloudportconfigure->setFont(wordFont);;
    ui->cloudportconfigure->setPalette(wordColor);
}

ConfigurationUI::~ConfigurationUI()
{
    delete ui;
}

QStringList ConfigurationUI::getUserInputParameters()
{
    QStringList paraAll;
    QString lineEditContent;
    lineEditContent = ui->fbgipconfigure->text();
    paraAll.append(lineEditContent);

    lineEditContent = ui->fbgportconfigure->text();
    paraAll.append(lineEditContent);

    lineEditContent = ui->dsno1portconfigure->text();
    paraAll.append(lineEditContent);

    lineEditContent = ui->dsno2portconfigure->text();
    paraAll.append(lineEditContent);

    lineEditContent = ui->envportconfigure->text();
    paraAll.append(lineEditContent);

    lineEditContent = ui->hncipconfigure->text();
    paraAll.append(lineEditContent);

    lineEditContent = ui->hncportconfigure->text();
    paraAll.append(lineEditContent);

    lineEditContent = ui->laseripconfigure->text();
    paraAll.append(lineEditContent);

    lineEditContent = ui->cloudipconfigure->text();
    paraAll.append(lineEditContent);

    lineEditContent = ui->cloudportconfigure->text();
    paraAll.append(lineEditContent);

    return paraAll;
}
