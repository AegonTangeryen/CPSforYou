#ifndef _TRSPACKET_H_
#define _TRSPACKET_H_

//#include "fileread.h"
#include "eventdef.h"

typedef struct _DataHead
{
	Bit8 type;  
	Bit16 uDataLength;
}HeadPack;

#define HEAD_LEN 3
#define START_OF_FILE 1
#define DATA_OF_FILE 2
#define END_OF_FILE 3

#define Receive_R		(0x01)	//�����շ�״̬
#define Receive_NULL	(0x02)	//����Ϊ��
#define Receive_E		(0x03)	//�ļ��������
#define Receive_H		(0x04)	//���ļ���ͷ��ʼ����
#define Send_R			(0x05)	//�����շ�״̬
#define Send_E			(0x06)	//�ļ��������
#define Send_H			(0x07)	//���ļ���ͷ��ʼ����
#define Send_Q			(0x08)	//�ļ�����
#define Reset_Com_Stat	(0x09)	//������λ��״̬Ϊ����

#define PLC 1
// ·���ָ���
#ifdef _LINUX
#define DIR_SEPARATOR '/'
#else
#define DIR_SEPARATOR '\\'
#endif

extern Bit32 trspack_period();
extern Bit16 trspack_init();
extern Bit8 trspack_stat();
extern Bit16 trspack_exit();
#endif
