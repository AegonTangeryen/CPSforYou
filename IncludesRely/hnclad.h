#ifndef __HNC_LAD_H__
#define __HNC_LAD_H__

#include "hncdatatype.h"
#include "lad_def.h"

#define CONNECT_NUM 8
typedef struct
{
	SLadRow* lad_row;//����ͼ��������
	Bit32 br;//����ͼ���濪ʼλ��
	Bit32 ln;//����ͼ��Ч����
}LAD_AP;//����ͼ��������

enum LAD_CMD//��������
{
	LAD_STATUS,//Ԫ��ʵʱ״̬
	LAD_ABLE_STATUS1,//ͨ�����з���Ԫ��ǿ��״̬
	LAD_ABLE_STATUS2,//ͨ�������Ԫ��ǿ��״̬
	LAD_REG_STATUS,//Ԫ���Ĵ���ʵʱ���ݣ����紫��
	LAD_ROW,//��ȡԪ������
	LAD_SYMBOL,//��ȡ���ű�
	LAD_DEL_ROW,//ɾ����
	LAD_COPY_ROW,//������
	LAD_PASTE_ROW,//ճ����
	LAD_ADD_ROW,//������
	LAD_INSERT_ROW,//������
	LAD_CHANGE_PARM,//�޸Ĳ���
	LAD_ADD_CELL,//����Ԫ��
	LAD_DEL_CELL,//ɾ��Ԫ��
	LAD_CHANGE_FLAG,//����ͼ�޸ı��
	LAD_COMPILE,//����
	LAD_RELOAD,//��������
	LAD_SAVE,//����
	LAD_DEL_VER,//ɾ������
	LAD_MAX_ROW,//��ȡ����ͼ�������
	LAD_COPY_NUM,//��ȡ���а��е�����
	LAD_FIND,//���ң����ַ���
	LAD_FIND_PRE,//���ϼ������ң�����ǰλ��
	LAD_FIND_NEXT,//���²��ң�����ǰλ��
	LAD_SYMBOL_CHANGE,//�޸ķ��ű�
	LAD_SYMBOL_FIND,//���ң����ַ���
	LAD_SYMBOL_FIND_PRE,//���ϼ������ң�����ǰλ��
	LAD_SYMBOL_FIND_NEXT,//���²��ң�����ǰλ��
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
