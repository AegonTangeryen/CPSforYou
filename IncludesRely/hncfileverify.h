/*
* Copyright (c) 2013, �人�������عɷ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�hncfileverify.h
* �ļ���ʶ���������ù���ƻ���
* ժ    Ҫ���ļ�У�顢��׼�ļ�ͷ
* ����ƽ̨��linux/winxp
* 
* ��    ����1.00
* ��    �ߣ�HNC-8 Team
* ��    �ڣ�2013��8��16��
* ˵    ����
*/

#ifndef __HNC_FILE_VERIFY_H__
#define __HNC_FILE_VERIFY_H__

#include <stdio.h>

#include "hncdatatype.h"

typedef struct _FileHead
{
	Bit8 fileFlag[4];		//	�ļ���ʾ�룬���磺����TDATA.DAT�ļ�ΪTOOL
	Bit32 version;			//	�ļ��汾�ţ����磺V1.01.13Ϊ010113
	Bit32 fileInfoAddr;		//	�ļ���Ϣͷ��ʼ��ַ
	Bit32 fileDataAddr;		//	�ļ�������ʼ��ַ
	Bit32 verifyType;		//	�ļ�У�鷽����MD5��CRC��У��͡���У��
	Bit32 verifyCode[8];	//	�ļ�У����
	Bit32 reserve[32];		//	����
} FileHead;

enum
{
	NO_VER = 0,	//	��У��
	MD5_VER,	//	MD5У��
	CRC_VER,	//	CRCУ��
	SUM_VER,	//	У���У��
};

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 HNC_FileVerifyCrc32Str(Bit8 *buf, Bit32 len)
//
//    ���ܣ�
//            ȡ�ַ�����CRC32��У����
//
//    ������
//            buf		���ַ�����ַ��
//            len		���ַ������ȣ�
//
//    ������
//
//    ���أ�
//            ����У���룻
//
///////////////////////////////////////////////////////////////////////////////
extern Bit32 HNC_FileVerifyCrc32Str(Bit8 *buf, Bit32 len);

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 HNC_FileVerifyCrc32File(FILE *fp)
//
//    ���ܣ�
//            ȡ�ļ���CRC32��У����
//
//    ������
//            fp		���ļ�ָ�룻
//
//    ������
//			  1��������ִ������ļ�ָ��λ�ûָ�����������֮ǰλ�ã�
//			  2�����ӿ�У����ļ�����Ϊ�ļ�ͷΪFileHead�Ķ������ļ�
//			  3��fp�Ĵ򿪷�ʽ����������ļ���ʽ�����ļ�����"rb"��д�ļ�����"wb+"
//
//    ���أ�
//            ����У���룻
//
///////////////////////////////////////////////////////////////////////////////
extern Bit32 HNC_FileVerifyCrc32File(FILE *fp);

///////////////////////////////////////////////////////////////////////////////
//
//    void HNC_FileVerifyMd5Str(Bit8 *srcStr, Bit8 *md5Str)
//
//    ���ܣ�
//            ��ȡ�ַ�����md5��
//
//    ������
//            srcStr ��Դ�ַ�����
//            md5Str �����������md5���ַ�����
//
//    ������
//            
//
//    ���أ�
//            
//
//////////////////////////////////////////////////////////////////////////
extern void HNC_FileVerifyMd5Str(Bit8 *srcStr, Bit8 *md5Str);

///////////////////////////////////////////////////////////////////////////////
//
//    void HNC_FileVerifyGetMd5File(const Bit8 *srcFile, Bit8 *md5File)
//
//    ���ܣ�
//            ��ȡ�ļ���md5��
//
//    ������
//            srcFile ���ļ�·����
//            md5File �����������md5���ַ�����
//
//    ������
//            
//
//    ���أ�
//            
//
//////////////////////////////////////////////////////////////////////////
extern void HNC_FileVerifyGetMd5File(const Bit8 *srcFile,Bit8 *md5File);

#endif // __HNC_FILE_VERIFY_H__
