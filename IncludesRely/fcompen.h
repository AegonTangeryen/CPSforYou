#ifndef _FCOMPEN_H_
#define _FCOMPEN_H_

#include "hncdatatype.h"

typedef struct _COMP_FILE_ERR
{
	Bit32 n; //出错行号
	Bit16 err_type; //出错类型
} CompFileErr;

//出错类型宏定义
#define COMP_FILE_NO_ERROR (0)         //无错误
#define COMP_FILE_OPEN_FAILED (-1)     //补偿文件打开失败
#define COMP_FILE_FORMAT_ERROR (-2)    //格式错误
#define COMP_FILE_DATA_ERROR (-3)      //数据错误

///////////////////////////////////////////////////////////////////////////////
//
//    Bit8 fcomp_vcp_load(Bit8 *path_name, CompFileErr *err_info)
//
//    功能：
//                  导入VCP空间误差补偿参数文件
//
//    参数：
//                  Bit8 *path_name：补偿参数文件路径
//		            CompFileErr *err_info：导入失败时返回出错信息，行号/出错类型
//    描述：
//
//    返回： 
//                  返回0：成功
//                  返回-1：失败
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
//    功能：
//                  导入螺距误差补偿参数文件
//
//    参数：
//                  Bit8 *path_name：补偿参数文件路径
//					ax：误差补偿的轴号
//		            CompFileErr *err_info：导入失败时返回出错信息，行号/出错类型
//    描述：
//
//    返回： 
//                  返回0：成功
//                  返回-1：失败
//
//////////////////////////////////////////////////////////////////////////
extern Bit32 fcom_pitch_err_comp_load(Bit8 *path_name, Bit32 ax, CompFileErr *errinfo);

#endif