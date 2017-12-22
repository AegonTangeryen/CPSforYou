/*
* Copyright (c) 2013, �人�������عɷ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�hnckeygen.h
* �ļ���ʶ���������ù���ƻ���
* ժ    Ҫ��ע����������
* ����ƽ̨��linux/winxp
* 
* ��    ����1.01
* ��    �ߣ�����
* ��    �ڣ�2013��8��23��
* ˵    ������У���㷨����hncfileverify��
*/

#ifndef __HNC_KEY_GENERATOR_H__
#define __HNC_KEY_GENERATOR_H__

#include "hncdatatype.h"

////////////////////////////////////////////////////////////////////////
//
//	  void HNC_KeyGenSystem(Bit8 *szkey, uBit16 day, uBit16 time[3], Bit8 *szcode)
//
//    ���ܣ�
//					ͨ���������ַ����������������ע����
//
//    ������
//					Bit8* szkey��������ַ���
//                  uBit16 day��ע������
//                  uBit16 sztime[3]: ע��ʱ��
//                  Bit8* szcode�����ע���룬����24λ
//                 
//
//    ������
//                  
//
//	  ���أ�
//                  
//
////////////////////////////////////////////////////////////////////////
extern void HNC_KeyGenSystem(Bit8 *szkey, uBit16 day, uBit16 time[3], Bit8 *szcode);

////////////////////////////////////////////////////////////////////////
//
//	  void HNC_KeyGenGetInfo(Bit8 *szcode, Bit8 *szmd5, uBit16 *day, uBit16 time[3])
//
//    ���ܣ�
//					ͨ�����ע�����ȡmd5���ע������
//
//    ������
//					Bit8* szcode: �������ע����
//                  Bit8* szmd5: ���md5��
//                  uBit16* day: �������
//                  ubit16 time[3]: ʱ��
//                 
//
//    ������
//                  
//
//	  ���أ�
//                  
//
////////////////////////////////////////////////////////////////////////
extern void HNC_KeyGenGetInfo(Bit8 *szcode, Bit8 *szmd5, uBit16 *day, uBit16 time[3]);

////////////////////////////////////////////////////////////////////////
//
//	  void HNC_KeyGenOption(Bit8 *szkey, Bit32 index, Bit8 *szmd5)
//
//    ���ܣ�
//				    ͨ���������ַ�����ѡ������������ѡ����
//
//    ������
//					Bit8* szkey: ������ַ���
//                  uBit16 index: ����ѡ��������
//                  Bit8* szmd5: ���ѡ���룬16λ�ַ���
//                 
//
//    ������
//                  
//
//	  ���أ�
//                  
//
////////////////////////////////////////////////////////////////////////
extern void HNC_KeyGenOption(Bit8 *szkey, Bit32 index, Bit8 *szmd5);

#endif // __HNC_KEY_GENERATOR_H__
