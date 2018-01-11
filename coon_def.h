#ifndef __COON_DEF_H__
#define __COON_DEF_H__

typedef bit bool;
#define true 1
#define false 0

#define MAXLEN_BUFF_SERIAL  20     //���ڻ�������С

//��������
#define uchar unsigned char   //�޷����ַ���
#define uint unsigned int     //�޷�������
#define ulng unsigned long    //�޷��ų�����

//�豸���ݽ���ģʽ
#define PARALLEL_MODE 1       //����ģʽ
#define SERIAL_MODE   2       //����ģʽ

#define MCU_FREQUENCY_12  (12)            //12M��������Ƶ
//#define MCU_FREQUENCY_110592  (11.0592)   //11.0592M��������Ƶ
//#define MCU_STC1T_12                      //STC1T

//#define BPS_9600  1		   //9600������
#define BPS_2400  1			 //2400������

#endif //__COON_DEF_H__
