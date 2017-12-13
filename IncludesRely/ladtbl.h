#ifndef _LAD_TBL_H_
#define _LAD_TBL_H_

#include "lad_def.h"

typedef struct _CMD_ATTRIB
{
	uBit16 cmdID;
	Bit8 name[12];//������
	Bit8 remark[32];//ע��
	Bit16 width;
	Bit16 height;
	Bit8 type;//0(��ʼ)��1(��)��2(��)��3(����)�������Ԫ����4,5(����)���������Ԫ����6����ռ�õ�����
	Bit8 input;//�������
	Bit8 ParmNum;//��������
	struct{
		Bit8 h_pos,w_pos;//�����洢λ��	
		Bit8 ParaType;//ָ���������,true�㣬false��
		Bit32 ParaEnableReg;//����ļĴ���,������'X'��'Y'��'F'��'G'��'R'��'W'��'D'��'P'��'T'��'C'��'B'��'L'��'S'
	}ParaSt[9];
}SCmdAttr;

#ifdef _NC_1024X768_
#define CELL_WIDTH				68
#define CELL_HEIGHT				56
#define CELL_PER_COL          10
#define TOP_BLANK              68
#define CELL_SEL_OF_ROW	6
#define CELL_SEL_OF_COL 10
#endif

#ifdef _NC_800X600_
#define CELL_WIDTH				68
#define CELL_HEIGHT				55
#define CELL_PER_COL          8
#define TOP_BLANK              64
#define CELL_SEL_OF_ROW	6
#define CELL_SEL_OF_COL 8
#endif

#ifdef _NC_800X600_808_
#define CELL_WIDTH				68
#define CELL_HEIGHT				55
#define CELL_PER_COL          8
#define TOP_BLANK              64
#define CELL_SEL_OF_ROW	6
#define CELL_SEL_OF_COL 8
#endif

#ifdef _NC_640X480_
#define CELL_WIDTH				54
#define CELL_HEIGHT				56
#define CELL_PER_COL          6
#define TOP_BLANK              24
#define CELL_SEL_OF_ROW	6
#define CELL_SEL_OF_COL 6
#endif

extern Bit8 lad_get_para_text( SLadCell *p, Bit8 *buf);
extern Bit8* lad_get_parm_name(uBit16 n, Bit8 flag);
extern Bit8* lad_get_parm_remark(uBit16 n, Bit8 flag);
extern void lad_get_para_comment(SLadReg* p, Bit8* buf);
extern Bit16 lad_get_parm_no(uBit16 cmdID, Bit8 w_pos, Bit8 h_pos);
extern Bit8 lad_check_input(uBit16 cmdID, Bit8 n, Bit8* buf,SLadReg* p);
extern Bit16 lad_get_height(uBit16 cmdID);
extern Bit8 lad_get_type(uBit16 cmdID);
extern Bit16 lad_get_width(uBit16 cmdID);
extern Bit32 lad_find_reg(SLadReg* p);
extern Bit8 lad_get_input_num(uBit16 cmdID);
extern uBit16 LadFlagToIncNo(uBit16 flag, Bit8 type);
extern Bit16 lad_get_parm_num(uBit16 cmdID);
extern Bit8 lad_get_parm_offset(uBit16 cmdID, Bit8* h_pos, Bit8* w_pos, Bit8 n);
extern void lad_load_usr_parm(Bit8* buf);
extern Bit8 lad_usr_file_load(Bit8 *file);
#endif
