#include "tools.h"

//字符数组转成Qstring
QString unsignedhcar2HexQstring(unsigned char* array,int len)
{
    QString hexQstring;
    for(int j=0;j<len;j++)
    {
        if(array[j]<16) //防止0x0a转换成'a',要的是转换成'0a'
        hexQstring+='0'+QString::number(array[j], 16);
        else hexQstring+=QString::number(array[j], 16);
    }
    return hexQstring;
}

//将1-9 a-f字符转化为对应的整数
int ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
    return ch-'0';
    else if((ch >= 'A') && (ch <= 'F'))
    return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
    return ch-'a'+10;
    else return (-1);
}

//将字符型进制转化为16进制
 QByteArray QString2Hex(QString str)
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len;)
    {
        hstr=str[i].toLatin1();   //字符型
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len) break;

        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16)) break;
        else
        hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);

    return senddata;
}

//以追加的方式记录数据
bool writeFile(QString fileName, QString text)
{
    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Open failed.";
        return false;
    }
    QTextStream txtOutput(&f);
    txtOutput << text<<"\n";
    f.close();
    return true;
}
