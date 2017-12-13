/*
* Copyright (c) 2010, 武汉华中数控股份有限公司开发二部
* All rights reserved.
* 
* 文件名称：ladwork.h
* 文件标识：梯形图操作
* 摘    要：
* 运行平台：
* 
* 版    本：1.00
* 作    者：王旭
* 日    期：
* 说    明：
*/

#ifndef __LAD_WORK_H__
#define __LAD_WORK_H__

#include <stdio.h>
#include <memory.h>
#include <string.h>

#include "hncdatatype.h"
#include "lad_def.h"
#include "lad_file.h"
#include "ladtbl.h"

#define MAX_SEL_ROW 30

extern SLadRow* ladwork_get_row_ptr(Bit32 r, Bit8 flag = 0);
extern void ladwork_init();
extern SLadCell* ladwork_get_cell_ptr(Bit32 r, Bit32 c);
extern Bit8 ladwork_del_row(Bit32 br, Bit32 er);
extern Bit8 ladwork_copy_row(Bit32 br, Bit32 er);
extern Bit8 ladwork_paste_row(Bit32 br, Bit32 n);
extern Bit8 ladwork_paste_row(Bit32 br);
extern Bit8 ladwork_add_row();
extern Bit8 ladwork_insert_row(Bit32 r, Bit32 n);
extern Bit8 ladwork_add_cell(uBit16 cmdID, Bit32 r, Bit32 c);
extern Bit8 ladwork_del_cell(Bit32 r, Bit32 c);
extern Bit8 ladwork_del_ver(Bit32 r, Bit32 c);
extern Bit8 ladwork_compile(Bit32* row, Bit32* col);
extern Bit8 ladwork_save();
extern Bit32 ladwork_get_max_row();
extern Bit32 ladwork_get_copy_row();
extern void ladwork_set_max_row(Bit32 n);
extern Bit8 ladwork_set_cell_parm(Bit8* str, Bit32 r, Bit32 c);
extern Bit8 ladwork_find_pre(Bit8 *str, Bit32 *row, Bit32 *col);
extern Bit8 ladwork_find_next(Bit8 *str, Bit32 *row, Bit32 *col);
extern Bit8 ladwork_reload();
extern Bit32 ladwork_get_change();

#endif
