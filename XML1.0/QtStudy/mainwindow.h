#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QString>
#include <QLayout>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString xmlStr;
    QString plainXMLStr;
    QString xmlTestStr ="<whut><head><time>20171106202122345</time><id>54EE75A6E578</id><msg>wuzhong</msg></head><body><data><DEV001><DSB><ID28ff28f8041603d9>20.00</ID28ff28f8041603d9><ID28ff280c01160410>21.11</ID28ff280c01160410><ID28ffa203011604fc>22.22</ID28ffa203011604fc></DSB><FBG><CH00-01>1551.456</CH00-01><CH00-02>1552.789</CH00-02></FBG><CCD><X>1.000</X><Y>2.000</Y><Z>3.000</Z></CCD><CNC><CH>1</CH><XPOS>2</XPOS><YPOS>3</YPOS><ZPOS>4</ZPOS><MAPOS>3.000</MAPOS><XPWR>3.000</XPWR><YPWR>3.000</YPWR><ZPWR>3.000</ZPWR><MAPWR>3.000</MAPWR><XFU>3.000</XFU><YFU>3.000</YFU><ZFU>3.000</ZFU><MAFU>3.000</MAFU><FR>3.000</FR><SP>3.000</SP><PA>Pause</PA></CNC></DEV001><DEV002><DSB><ID28ff28f8041603d9>20.00</ID28ff28f8041603d9><ID28ff280c01160410>21.11</ID28ff280c01160410><ID28ffa203011604fc>22.22</ID28ffa203011604fc></DSB><FBG><CH00-01>1551.456</CH00-01><CH00-02>1552.789</CH00-02></FBG></DEV002></data><urls><DEV001><MODELBIN>http://xxx.zip</MODELBIN><HBASE>http://xxx.zip</HBASE></DEV001></urls><cmds><DEV001><CMD>softupdate</CMD></DEV001></cmds></body></whut>";


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void clickedTranscodingButton();
    void clickedClearButton();
    void clickedGetDataButton();
    void clickedClear2Button();

private slots:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
