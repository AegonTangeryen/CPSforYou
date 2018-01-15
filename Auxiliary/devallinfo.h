#ifndef DEVALLINFO_H
#define DEVALLINFO_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QMapIterator>

#define FBG_CHANNEL 32		//FBG通道个数
#define FBG_NODE 20         //FBG节点个数
#define CCD_DIMENSION 3     //CCD维度
#define CNC_DIMENSION 16    //CNC维度
#define DSB_DIMENSION 126    //DSB维度
#define CLOUD_URLS_DIMENSION 2  //服务器URLS命令维度

typedef struct
{
    QString CCDkey[CCD_DIMENSION] = {"X", "Y", "Z"};
    QMap<QString, QString> CCDdata;
}CCDinfoTypeDef;    //CCD信息结构体

typedef struct
{
    QString CNCkey[CNC_DIMENSION] = {"CH", "XPOS", "YPOS", "ZPOS", "MAPOS", "XPWR", "YPWR", "ZPWR", "MAPWR", "XFU", "YFU", "ZFU", "MAFU", "FR", "SP", "PA"};
    QMap<QString, QString> CNCdata;
}CNCinfoTypeDef;     //CNC信息结构体

typedef struct
{
    QString FBGchannelKey[FBG_CHANNEL] = {"CH01-", "CH02-", "CH03-", "CH04-", "CH05-", "CH06-", "CH07-", "CH08-", "CH09-", "CH10-", "CH11-", "CH12-", "CH13-", "CH14-", "CH15-", "CH16-", "CH17-", "CH18-", "CH19-", "CH20-", "CH21-", "CH22-", "CH23-","CH24-", "CH25-", "CH26-", "CH27-", "CH28-", "CH29-", "CH30-", "CH31-","CH32-"};
    QString FBGnodeKey[FBG_NODE] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
    QMap<QString, QString> FBGdata;
}FBGinfoTypeDef;     //FBG信息结构体

typedef struct
{
    QString DSBkey[DSB_DIMENSION] = {"ID28ffcdfa001604cb","ID28ff7eeda0160301","ID28ffa203011604fc","ID28ffd7cc0016044b","ID28ff6ba7a0160589","ID28ff28f8041603d9","ID28ff280c01160410","ID28ff4a2305160375","ID28ffaf1fb2150108","ID28ff921db2150167","ID28ff86eb041603f8","ID28ffd3dd041603fe","ID28ff71c100160479","ID28ffb81cb2150311","ID28ff6a0c0116047a","ID28ffa2dd00160443","ID28ff1d93a01603e3","ID28ff78bea01603cd","ID28ff4ec300160495","ID28ffaddc001604a3","ID28ffb6e500160474","ID28ffa3f7001604e5","ID28ff30f70016041c","ID28ff95f7001604fd","ID28ffe6ce00160405","ID28ff783db215044f","ID28ff52c600160449","ID28ffed30b2150334","ID28ffdcc20016042e","ID28ffd827b215045f","ID28ff3425051603b3","ID28ff247eb2150310","ID28ff76e500160456","ID28ffa5c30016043f","ID28ff2d22b2150195","ID28ffcd0d01160497","ID28ff55a7a01605af","ID28ff56d7001604e1","ID28ff3ccba0160491","ID28ff0091a01604f7","ID28ff80efa01605df","ID28ffd7c6a0160325","ID28ff04ada01605ec","ID28fffdd4a0160582","ID28ff87caa0160421","ID28ff1d9da0160475","ID28fffdada01605b9","ID28ff44d3a01605b8","ID28ff538da0160406","ID28ff387da0160416","ID28ffcacfa01605fb","ID28ff16a8a0160592","ID285c7ac7060000f3","ID28ffafd9531704fa","ID28ffd7da53170421","ID28fffaee53170473","ID28ff0524541704e2","ID28fff1f05317042e","ID28ff2e4d54170469","ID28ff5ada53170406","ID28ffd8ea53170406","ID28ff65f153170409","ID28ff1600541704ae","ID28ff77325417043d","ID28ff01d8531704e4","ID28ff0048531704c8","ID28ffa64754170487","ID28ffb6d35317046e","ID28ff4045541704c6","ID28ffd41c54170425","ID28ff2deb531704fd","ID28ff66da531704a3","ID28ff48da531704f9","ID28ff643354170480","ID28ffe44b53170485","ID28ffed1054170440","ID28ffda43541704c5","ID28ff50f15317045f","ID28fffa4754170433","ID28ff16ee53170488","ID28ffe9d7601704a0","ID28ff0a1a541704d0","ID28ffbb46531704e2","ID28ff011f54170421","ID28fff1495317042c","ID28ffade553170423","ID28ff62d8531704bb","ID28ff8631541704de","ID28ff3bff5317042b","ID28ff90d85317049e","ID28ff041a54170472","ID28fff1d853170442","ID28ffe0fa53170484","ID28fff1125417041a","ID28ff971f5417040a","ID28ffa22654170487","ID28ff3c1b54170447","ID28ff2f3c54170483","ID28fff7d953170451","ID28ff5af1531704e2","ID28ffe04e54170461","ID28ff6f33541704f0","ID28ff6524541704f3","ID28ff582554170414","ID28ff56ef531704ee","ID28ff59025417042f","ID28ffcded5317042e","ID28ff533f5317043d","ID28fffa01541704da","ID28ff7331541704aa","ID28ff07ff5317048e","ID28ffd61d54170429","ID28ff942054170496","ID28ff1a2154170470","ID28ffae4e5417042a","ID28ffc83c54170408","ID28ff6fde5317045e","ID28ffe0d753170469","ID28fffd46541704ed","ID28ff393254170476","ID28ffe37053170408","ID28ff4fd953170420","ID28f3deee050000a0","ID28ff401e0516031d","ID28ff2cf700160441","ID28ff7cff001604c8"};
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

extern DataInfoTypeDef dataInfo;  // 全局变量，信息汇总

class devAllInfo : public QObject
{
    Q_OBJECT

public:
    explicit devAllInfo(QObject *parent = nullptr);
};

#endif // DEVALLINFO_H
