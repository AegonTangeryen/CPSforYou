#ifndef _FCOMPEN_H_
#define _FCOMPEN_H_

#include "hncdatatype.h"

typedef struct _COMP_FILE_ERR
{
	Bit32 n; //�����к�
	Bit16 err_type; //��������
} CompFileErr;

//�������ͺ궨��
#define COMP_FILE_NO_ERROR (0)         //�޴���
#define COMP_FILE_OPEN_FAILED (-1)     //�����ļ���ʧ��
#define COMP_FILE_FORMAT_ERROR (-2)    //��ʽ����
#define COMP_FILE_DATA_ERROR (-3)      //���ݴ���

///////////////////////////////////////////////////////////////////////////////
//
//    Bit8 fcomp_vcp_load(Bit8 *path_name, CompFileErr *err_info)
//
//    ���ܣ�
//                  ����VCP�ռ����������ļ�
//
//    ������
//                  Bit8 *path_name�����������ļ�·��
//		            CompFileErr *err_info������ʧ��ʱ���س�����Ϣ���к�/��������
//    ������
//
//    ���أ� 
//                  ����0���ɹ�
//                  ����-1��ʧ��
//
//////////////////////////////////////////////////////////////////////////
Bit8 fcomp_vcp_load(Bit8 *path_name, CompFileErr *err_info);


#define FILE_LOAD_OK			(0)
#define PARM_ERR				(-1)
#define FILE_OPEN_FAILED		(-2)
#define FILE_FORMAT_ERROR		(-3)
#define COMP_NUM_NOT_MATCH		(-4)

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 fcom_pitch_err_comp_load(Bit8 *path_name, Bit32 ax, CompFileErr *errinfo)
//
//    ���ܣ�
//                  �����ݾ����������ļ�
//
//    ������
//                  Bit8 *path_name�����������ļ�·��
//					ax�����������
//		            CompFileErr *err_info������ʧ��ʱ���س�����Ϣ���к�/��������
//    ������
//
//    ���أ� 
//                  ����0���ɹ�
//                  ����-1��ʧ��
//
//////////////////////////////////////////////////////////////////////////
extern Bit32 fcom_pitch_err_comp_load(Bit8 *path_name, Bit32 ax, CompFileErr *errinfo);

#endif