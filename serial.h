#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "coon_def.h"

/*
    ˵��: 1 ������ʹ���˶�ʱ��1�ж�,ʹ�ô�������Ӧ��,��Ӧ����ʹ�ö�ʱ��1����;
	      2 ������������MAXLEN_BUFF_SERIAL�ֽڵĴ��ڽ��ջ���
		  3 ʹ�ô�������Ӧ��Ӧ������Ӧ������ʱ��ִ��init_serial, Ȼ������Ҫ��ʱ��ִ��EA=1
*/

#define VERSION_SERIAL  "Serial V4.0 150912"   //�����汾�Ŷ���

#define NEED_READ_SERIAL       1   //��Ҫ�����ڷ���
//#define NEED_READ2_SERIAL      1   //��Ҫ��ʱ�����ڷ���(�������Ѷ�����)
//#define NEED_CLEAR_SERIAL      1   //��մ��ڻ���
#define NEED_WIRTE_SERIAL      1   //�Ƿ���Ҫд���ڷ���

#ifdef NEED_CLEAR_SERIAL
	//������ڽ��ջ���
	void clear_serial();
#endif

//��ʼ������,��Ӧ����ʱ����,�������Ҫ��ʱ��,����EA=1
void init_serial();

#ifdef NEED_WIRTE_SERIAL
	//�򴮿�д��һ���ֽ�����
	void writebyte_serial(uchar dat);
	//�򴮿�дһ���ַ���, ���pStrLen=-1,��ʾȡC�ַ�������
	void write_serial(uchar *pStr, int pStrLen);
#endif

#ifdef NEED_READ_SERIAL
    //����ǰ���ڽ��ջ������������,��������ֵΪ���������ݳ���
	uchar read_serial(uchar *pStr);
#endif
#ifdef NEED_READ2_SERIAL
	uchar read2_serial(uchar *pStr);
#endif

#endif  //__SERIAL_H__

