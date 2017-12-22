/*
* Copyright (c) 2013, 武汉华中数控股份有限公司
* All rights reserved.
* 
* 文件名称：hnckeygen.h
* 文件标识：根据配置管理计划书
* 摘    要：注册码生成器
* 运行平台：linux/winxp
* 
* 版    本：1.01
* 作    者：刘涛
* 日    期：2013年8月23日
* 说    明：将校验算法移入hncfileverify；
*/

#ifndef __HNC_KEY_GENERATOR_H__
#define __HNC_KEY_GENERATOR_H__

#include "hncdatatype.h"

////////////////////////////////////////////////////////////////////////
//
//	  void HNC_KeyGenSystem(Bit8 *szkey, uBit16 day, uBit16 time[3], Bit8 *szcode)
//
//    功能：
//					通过给定的字符串和天数生成软件注册码
//
//    参数：
//					Bit8* szkey：输入的字符串
//                  uBit16 day：注册天数
//                  uBit16 sztime[3]: 注册时间
//                  Bit8* szcode：输出注册码，长度24位
//                 
//
//    描述：
//                  
//
//	  返回：
//                  
//
////////////////////////////////////////////////////////////////////////
extern void HNC_KeyGenSystem(Bit8 *szkey, uBit16 day, uBit16 time[3], Bit8 *szcode);

////////////////////////////////////////////////////////////////////////
//
//	  void HNC_KeyGenGetInfo(Bit8 *szcode, Bit8 *szmd5, uBit16 *day, uBit16 time[3])
//
//    功能：
//					通过软件注册码获取md5码和注册天数
//
//    参数：
//					Bit8* szcode: 输入软件注册码
//                  Bit8* szmd5: 输出md5码
//                  uBit16* day: 输出天数
//                  ubit16 time[3]: 时间
//                 
//
//    描述：
//                  
//
//	  返回：
//                  
//
////////////////////////////////////////////////////////////////////////
extern void HNC_KeyGenGetInfo(Bit8 *szcode, Bit8 *szmd5, uBit16 *day, uBit16 time[3]);

////////////////////////////////////////////////////////////////////////
//
//	  void HNC_KeyGenOption(Bit8 *szkey, Bit32 index, Bit8 *szmd5)
//
//    功能：
//				    通过给定的字符串和选型索引号生成选型码
//
//    参数：
//					Bit8* szkey: 输入的字符串
//                  uBit16 index: 输入选型索引号
//                  Bit8* szmd5: 输出选型码，16位字符串
//                 
//
//    描述：
//                  
//
//	  返回：
//                  
//
////////////////////////////////////////////////////////////////////////
extern void HNC_KeyGenOption(Bit8 *szkey, Bit32 index, Bit8 *szmd5);

#endif // __HNC_KEY_GENERATOR_H__
