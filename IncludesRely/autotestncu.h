#ifndef _AUTOTEST_
#define _AUTOTEST_
#define _STR_BUF_SIZE 128
#define MAINSTEP_FLAG 0x00ff
#define SUBSTEP_FLAG  0xff00

#define  ERROR_NOFILE 0x1
#define  ERROR_NOMATCH 0x2
#define  ERROR_NOAll 0x4
#define  ERROR_ALARM 0x8

#define  DOUBLE_PREC 1.0e-3
#define  MAX_ERR_LINES 100

#ifdef _WIN32
#define  RETURN_CHAR  '\n'
#else
#define  RETURN_CHAR  '\r'
#endif

#define  MAX_CHECK_POINT_NUM 200
#define  MAX_TESTPROG_NUM 1000
#include "hncdatatype.h"

///////////////////////////////////////////////////////////////////////////////
//
//    Bit8 autotest_loop();
//
//    ���ܣ� 
//           �Զ�������ѭ��
//
//    ������
//            
//
//    ������
//           ϵͳ�������Ե��øú���ִ���Զ������Թ���  
//
//    ���أ�
//           
//           
////////////////////////////////////////////////////////////////////////////////
extern Bit8 autotest_loop(uBit16 key);



///////////////////////////////////////////////////////////////////////////////
//
//    Bit8 autotest_get_flag();
//
//    ���ܣ� 
//           ��ȡ�Զ������Ա�־
//
//    ������
//            
//
//    ������
//           
//
//    ���أ�
//           true  �����Զ�������
//           false ���Զ�������
////////////////////////////////////////////////////////////////////////////////
extern bool autotest_get_flag();


///////////////////////////////////////////////////////////////////////////////
//
//    Bit8 autotest_set_flag();
//
//    ���ܣ� 
//           �����Զ������Ա�־
//
//    ������
//            
//
//    ������
//           
//
//    ���أ�
//           
//           
////////////////////////////////////////////////////////////////////////////////
extern void autotest_set_flag();















#endif
