/*
* Copyright (c) 2011, �人�������عɷ����޹�˾���������
* All rights reserved.
* 
* �ļ����ƣ�ncassert.h
* �ļ���ʶ���������ù���ƻ���
* ժ    Ҫ���Զ������
*           1 ��ʽ��
*             NC Assertion failed: <expr>, file <filename>, line <lineno>
*           2 ʹ�ã�
*             NDEBUG�رգ�_DEBUG�򿪣�
* ����ƽ̨��linux/winxp
* 
* ��    ����1.00
* ��    �ߣ�����
* ��    �ڣ�2011��12��5��
* ˵    ����Linuxƽ̨��assert�޷������˳�����̨
*/

#ifndef __NC_ASSERT_H__
#define __NC_ASSERT_H__

///////////////////////////////////////////////////////////////////////////////
//
//    void nc_assert_print(Bit8 *expr, Bit8 *filename, Bit32 lineno)
//
//    ���ܣ�
//            ��ʾ������Ϣ
//
//    ������
//            expr �����ʽ��
//            filename ���ļ�����
//            lineno ���кţ�
//
//    ������
//            
//
//    ���أ�
//            
//
//////////////////////////////////////////////////////////////////////////
extern void nc_assert_print(char *exp, char *filename, int line);

#ifdef NDEBUG

#define nc_assert(exp)	((void)0)

#else

#define nc_assert(exp)	(void)((exp) || (nc_assert_print(#exp, __FILE__, __LINE__), 0))

#endif // NDEBUG

#endif // __NC_ASSERT_H__
