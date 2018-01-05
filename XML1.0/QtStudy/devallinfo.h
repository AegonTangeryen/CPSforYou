#ifndef DEVALLINFO_H
#define DEVALLINFO_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QMapIterator>

#define FBG_CHANNEL 32		//FBG通道个数
#define FBG_NODE 30         //FBG节点个数

#define CCD_DIMENSION 3     //CCD维度
#define CNC_DIMENSION 16    //CNC维度
#define DSB_DIMENSION 52    //DSB维度

#define CLOUD_URLS_DIMENSION 2  //服务器URLS命令维度

typedef struct
{
    QString CCDkey[CCD_DIMENSION] = {"X", "Y", "Z"};
    QMap<QString, QString> CCDdata;
}CCDinfoTypeDef;    //CCD信息结构体

typedef struct
{
    QString CNCkey[CNC_DIMENSION] = {"CH", "XPOS", "YPOS", "ZPOS", "MAPOS", "XPWR", "YPWR", "ZPWR", "ZPWR", "XFU", "YFU", "ZFU", "MAFU", "FR", "SP", "PA"};
    QMap<QString, QString> CNCdata;
}CNCinfoTypeDef;     //CNC信息结构体

typedef struct
{
    QString FBGchannelKey[FBG_CHANNEL] = {"CH00-", "CH01-", "CH02-", "CH03-", "CH04-", "CH05-", "CH06-", "CH07-", "CH08-", "CH09-", "CH10-", "CH11-", "CH12-", "CH13-", "CH14-", "CH15-", "CH16-", "CH17-", "CH18-", "CH19-", "CH20-", "CH21-", "CH22-", "CH23-","CH24-", "CH25-", "CH26-", "CH27-", "CH28-", "CH29-", "CH30-", "CH31-"};
    QString FBGnodeKey[FBG_NODE] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"};
    QMap<QString, QString> FBGdata;
}FBGinfoTypeDef;     //FBG信息结构体

typedef struct
{
    QString DSBkey[DSB_DIMENSION] = {"ID28ffcdfa001604cb", "ID28ff7eeda0160301", "ID28ffa203011604fc", "ID28ffd7cc0016044b", "ID28ff6ba7a0160589", "ID28ff28f8041603d9", "ID28ff280c01160410", "ID28ff4a2305160375", "ID28ffaf1fb2150108", "ID28ff921db2150167", "ID28ff86eb041603f8", "ID28ffd3dd041603fe", "ID28ff71c100160479", "ID28ffb81cb2150311", "ID28ff6a0c0116047a", "ID28ffa2dd00160443", "ID28ff1d93a01603e3", "ID28ff78bea01603cd", "ID28ff4ec300160495", "ID28ffaddc001604a3", "ID28ffb6e500160474", "ID28ffa3f7001604e5", "ID28ff30f70016041c", "ID28ff95f7001604fd", "ID28ffe6ce00160405", "ID28ff783db215044f", "ID28ff52c600160449", "ID28ffed30b2150334", "ID28ffdcc20016042e", "ID28ffd827b215045f", "ID28ff3425051603b3", "ID28ff247eb2150310", "ID28ff76e500160456", "ID28ffa5c30016043f", "ID28ff2d22b2150195", "ID28ffcd0d01160497", "ID28ff55a7a01605af", "ID28ff56d7001604e1", "ID28ff3ccba0160491", "ID28ff0091a01604f7", "ID28ff80efa01605df", "ID28ffd7c6a0160325", "ID28ff04ada01605ec", "ID28fffdd4a0160582", "ID28ff87caa0160421", "ID28ff1d9da0160475", "ID28fffdada01605b9", "ID28ff44d3a01605b8", "ID28ff538da0160406", "ID28ff387da0160416", "ID28ffcacfa01605fb", "ID28ff16a8a0160592"};
    QMap<QString, QString> DSBdata;
}DSBinfoTypeDef;     //DS18B20信息结构体

typedef struct
{
    QString time;
    QString macId;
    QString msg;
}HeadinfoTypeDef;    //XML <head>信息结构体

typedef struct
{
    QString cloudURLSkey[CLOUD_URLS_DIMENSION] = {"MODELBIN", "HBASE"};
    QMap<QString, QString> cloudURLS;
    QString cloudCMDS;
}CloudinfoTypeDef;   //XML <urls>, <cmds>信息结构体

typedef struct
{
    HeadinfoTypeDef headInfo;
    CCDinfoTypeDef  ccdInfo;
    CNCinfoTypeDef  cncInfo;
    FBGinfoTypeDef  fbgInfo;
    DSBinfoTypeDef  dsbInfo;
    CloudinfoTypeDef cloudInfo;
}DataInfoTypeDef;    //所有信息汇总

extern DataInfoTypeDef dataInfo;

class devAllInfo : public QObject
{
    Q_OBJECT

public:
    explicit devAllInfo(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DEVALLINFO_H
