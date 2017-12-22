#ifndef __DEVDICT_H__
#define __DEVDICT_H__

#include "hncdatatype.h"

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_write(Bit32 ax_no, Bit32 i)
//
//    ���ܣ�
//					�ŷ���������
//
//    ������
//					Bit32 ax_no���߼����
//					Bit32 i���ŷ��������
//
//    ������
//                  �����ŷ��������ر�־
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_write(Bit32 ax_no, Bit32 i);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_write_axis(Bit32 ax_no)
//
//    ���ܣ�
//					����ָ����ȫ���ŷ�����
//
//    ������
//					Bit32 ax_no���߼����
//
//    ������
//                  �����ŷ��������ر�־
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_write_axis(Bit32 ax_no);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_write_all(void)
//
//    ���ܣ�
//					�������ŷ�����ȫ�����ص��ŷ�������
//
//    ������
//
//    ������
//                  �����ŷ��������ر�־
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_write_all(void);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_read(Bit32 ax_no, Bit32 i)
//
//    ���ܣ�
//					�ŷ������ϴ�
//
//    ������
//					Bit32 ax_no���߼����
//					Bit32 i���ŷ��������
//
//    ������
//                  �����ŷ������ϴ���־	
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��					
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_read(Bit32 ax_no, Bit32 i);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_read_axis(Bit32 ax_no)
//
//    ���ܣ�
//					�ϴ�ָ����ȫ���ŷ�����
//
//    ������
//					Bit32 ax_no���߼����
//
//    ������
//                  �����ŷ������ϴ���־
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_read_axis(Bit32 ax_no);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_read_all(void)
//
//    ���ܣ�
//					�ϴ�ȫ���ŷ�����������
//
//    ������
//
//    ������
//                  �����ŷ������ϴ���־
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_read_all(void);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_check(Bit32 ax_no, Bit32 i)
//
//    ���ܣ�
//					�ŷ�����һ���Լ��
//
//    ������
//					Bit32 ax_no���߼����
//					Bit32 i���ŷ��������
//
//    ������
//                  ϵͳ�����ŷ�����VS�ŷ���������վ����
//
//	  ���أ�
//                  ����1����һ��
//					����0��һ��
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_check(Bit32 ax_no, Bit32 i);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_check_axis(Bit32 ax_no)
//
//    ���ܣ�
//					ָ�����ŷ�����һ���Լ��
//
//    ������
//					Bit32 ax_no���߼����
//
//    ������
//                  ϵͳ�����ŷ�����VS�ŷ���������վ����
//
//	  ���أ�
//                  ����1����һ��
//					����0��һ��
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_check_axis(Bit32 ax_no);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_sync_all(void)
//
//    ���ܣ�
//					ͬ�������ŷ�����������
//
//    ������
//
//    ������
//					ϵͳ�����ŷ�����->�ŷ�������
//					ͬ�����Զ������ŷ�����������
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_sync_all(void);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_sync_axis(Bit32 ax_no)
//
//    ���ܣ�
//					ָ�����ŷ�����ͬ��
//
//    ������
//					Bit32 ax_no���߼����
//
//    ������
//					ϵͳ�����ŷ�����->�ŷ�������
//					ͬ�����Զ������ŷ�����������
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_sync_axis(Bit32 ax_no);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_is_change(void)
//
//    ���ܣ�
//					����豸�����ֵ��Ƿ��޸�
//
//    ������
//
//    ������
//                  Ŀǰ������ŷ������Ƿ��޸�
//
//	  ���أ�
//					����0��δ�޸�
//                  ����1�����޸�
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_is_change(void);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_clear_change_flag(void)
//
//    ���ܣ�
//					����豸�����ֵ��޸ı�־
//
//    ������
//
//    ������
//                  Ŀǰ������ŷ������޸ı�־
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_clear_change_flag(void);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_save_all(void)
//
//    ���ܣ�
//					֪ͨ�����ŷ��������������
//
//    ������
//
//    ������
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_save_all(void);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_save_axis(Bit32 ax_no)
//
//    ���ܣ�
//					֪ͨ��ָ����������ŷ��������������
//
//    ������
//					Bit32 ax_no���߼����
//
//    ������
//
//	  ���أ�
//					����0���ɹ�
//                  ����-1��ʧ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_save_axis(Bit32 ax_no);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_get_wr_state(Bit32 ax_no, Bit32 i)
//
//    ���ܣ�
//					��ȡָ���ŷ�����ͨѶ״̬
//
//    ������
//					Bit32 ax_no���߼����
//					Bit32 i���������
//
//    ������
//
//	  ���أ�
//                  ����-1��ָ���ŷ���������
//                  ����0������
//					����1����дͨѶ��
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_get_wr_state(Bit32 ax_no, Bit32 i);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_get_save_state(void)
//
//    ���ܣ�
//					����ŷ��������Ƿ��ڱ������״̬
//
//    ������
//
//    ������
//
//	  ���أ�
//					����1��������
//                  ����0������
//                  ����-1����ȡ�ŷ���������״̬����
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_get_save_state(void);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_get_bus_state(void)
//
//    ���ܣ�
//				��ȡ����ͨѶ״̬
//
//    ������
//
//    ������
//
//	  ���أ�
//				����0������ͨѶδ׼����
//				����1������ͨѶ��׼���ã�ͨѶ����
//				����2������ͨѶ��׼���ã�ͨѶæ
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_get_bus_state(void);

////////////////////////////////////////////////////////////////////////
//
//	  Bit32 hdict_get_nc_axis_mask(void)
//
//    ���ܣ�
//				��ȡʵ�����ӵ��ŷ����������߼���������
//
//    ������
//
//    ������
//
//	  ���أ�
//				�����߼���������
//
////////////////////////////////////////////////////////////////////////
extern Bit32 hdict_get_nc_axis_mask(void);

#endif