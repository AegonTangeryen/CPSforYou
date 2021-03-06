#ifndef _PASSWD_H
#define _PASSWD_H

#include "hncdatatype.h"

//参数访问权限枚举定义
enum _PARA_RIGHT_
{
	NO_RIGHTS,		//无权限
	USER_RIGHTS,	//用户权限
	MAC_RIGHTS,		//机床厂家权限
	NC_RIGHTS,		//数控厂家权限
	RD_RIGHTS,		//开发人员权限
	VENDER_RIGHTS	//固化不可修改
};

////////////////////////////////////////////////////////////////////////
//
//   Bit32 passwd_get_rights(void)
//
//    功能：
//				获取参数管理权限
//
//    参数：
//			             
//
//    描述：
//
//	  返回：
//              参数访问权限
//              
//
/////////////////////////////////////////////////////////////////////////
Bit32 passwd_get_rights(void);

////////////////////////////////////////////////////////////////////////
//
//   void passwd_set_rights(Bit32 rights)
//
//    功能：
//				设置参数管理权限
//
//    参数：
//			    rights: 当前的参数访问权限         
//
//    描述：
//
//	  返回：
//              
//              
//
/////////////////////////////////////////////////////////////////////////
void passwd_set_rights(Bit32 rights);

////////////////////////////////////////////////////////////////////////
//
//    Bit32 passwd_init(void)
//
//    功能：
//				密码管理初始化
//
//    参数：
//			           
//
//    描述：
//
//	  返回：
//              0: 成功
//              1: 失败
//
/////////////////////////////////////////////////////////////////////////
Bit32 passwd_init(void);

////////////////////////////////////////////////////////////////////////
//
//    Bit32 passwd_check(const Bit8 *pass,Bit32 nLevel)
//
//    功能：
//				密码权限检查
//
//    参数：
//			    pass: 密码
//              nLevel: 对应的权限级别        
//
//    描述：
//
//	  返回：
//              权限级别
//             
//
/////////////////////////////////////////////////////////////////////////
Bit32 passwd_check(const Bit8 *pass,Bit32 nLevel);



////////////////////////////////////////////////////////////////////////
//
//    Bit32 passwd_change(const Bit8 *pass, const Bit32 posit)
//
//    功能：
//				密码修改
//
//    参数：
//			    pass: 密码
//              posit: 权限级别       
//
//    描述：
//
//	  返回：
//              0: 成功
//              1: 失败
//             
//
/////////////////////////////////////////////////////////////////////////
Bit32 passwd_change(const Bit8 *pass, const Bit32 posit);


////////////////////////////////////////////////////////////////////////
//
//    Bit32 passwd_save()
//
//    功能：
//				密码保存
//
//    参数：
//			           
//
//    描述：
//
//	  返回：
//              0: 成功
//              1: 失败
//
/////////////////////////////////////////////////////////////////////////
Bit32 passwd_save();

#endif