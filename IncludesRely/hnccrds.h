/*
* Copyright (c) 2013, �人�������عɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�hnccrds.h
* �ļ���ʶ���������ù����ƻ���
* ժ    Ҫ��ͨ�����ݽӿ�
* ����ƽ̨��Linux/Windows
*
* ��    ����1.00
* ��    �ߣ�HNC-8 Team
* ��    �ڣ�2013��7��17��
* ˵    ��������ֵ˵����
*           0���ɹ���
*           -1���������벻��ȷ��
*           -2���ӿڲ��ṩ�ù��ܣ�
*/

#ifndef __HNC_CRDS_H__
#define __HNC_CRDS_H__

#include "hncdatatype.h"

// ����ϵ��������
// δ��ע���͵���Bit32
enum HncCRDS
{
	HNC_CRDS_CH_G5X_ZERO = 0, // ָ��ͨ��������ϵ���
	HNC_CRDS_CH_G5X_ID,       // ָ��ͨ��������ϵID
	HNC_CRDS_CH_WCS_ZERO,     // ָ��ͨ���Ṥ������ϵ���
	HNC_CRDS_CH_REL_ZERO,     // ָ��ͨ�����������ϵ���
	HNC_CRDS_CH_FRAME_ZERO,   // ָ��ͨ�����������ϵ���
	HNC_CRDS_G68_PNT1,        // ��������ϵ������1����
	HNC_CRDS_G68_PNT2,        // ��������ϵ������2����
	HNC_CRDS_G68_ZERO,        // ��������ϵ���
	HNC_CRDS_G68_VCT,         // ��������ϵ���� fBit64
	HNC_CRDS_CH_G5X_OFFSET_ZERO,  //ָ��ͨ��������ϵƫ�����
	HNC_CRDS_TOTAL
};

//	ȡϵͳ����ĸ�������ϵ��Ŀ
enum HncCrdsMaxNum
{
	G5EXT_MAX_NUM,		//	G54.X��չ����ϵ����Ŀ
	CHG_WCS_MAX_NUM,	//	��������ʱ����ʱ��������ϵ��Ŀ
	TCS_MAX_NUM			//	TCS����ϵ��Ŀ
};

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 HNC_CrdsGetValue(Bit32 type, Bit32 ax, void *value, Bit32 ch, Bit32 crds, Bit16 clientNo)
//
//    ���ܣ�
//            ��ȡ����ϵ���ݵ�ֵ
//
//    ������
//            type		������ϵ���ݵ����ͣ�
//            ax		����ţ�
//            value		������ϵ���ݵ�ֵ��
//            ch		��ͨ���ţ�
//            crds		������ϵ��ţ�
//            clientNo	���������Ӻţ�
//
//    ������
//
//
//    ���أ�
//            0���ɹ�����0��ʧ�ܣ��μ�����ֵ˵����
//
//////////////////////////////////////////////////////////////////////////
HNCAPI Bit32 HNC_CrdsGetValue(Bit32 type, Bit32 ax, void *value, Bit32 ch = -1, Bit32 crds = -1, Bit16 clientNo = 0);

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 HNC_CrdsSetValue(Bit32 type, Bit32 ax, void *val, Bit32 ch, Bit32 crds, Bit16 clientNo)
//
//    ���ܣ�
//            ��������ϵ���ݵ�ֵ
//
//    ������
//            type		������ϵ���ݵ����ͣ�
//            ax		����ţ�
//            value		������ϵ���ݵ�ֵ��
//            ch		��ͨ���ţ�
//            crds		������ϵ��ţ�
//            clientNo	���������Ӻţ�
//
//    ������
//
//
//    ���أ�
//            0���ɹ�����0��ʧ�ܣ��μ�����ֵ˵����
//
//////////////////////////////////////////////////////////////////////////
HNCAPI Bit32 HNC_CrdsSetValue(Bit32 type, Bit32 ax, void *val, Bit32 ch = -1, Bit32 crds = -1, Bit16 clientNo = 0);

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 HNC_CrdsGetMaxNum(HncCrdsMaxNum type)
//
//    ���ܣ�
//            ȡϵͳ����ĸ�������ϵ��Ŀ
//
//    ������
//
//    ������
//
//    ���أ�
//            -1����������������type��Ӧ������ϵ��Ŀ
//
//////////////////////////////////////////////////////////////////////////
HNCAPI Bit32 HNC_CrdsGetMaxNum(Bit32 type, Bit16 clientNo = 0);

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 HNC_CrdsLoad(void)
//
//    ���ܣ�
//            ����ϵ���ݴ��ļ�����
//
//    ������
//
//    ������
//            ��������ԭ�ļ������ԭ�ļ��𻵽����뱸���ļ�
//
//    ���أ�
//            0���ɹ���-1���ϴα�������ϵ�ļ����쳣,���ʵ����ϵ���ݣ�-2������ʧ��
//
//////////////////////////////////////////////////////////////////////////
HNCAPI Bit32 HNC_CrdsLoad(Bit16 clientNo = 0);

///////////////////////////////////////////////////////////////////////////////
//
//    void sys_crds_save(Bit16 clientNo)
//
//    ���ܣ�
//            �������ݱ���
//
//    ������
//
//    ������
//
//
//    ���أ�
//            0���ɹ���-1��ʧ�ܣ�
//
//////////////////////////////////////////////////////////////////////////
HNCAPI Bit32 HNC_CrdsSave(Bit16 clientNo = 0);

#endif // __HNC_CRDS_H__