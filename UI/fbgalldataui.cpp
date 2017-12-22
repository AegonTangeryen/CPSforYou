#include "fbgalldataui.h"
#include "ui_fbgalldataui.h"

fbgAllDataUi::fbgAllDataUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fbgAllDataUi)
{
    ui->setupUi(this);

    ui->tableWidget->setWindowTitle("光纤光栅传感器32通道*20节点示数展示");
    QStringList header;
    for(int channum=1;channum<=32;channum++)
    {
        QString title;
        if(channum<10)
        {
            title = "TCH0"+QString::number(channum,10);
        }
        else
        {
            title = "TCH"+QString::number(channum,10);
        }
        header<<title;
    }
    ui->tableWidget->setHorizontalHeaderLabels(header);

    marquessTimer = new QTimer(this);
    marquessTimer->setInterval(3000);
    connect(marquessTimer,&QTimer::timeout,this,&fbgAllDataUi::refreshTable);
    marquessTimer->start();
}

fbgAllDataUi::~fbgAllDataUi()
{
    delete ui;
}

void fbgAllDataUi::refreshTable()
{
    if(fbgWorkingStatus)
    {
        for(int col=0;col<32;col++)     // 每个通道，按列填充
        {
            for(int row=0;row<20;row++) // 每个节点
            {
                ui->tableWidget->setItem(row,col,new QTableWidgetItem(FBG_ALL[col][row]));
            }
        }
    }
}
