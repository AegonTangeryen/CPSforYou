#include "ds18seeallui.h"
#include "ui_ds18seeallui.h"

Ds18SeeAllUi::Ds18SeeAllUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ds18SeeAllUi)
{
    ui->setupUi(this);

    QStringList header;
    QString title;
    for(int channum=1;channum<=8;channum++)
    {
        if(channum<10)
        {
            title = "DCH0"+QString::number(channum,10);
        }
        else
        {
            title = "DCH"+QString::number(channum,10);
        }
        header<<title;
    }
    ui->no1tableWidget->setHorizontalHeaderLabels(header);

    header.clear();
    for(int channum=9;channum<=16;channum++)
    {
        if(channum<10)
        {
            title = "DCH0"+QString::number(channum,10);
        }
        else
        {
            title = "DCH"+QString::number(channum,10);
        }
        header<<title;
    }
    ui->no2tableWidget->setHorizontalHeaderLabels(header);

    churchTimer = new QTimer(this);
    churchTimer->setInterval(5000);
    connect(churchTimer,&QTimer::timeout,this,&Ds18SeeAllUi::refreshTable);
    churchTimer->start();
}

Ds18SeeAllUi::~Ds18SeeAllUi()
{
    delete ui;
}

// 每5s刷新一次表格
void Ds18SeeAllUi::refreshTable()
{
    if(ds18WorkingStatus) // 一号板
    {
        ui->no1tableWidget->clearContents(); // 刷新前先清除上次内存，防止内存泄漏
        for(int col=0;col<8;col++)     // 每个通道，按列填充
        {
            for(int row=0;row<8;row++) // 每个节点
            {
                ui->no1tableWidget->setItem(row,col,new QTableWidgetItem(DS18B20_ALL_Node[col][row].temperature));
            }
        }
    }
    if(ds18No2WorkStatus) // 二号板
    {
        ui->no2tableWidget->clearContents();
        for(int col=0;col<8;col++)
        {
            for(int row=0;row<8;row++)
            {
                ui->no2tableWidget->setItem(row,col,new QTableWidgetItem(DS18B20_ADD_Node[col][row].temperature));
            }
        }
    }
}
