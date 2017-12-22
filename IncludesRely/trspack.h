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

#define Receive_R		(0x01)	//正常收发状态
#define Receive_NULL	(0x02)	//接收为空
#define Receive_E		(0x03)	//文件发送完毕
#define Receive_H		(0x04)	//从文件的头开始接收
#define Send_R			(0x05)	//正常收发状态
#define Send_E			(0x06)	//文件发送完毕
#define Send_H			(0x07)	//从文件的头开始发送
#define Send_Q			(0x08)	//文件请求
#define Reset_Com_Stat	(0x09)	//重置下位机状态为接收

#define PLC 1
// 路径分隔符
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
