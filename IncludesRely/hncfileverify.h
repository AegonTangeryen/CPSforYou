/*
* Copyright (c) 2013, 武汉华中数控股份有限公司
* All rights reserved.
* 
* 文件名称：hncfileverify.h
* 文件标识：根据配置管理计划书
* 摘    要：文件校验、标准文件头
* 运行平台：linux/winxp
* 
* 版    本：1.00
* 作    者：HNC-8 Team
* 日    期：2013年8月16日
* 说    明：
*/

#ifndef __HNC_FILE_VERIFY_H__
#define __HNC_FILE_VERIFY_H__

#include <stdio.h>

#include "hncdatatype.h"

typedef struct _FileHead
{
	Bit8 fileFlag[4];		//	文件标示码，例如：刀具TDATA.DAT文件为TOOL
	Bit32 version;			//	文件版本号，例如：V1.01.13为010113
	Bit32 fileInfoAddr;		//	文件信息头起始地址
	Bit32 fileDataAddr;		//	文件数据起始地址
	Bit32 verifyType;		//	文件校验方法，MD5、CRC、校验和、无校验
	Bit32 verifyCode[8];	//	文件校验码
	Bit32 reserve[32];		//	保留
} FileHead;

enum
{
	NO_VER = 0,	//	无校验
	MD5_VER,	//	MD5校验
	CRC_VER,	//	CRC校验
	SUM_VER,	//	校验和校验
};

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 HNC_FileVerifyCrc32Str(Bit8 *buf, Bit32 len)
//
//    功能：
//            取字符串的CRC32的校验码
//
//    参数：
//            buf		：字符串地址；
//            len		：字符串长度；
//
//    描述：
//
//    返回：
//            返回校验码；
//
///////////////////////////////////////////////////////////////////////////////
extern Bit32 HNC_FileVerifyCrc32Str(Bit8 *buf, Bit32 len);

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 HNC_FileVerifyCrc32File(FILE *fp)
//
//    功能：
//            取文件的CRC32的校验码
//
//    参数：
//            fp		：文件指针；
//
//    描述：
//			  1、本函数执行完后，文件指针位置恢复到函数调用之前位置；
//			  2、本接口校验的文件必须为文件头为FileHead的二进制文件
//			  3、fp的打开方式，必须带读文件方式。读文件可用"rb"，写文件可用"wb+"
//
//    返回：
//            返回校验码；
//
///////////////////////////////////////////////////////////////////////////////
extern Bit32 HNC_FileVerifyCrc32File(FILE *fp);

///////////////////////////////////////////////////////////////////////////////
//
//    void HNC_FileVerifyMd5Str(Bit8 *srcStr, Bit8 *md5Str)
//
//    功能：
//            获取字符串的md5码
//
//    参数：
//            srcStr ：源字符串；
//            md5Str ：输出参数，md5码字符串；
//
//    描述：
//            
//
//    返回：
//            
//
//////////////////////////////////////////////////////////////////////////
extern void HNC_FileVerifyMd5Str(Bit8 *srcStr, Bit8 *md5Str);

///////////////////////////////////////////////////////////////////////////////
//
//    void HNC_FileVerifyGetMd5File(const Bit8 *srcFile, Bit8 *md5File)
//
//    功能：
//            获取文件的md5码
//
//    参数：
//            srcFile ：文件路径；
//            md5File ：输出参数，md5码字符串；
//
//    描述：
//            
//
//    返回：
//            
//
//////////////////////////////////////////////////////////////////////////
extern void HNC_FileVerifyGetMd5File(const Bit8 *srcFile,Bit8 *md5File);

#endif // __HNC_FILE_VERIFY_H__
