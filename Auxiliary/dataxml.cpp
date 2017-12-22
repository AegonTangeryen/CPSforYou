#include "dataxml.h"

dataXML::dataXML(QObject *parent) : QObject(parent)
{

}

QMap<QString, QString> dataXML::xmlFindKeyValue(QDomNode _node){
    QDomElement e;
    QMap<QString, QString> tempMap;
    tempMap.clear();
    while(!_node.isNull()){
        e = _node.toElement();
         if(!e.isNull())
         {
             tempMap.insert(e.tagName(), e.text());
            qDebug()<<e.tagName() << ":" << e.text();
         }
         _node = _node.nextSibling();
     }
    return tempMap;
}

QString dataXML::xmlStrRead(QString xmlstr){
    QString str;    //信息键值对字符串
    QMap<QString, QString> receiveMap;  //接收键值对
    QDomDocument doc;
    doc.setContent(xmlstr);

    QDomElement root = doc.documentElement();//读取根节点
    QDomNode node, posNode;

    node = root.namedItem("head");   //定位到head节点
    if(!node.isNull()){
        posNode = node.firstChild();
        receiveMap.clear();
        receiveMap = dataXML::xmlFindKeyValue(posNode);

        QMapIterator<QString, QString> headIndex(receiveMap);
        while (headIndex.hasNext()) {
            headIndex.next();
            str = str.append(QString("%1: %2\n").arg(headIndex.key()).arg(headIndex.value()));
        }
    }

    node = root.namedItem("body").namedItem("data").namedItem("DEV001");    //定位到data/DEV001
    if(!node.isNull()){
        posNode = node.namedItem("DSB").firstChild();  //定位到DSB
        if(!posNode.isNull()){
            receiveMap.clear();
            receiveMap = dataXML::xmlFindKeyValue(posNode);

            QMapIterator<QString, QString> dsbIndex(receiveMap);
            while (dsbIndex.hasNext()) {
                dsbIndex.next();
               str = str.append(QString("%1: %2\n").arg(dsbIndex.key()).arg(dsbIndex.value()));
            }
        }
        posNode = node.namedItem("FBG").firstChild();   //定位到FBG
        if(!posNode.isNull()){
            receiveMap.clear();
            receiveMap = dataXML::xmlFindKeyValue(posNode);

            QMapIterator<QString, QString> fbgIndex(receiveMap);
            while (fbgIndex.hasNext()) {
                fbgIndex.next();
                str = str.append(QString("%1: %2\n").arg(fbgIndex.key()).arg(fbgIndex.value()));
            }
        }
        posNode = node.namedItem("CCD").firstChild();   //定位到CCD
        if(!posNode.isNull()){
            receiveMap.clear();
            receiveMap = dataXML::xmlFindKeyValue(posNode);

            QMapIterator<QString, QString> ccdIndex(receiveMap);
            while (ccdIndex.hasNext()) {
                ccdIndex.next();
                str = str.append(QString("%1: %2\n").arg(ccdIndex.key()).arg(ccdIndex.value()));
            }
        }
    }

    node = root.namedItem("body").namedItem("urls").namedItem("DEV001");   //定位到urls/DEV001
    if(!node.isNull()){
        posNode = node.firstChild();
        if(!posNode.isNull()){
            receiveMap.clear();
             dataInfo.cloudInfo.cloudURLS.clear();
            receiveMap = dataXML::xmlFindKeyValue(posNode);
            dataInfo.cloudInfo.cloudURLS = receiveMap;//更新

            QMapIterator<QString, QString> urlsIndex(dataInfo.cloudInfo.cloudURLS);
            while (urlsIndex.hasNext()) {
                urlsIndex.next();
                str = str.append(QString("%1: %2\n").arg(urlsIndex.key()).arg(urlsIndex.value()));
            }
        }
    }

    node = root.namedItem("body").namedItem("cmds").namedItem("DEV001");   //定位到cmds/DEV001
    if(!node.isNull()){
        posNode = node.firstChild();
        if(!posNode.isNull()){
            receiveMap.clear();
             dataInfo.cloudInfo.cloudCMDS.clear();
            receiveMap = dataXML::xmlFindKeyValue(posNode);
            dataInfo.cloudInfo.cloudCMDS = receiveMap["CMD"];//更新
            str = str.append(QString("%1: %2\n").arg("CMD").arg(dataInfo.cloudInfo.cloudCMDS));
        }
    }
    return str;
}

QString dataXML::xmlStrCreat(DataInfoTypeDef _dataInfo){
    QDomDocument doc;
    QDomText dataText;  //写数据变量
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);

    QDomElement whutRoot = doc.createElement("whut");   //whut根目录
    doc.appendChild(whutRoot);

    QDomElement head = doc.createElement("head");    //head标签
    whutRoot.appendChild(head);

    QDomElement body = doc.createElement("body");    //body标签
    whutRoot.appendChild(body);

    /*head分支标签*/
    QDomElement time=doc.createElement("time");
    QDomElement id=doc.createElement("id");
    QDomElement msg=doc.createElement("msg");
    head.appendChild(time);
    head.appendChild(id);
    head.appendChild(msg);

    dataText = doc.createTextNode(_dataInfo.headInfo.time); //head标签数据填充
    time.appendChild(dataText);
    dataText = doc.createTextNode(_dataInfo.headInfo.macId);
    id.appendChild(dataText);
    dataText = doc.createTextNode(_dataInfo.headInfo.msg);
    msg.appendChild(dataText);

    /*body分支标签*/
    QDomElement data = doc.createElement("data");
    body.appendChild(data);

    QDomElement DEV001data = doc.createElement("DEV001");
    data.appendChild(DEV001data);

    /*DEV001data分支标签*/
    QDomElement DEV001dataDSB = doc.createElement("DSB");
    QDomElement DEV001dataFBG = doc.createElement("FBG");
    QDomElement DEV001dataCCD = doc.createElement("CCD");
    QDomElement DEV001dataCNC = doc.createElement("CNC");
    DEV001data.appendChild(DEV001dataDSB);
    DEV001data.appendChild(DEV001dataFBG);
    DEV001data.appendChild(DEV001dataCCD);
    DEV001data.appendChild(DEV001dataCNC);

    QMapIterator<QString, QString> ccdIndex(_dataInfo.ccdInfo.CCDdata);  //写CCD数据
    while (ccdIndex.hasNext()) {
        ccdIndex.next();
        QDomElement DEV001dataCcdKey = doc.createElement(ccdIndex.key());
        DEV001dataCCD.appendChild(DEV001dataCcdKey);
        dataText = doc.createTextNode(ccdIndex.value());
        DEV001dataCcdKey.appendChild(dataText);
    }

    QMapIterator<QString, QString> cncIndex(_dataInfo.cncInfo.CNCdata);  //写CNC数据
    while (cncIndex.hasNext()) {
        cncIndex.next();
        QDomElement DEV001dataCncKey = doc.createElement(cncIndex.key());
        DEV001dataCNC.appendChild(DEV001dataCncKey);
        dataText = doc.createTextNode(cncIndex.value());
        DEV001dataCncKey.appendChild(dataText);
    }

    QMapIterator<QString, QString> fbgIndex(_dataInfo.fbgInfo.FBGdata);  //写FBG数据
    while (fbgIndex.hasNext()) {
        fbgIndex.next();
        QDomElement DEV001dataFbgKey = doc.createElement(fbgIndex.key());
        DEV001dataFBG.appendChild(DEV001dataFbgKey);
        dataText = doc.createTextNode(fbgIndex.value());
        DEV001dataFbgKey.appendChild(dataText);
    }

    QMapIterator<QString, QString> dsbIndex(_dataInfo.dsbInfo.DSBdata);  //写DSB数据
    while (dsbIndex.hasNext()) {
        dsbIndex.next();
        QDomElement DEV001dataDsbKey = doc.createElement(dsbIndex.key());
        DEV001dataDSB.appendChild(DEV001dataDsbKey);
        dataText = doc.createTextNode(dsbIndex.value());
        DEV001dataDsbKey.appendChild(dataText);
    }

    QString xml = doc.toString();
    return xml;
}
