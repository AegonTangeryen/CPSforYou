#ifndef TOOLS_H
#define TOOLS_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QObject>
#include <QtNetwork>
#include <QMutex>
#include <QTimer>

QString unsignedhcar2HexQstring(unsigned char* array,int len);
int ConvertHexChar(char ch);
QByteArray QString2Hex(QString str);
bool writeFile(QString fileName, QString text);

#endif // TOOLS_H
