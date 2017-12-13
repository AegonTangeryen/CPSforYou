#ifndef WRITEXML_H
#define WRITEXML_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QtXml\QtXml>
#include <QtXml\QDomDocument>
#include <QMapIterator>
#include "devallinfo.h"

class dataXML : public QObject
{
    Q_OBJECT

public:
    explicit dataXML(QObject *parent = nullptr);
    static QString xmlStrCreat(DataInfoTypeDef _dataInfo);
    static QString xmlStrRead(QString xmlstr);
    static QMap<QString, QString> xmlFindKeyValue(QDomNode _node);
};

#endif // WRITEXML_H
