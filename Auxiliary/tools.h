#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QList>
#include <QString>
#include <QVector>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QtNetwork>
#include <QMutexLocker>
#include <QTimer>
#include <QNetworkInterface>
#include <QThread>
#include <windows.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "mmtimer.h"

#define MB (1024*1024)

QString unsignedhcar2HexQstring(unsigned char* array,int len);  // char转成十六进制QString
int ConvertHexChar(char ch);    // 转换大小写
QByteArray QString2Hex(QString str);            // Qstring转成十六进制
bool writeFile(QString fileName, QString text); // 写文件
QString getHostIpAddress();     // 获取本地IP
QString getHostMacAddress();    // 获取本机Mac地址
QStringList getSysMemory();     // 获取本机内存使用情况

#endif // TOOLS_H
