/*
* Copyright (c) 2013, 武汉华中数控股份有限公司
* All rights reserved.
* 
* 文件名称：hncmath.h
* 文件标识：根据配置管理计划书
* 摘    要：常用的浮点数运算
* 运行平台：linux/winxp
* 
* 版    本：1.00
* 作    者：刘涛
* 日    期：2013年8月13日
* 说    明：
*/

#ifndef __HNC_MATH_H__
#define __HNC_MATH_H__

#include "hncdatatype.h"

///////////////////////////////////////////////////////////////////////////////
//
//    Bit32 HNC_DoubleCompare(fBit64 first, fBit64 second)
//
//    功能：
//            浮点数比较
//
//    参数：
//            first ：第一个浮点数；
//            second ：第二个浮点数；
//
//    描述：
//            
//
//    返回：
//            1：first大于second；0：相等；-1：first小于second；
//
//////////////////////////////////////////////////////////////////////////
extern Bit32 HNC_DoubleCompare(fBit64 first, fBit64 second);

///////////////////////////////////////////////////////////////////////////////
//
//    Bit64 HNC_DoubleToLong(fBit64 f)
//
//    功能：
//            将浮点型转换成长整型
//
//    参数：
//            f：待转换的浮点数；          
//    描述：
//            
//
//    返回：
//            转换后的整数；
//
//////////////////////////////////////////////////////////////////////////
extern Bit64 HNC_DoubleToLong(fBit64 f);

#endif // __HNC_MATH_H__
