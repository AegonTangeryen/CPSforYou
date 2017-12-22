/*
* Copyright (c) 2011, 武汉华中数控股份有限公司软件开发部
* All rights reserved.
* 
* 文件名称：ncassert.h
* 文件标识：根据配置管理计划书
* 摘    要：自定义断言
*           1 格式：
*             NC Assertion failed: <expr>, file <filename>, line <lineno>
*           2 使用：
*             NDEBUG关闭，_DEBUG打开；
* 运行平台：linux/winxp
* 
* 版    本：1.00
* 作    者：刘涛
* 日    期：2011年12月5日
* 说    明：Linux平台的assert无法正常退出到后台
*/

#ifndef __NC_ASSERT_H__
#define __NC_ASSERT_H__

///////////////////////////////////////////////////////////////////////////////
//
//    void nc_assert_print(Bit8 *expr, Bit8 *filename, Bit32 lineno)
//
//    功能：
//            显示断言信息
//
//    参数：
//            expr ：表达式；
//            filename ：文件名；
//            lineno ：行号；
//
//    描述：
//            
//
//    返回：
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
