#ifndef __HNC_LAD_H__
#define __HNC_LAD_H__

#include "hncdatatype.h"
#include "lad_def.h"

#define CONNECT_NUM 8
typedef struct
{
	SLadRow* lad_row;//梯形图缓存区域
	Bit32 br;//梯形图缓存开始位置
	Bit32 ln;//梯形图有效行数
}LAD_AP;//梯形图缓存数据

enum LAD_CMD//数据命令
{
	LAD_STATUS,//元件实时状态
	LAD_ABLE_STATUS1,//通过行列访问元件强制状态
	LAD_ABLE_STATUS2,//通过命令号元件强制状态
	LAD_REG_STATUS,//元件寄存器实时数据，网络传输
	LAD_ROW,//获取元件数据
	LAD_SYMBOL,//获取符号表
	LAD_DEL_ROW,//删除行
	LAD_COPY_ROW,//复制行
	LAD_PASTE_ROW,//粘贴行
	LAD_ADD_ROW,//增加行
	LAD_INSERT_ROW,//插入行
	LAD_CHANGE_PARM,//修改参数
	LAD_ADD_CELL,//增加元件
	LAD_DEL_CELL,//删除元件
	LAD_CHANGE_FLAG,//梯形图修改标记
	LAD_COMPILE,//编译
	LAD_RELOAD,//重新载入
	LAD_SAVE,//保存
	LAD_DEL_VER,//删除竖线
	LAD_MAX_ROW,//获取梯形图最大行数
	LAD_COPY_NUM,//获取剪切板中的行数
	LAD_FIND,//查找，带字符串
	LAD_FIND_PRE,//向上继续查找，带当前位置
	LAD_FIND_NEXT,//向下查找，带当前位置
	LAD_SYMBOL_CHANGE,//修改符号表
	LAD_SYMBOL_FIND,//查找，带字符串
	LAD_SYMBOL_FIND_PRE,//向上继续查找，带当前位置
	LAD_SYMBOL_FIND_NEXT,//向下查找，带当前位置
};

extern void HNC_LadDisableBlk(Bit32 row, Bit32 col, Bit16 clientNo = 0);
extern void HNC_LadDisableBlk(Bit32 sub, Bit16 clientNo = 0);
extern void HNC_LadEnableBlk(Bit32 row, Bit32 col, Bit16 clientNo = 0);
extern void HNC_LadEnableBlk(Bit32 sub, Bit16 clientNo = 0);
extern void HNC_LadRestoreBlk(Bit32 row, Bit32 col, Bit16 clientNo = 0);
extern void HNC_LadRestoreBlk(Bit32 sub, Bit16 clientNo = 0);
extern uBit8 HNC_LadGetBlk(Bit32 row, Bit32 col, Bit16 clientNo = 0);
extern uBit8 HNC_LadGetBlk(Bit32 sub, Bit16 clientNo = 0);
//extern Bit8 *usr_get_view_pointer();

extern void HNC_LadInit(Bit32 n);
extern void HNC_LadUpdate(Bit32 br, Bit32 n, Bit16 clientNo = 0);
extern SLadRow* HNC_LadGetRowPtr(Bit32 r, Bit16 clientNo = 0);
extern void HNC_LadGetParaComment(SLadReg* p, Bit8* buf, Bit16 clientNo = 0);
extern Bit32 HNC_LadDelRow(Bit32 br, Bit32 er, Bit16 clientNo = 0);
extern Bit32 HNC_LadCopyRow(Bit32 br, Bit32 er, Bit16 clientNo = 0);
extern Bit32 HNC_LadPasteRow(Bit32 br, Bit16 clientNo = 0);
extern Bit32 HNC_LadAddRow(Bit32 br, Bit32 rn, Bit16 clientNo = 0);
extern Bit32 HNC_LadInsertRow(Bit32 br, Bit32 rn, Bit16 clientNo = 0);
extern Bit32 HNC_LadAddCell(uBit16 cmdID, Bit32 r, Bit32 c, Bit16 clientNo = 0);
extern Bit32 HNC_LadDelCell(Bit32 r, Bit32 c, Bit16 clientNo = 0);
extern Bit32 HNC_LadDelVer(Bit32 r, Bit32 c, Bit16 clientNo = 0);
extern Bit32 HNC_LadCompile(Bit32* row, Bit32* col, Bit16 clientNo = 0);
extern Bit32 HNC_LadSave(Bit16 clientNo = 0);
extern Bit32 HNC_LadGetNum(Bit16 clientNo = 0);
extern Bit32 HNC_LadGetCopyNum(Bit16 clientNo = 0);
extern Bit32 HNC_LadSetCell(Bit8* buf, Bit32 r, Bit32 c, Bit16 clientNo = 0);
extern Bit32 HNC_LadFindstring(Bit8* buf, Bit32* row, Bit32* col, Bit32 updown = 0, Bit16 clientNo = 0);
extern Bit32 HNC_LadReload(Bit16 clientNo = 0);
extern Bit32 HNC_LadGetChangeFlag(Bit16 clientNo = 0);

#endif
