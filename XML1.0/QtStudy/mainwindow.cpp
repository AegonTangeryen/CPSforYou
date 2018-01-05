#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataxml.h"
#include <QColorDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    devAllInfo allData; //信息对象
    xmlStr = dataXML::xmlStrCreat(dataInfo);    //生成XML
    ui->outXmlText->setText(xmlStr);

    connect(ui->transcodeButon,SIGNAL(clicked()),this,SLOT(clickedTranscodingButton()));
    connect(ui->clearButton,SIGNAL(clicked()),this,SLOT(clickedClearButton()));
    connect(ui->getDataButton,SIGNAL(clicked()),this,SLOT(clickedGetDataButton()));
    connect(ui->clearButton_2,SIGNAL(clicked()),this,SLOT(clickedClear2Button()));
}

void MainWindow::clickedTranscodingButton(){
    ui->outXmlText->setText(xmlStr);
}
void MainWindow::clickedClearButton(){
    ui->outXmlText->clear();
}

void MainWindow::clickedGetDataButton(){
    plainXMLStr = ui->outXmlText->toPlainText();
    xmlTestStr = dataXML::xmlStrRead(plainXMLStr);
    ui->inXmlText->setText(xmlTestStr);
}

void MainWindow::clickedClear2Button(){
    ui->inXmlText->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

