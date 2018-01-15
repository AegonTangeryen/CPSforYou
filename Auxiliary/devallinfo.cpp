#include "devallinfo.h"

DataInfoTypeDef dataInfo;
devAllInfo::devAllInfo(QObject *parent) : QObject(parent)
{
    //信息初始化
    dataInfo.headInfo.time = "2017-12-25-18:00:00";
    dataInfo.headInfo.macId = "54EE75A6E578";
    dataInfo.headInfo.msg = "WuZhong";
    for(int i = 0; i < CCD_DIMENSION; i++){
        dataInfo.ccdInfo.CCDdata.insert(dataInfo.ccdInfo.CCDkey[i], "1111.111");
    }

    for(int i = 0; i < CNC_DIMENSION; i++){
        dataInfo.cncInfo.CNCdata.insert(dataInfo.cncInfo.CNCkey[i], "1111.111");
    }

    for(int i = 0; i < DSB_DIMENSION; i++){
        dataInfo.dsbInfo.DSBdata.insert(dataInfo.dsbInfo.DSBkey[i], "1111.111");
    }

    QString temp1;
    QString temp2;
    for(int i = 0; i < FBG_CHANNEL; i++){
        for(int j = 0; j < FBG_NODE; j++){
            temp1 = dataInfo.fbgInfo.FBGchannelKey[i];
            temp2 = temp1.append(dataInfo.fbgInfo.FBGnodeKey[j]);
            dataInfo.fbgInfo.FBGdata.insert(temp2, "1111.111");
        }
    }

    for(int i = 0; i < CLOUD_URLS_DIMENSION; i++){
        dataInfo.cloudInfo.cloudURLS.insert(dataInfo.cloudInfo.cloudURLSkey[i], "http://1111.zip");
    }
    dataInfo.cloudInfo.cloudCMDS = "No cmds";
}
