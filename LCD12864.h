#ifndef __LCD12864_H__
#define __LCD12864_H__

#include "coon_def.h"

#define VERSION_12864 "LCM12864 V4.0 150912"   //ͳһ�ӿ�
//#define NEED_CLS_LCD12864       1   //�Ƿ���Ҫ��������
//#define NEED_POS_LCD12864         1   //��Ҫ�������÷���,�÷�������
//#define NEED_CURSOR_LCD12864    1   //�Ƿ���Ҫ��ʾ���
//#define NEED_FLICKER_LCD12864   1   //ȫ����˸
//#define NEED_IMAGE_LCD12864     1   //ͼ����ʾ

//��ʼ��Һ��,Ӧ������ʱ����
void init_LCD();
//��Һ��ָ����(0..n-1)��ָ����(0..m-1)��ʼ,��ʾָ�����ַ���,��������
void show_str_LCD(uchar *pStr, uchar pLine, uchar pIdx);

#ifdef NEED_CLS_LCD12864   //����
	void cls_LCD();
#endif

#ifdef NEED_POS_LCD12864  //��λ���
	void pos_LCD(uchar pLine, uchar pIdx);
#endif

#ifdef NEED_CURSOR_LCD12864  //�Ƿ���Ҫ��ʾ���,pFlag=1��ʾ���, 0�رչ��
	void cursor_LCD(bit pFlag);
#endif

#ifdef NEED_FLICKER_LCD12864  //ȫ����˸
	void flicker_LCD(uint pMs);
#endif

#ifdef NEED_IMAGE_LCD12864  //ͼ����ʾ
	void image_LCD(uint x, uint y, uint w, uint h, uchar *pBmp);
#endif

#endif

