#ifndef _LAD_DEF_H_
#define _LAD_DEF_H_

#include "hncdatatype.h"

//�����Ǳ�׼��䴦���������
enum LAD_CMDID
{
	I_VOR,		//0����
	I_LINE,     //1ֱ��
	I_LDT,		//2
	I_LD,		//3
	I_LDI,		//4
	I_LDC,		//5
	I_LDNC,		//6
	I_OUT,		//7
	I_OOUT,		//8
	I_SET,		//9
	I_RST,		//10
	I_AND,		//11
	I_ANI,		//12
	I_ANC,		//13
	I_ANNC,		//14
	I_OR,		//15
	I_ORI,		//16
	I_ORC,	    //17
	I_ORNC,		//18
	I_LDP,		//19
	I_LDF,		//20
	I_ANDP,		//21
	I_ANDF,		//22
	I_ORP,		//23
	I_ORF,		//24
	I_ORB,		//25
	I_ANB,		//26
	I_MPS,		//27
	I_MRD,		//28
	I_MPP,		//29

	I_TMR=36,	//36
	I_TMRB,		//37
	I_STMR,		//38
	
	I_CTR=44,	//44
	I_CTRC,		//45
	I_CTUD,		//46

	I_IEND=52,	//52
	I_1END,		//53
	I_2END,		//54
	I_JMP=57,	
	I_LBL,		//58
	I_CALL,		//59
	I_SP,		//60
	I_SPE,		//61
	I_RETN,		//62
	I_LOOP,		//63
	I_NEXT,		//64

	I_ADD=70,	//70
	I_SUB,		//71
	I_MUL,		//72
	I_DIV,		//73
	I_INC,		//74
	I_DEC,		//75
	I_WAND,		//76
	I_WOR,		//77
	I_WXOR,		//78
	I_NEG,		//79
	I_CMP,		//80
	I_COIN,		//81
	I_MOV,		//82
	I_BMOV,		//83
	I_FMOV,		//84
	I_XCH,		//85
	I_ZRST,		//86
	I_XMOV,		//87
	I_LT,		//88
	I_ACMP,		//89
	
	I_PLS=100,	//100
	I_PLF,		//101
	I_ALT,		//102
	I_ROT,		//103
	I_ENCO,		//104
	I_DECO,		//105
	I_COD,		//106
	I_SER,		//107
	I_ALARM,	//108
	I_EVENT,	//109
	I_PTN,		//110
	I_NTP,		//111
	I_NIXIE,    //112
	I_TOOLUSE,  //113
	I_ASSEM,	//114
	I_DISAS,	//115
	I_ACVT,		//116


	I_MDST=140,	//140
	I_MDGT,		//141
	I_CYCLE,	//142
	I_HOLD,		//143
	I_CYCLED,	//144
	I_HOLDLED,	//145
	I_MGET,		//146
	I_MACK,		//147
	I_TGET,		//148
	I_TACK,		//149
	I_DRYRUN,	//150
	I_SKIP,		//151
	I_RPOVRD,	//152
	I_FDOVRD,	//153
	I_SPOVRD,	//154
	I_SELSTOP,	//155
	I_GEARSW,   //156
	I_TEMPSEN, //157
    I_MDI,//158

	I_SPBRAK=159,//159
	I_SPORIEN,	//160
	I_MPGSET,	//161	
	I_STEPMUL,	//162	
	I_STEPAX,	//163	
	I_STEPAXES,	//164	
	I_JOGSW,	//165     
	I_JOGSWS,	//166     
	I_JOGVEL,	//167
	I_JOGVELS,	//168
	I_HOMRUN,	//169
	I_HOMRUNS,	//170
	I_HOMSW,	//171
	I_HOMSWS,	//172
	I_HOMLED,	//173
	I_HOMLEDS,	//174
	I_AXEN,		//175
	I_AXENS,	//176
	I_AXPLMT,	//177
	I_AXPLMTS,	//178
	I_AXNLMT,	//179
	I_AXNLMTS,	//180
	I_AXOK,		//181
	I_AXOKS,	//182
	I_AXLOCK,	//183
	I_AXLOCKS,	//184
	I_SVSW,		//185
	I_SPDA,		//186
	I_ESCBLK,	//187
	I_CHANSW,	//188
	I_USERIN,	//189
	I_USEROUT,	//190
	I_DESYN,	//191

	I_STOP=194,		//194
	I_RESET,	//195
	I_TOOLSET,	//196
	I_TOOLCLR,	//197
	I_HOMRUN1,	//198
	I_PARTCNT,	//199
	I_PARTCLR,	//200
	I_POWEROFF,	//201
	I_SAVEDATA,	//202
	I_SPBUS,	//203
	I_SPJOG,	//204
	I_HEADSEN,	//205
	I_SPORIOK,	//206
	I_RTOMPG,	//207
	I_AXMOVE,	//208
	I_AXMOVETO,	//209
	I_AXLMF2,	//210
	I_RST_CHK,  //211
	I_RST_CLR,  //212
	I_SPZERO,	//213
	I_SPRCH,	//214
	I_SPBUS1,	//215
	I_MST,      //216
	I_REFPT,	//217
	I_AXMD,		//218
	I_AXISMOVE, //219
	I_AXISHOME2,//220
	I_USR1,		//221
	I_USR2,		//222
	I_USR3,		//223
	I_USR4,		//224
	I_USR5,		//225
	I_USR6,		//226
	I_USR7,		//227
	I_USR8,		//228
	I_USR9,		//229
	I_USR10,	//230
 	I_FILT,		//231
	I_TOTAL
};

#define X_MAX_NUM	512
#define Y_MAX_NUM	512
#define F_MAX_NUM	3119
#define G_MAX_NUM	3119
#define R_MAX_NUM	400
#define W_MAX_NUM	200
#define D_MAX_NUM	100
#define B_MAX_NUM	1722
#define P_MAX_NUM	200

#define PLC_CMD_NUM 161

#define MAX_PLC_CMD_NUM		512
#define LAD_CMD_TBL_LEN		10000
#define LAD_REG_TBL_LEN		24000
#define LAD_CELL_TBL_LEN	50000 //
#define LAD_SYMBL_TBL_LEN	5000

#define CELL_PER_ROW		 10

typedef struct LADPRG
{
	Bit32 Ver;//�汾
	Bit32 Hsize;//�ļ�ͷ��С
	Bit32 CMDN;// ָ������
	Bit32 REGN;//��������
	Bit32 IBRow;//��ʼ����ʼ��
	Bit32 IERow;//��ʼ��������
	Bit32 FBRow;//plc1��ʼ��
	Bit32 FERow;//plc1������
	Bit32 SBRow;//plc2��ʼ��
	Bit32 SERow;//plc2������
	Bit32 IREGN;//��ʼ��������ʼλ��
	Bit32 FREGN;//plc1������ʼλ��
	Bit32 SREGN;//plc2������ʼλ��
	Bit32 LADN;//����ͼ����
	Bit32 SYMN;//ע������
	Bit32 reserv[111];//����
	Bit32 CheckFlag;//�ļ�У����
	Bit32 CheckNum;//�ļ�У����
}LadPrg;

typedef struct _LADCMD
{
    uBit16 cmdID;//����ID
	uBit8 col,cast;//�кš�ǿ�ƿ����� 0X1��ʾͨ��0x2��ʾ�ϣ�0x0��ʾ����
	uBit32 state;//����״̬
	Bit32 reg_idx;//Ԫ���Ĳ����Ĵ������б��е�λ������
    Bit32 row;//����ͼ�е��к�
}SLadCmd;//16 bytes

typedef struct _LADREG
{
    Bit16 index;//�Ĵ����±� x5.7 �е�5
    Bit8 reg_type;//�Ĵ������� x5.7 �е� 'x'
    Bit8 bit; //�Ĵ���λ��-1��ʾ��Ч �е� '7'
}SLadReg; //4 bytes

typedef struct _LADCELL
{
	Bit8 parmmask;//�������룬����˴��Ƿ��в���
	Bit8 parallel;//���ߣ������е�Ԫ����
    Bit8 rectmask;//�߿����룬������������
	Bit8 reserv;     
	Bit8 w_pos,h_pos; //����Ԫ�����Ԫ���󶥵��ڿ�Ⱥ͸߶ȷ����ϵĸ���λ��
    uBit16 cmdID; //����ID
    Bit32 cmd_idx;//��������е�λ��
	SLadReg reg;
}SLadCell;//16 bytes

//��ͼ��
typedef struct _LADROW
{
	SLadCell dft_cell[CELL_PER_ROW];
}SLadRow;

typedef struct _LAD_SYMBOL
{
	SLadReg reg;
	Bit8 symbol[16];
	Bit8 comments[76];
}SSymbItem;//96 bytes

#define _hnclad_get_size() (sizeof(SLadCmd)*LAD_CMD_TBL_LEN+sizeof(SLadReg)*LAD_REG_TBL_LEN+sizeof(SLadCell)*LAD_CELL_TBL_LEN+sizeof(SSymbItem)*LAD_SYMBL_TBL_LEN)

#endif
