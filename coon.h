#ifndef __COON_H__
#define __COON_H__

#include "coon_def.h"

//#define VERSION_COON  "coon V1.0"  //��һ�α�д
//#define VERSION_COON  "coon V2.0"  //�Ż�����ռ�,2015-5-3 
#define VERSION_COON  "coon V2.1"  //�Ż�����ռ�,2015-5-4

#define NEED_MS_SLEEP    1    //��Ҫ���뼶��ʱ����
#define NEED_5US_SLEEP   1    //��Ҫ5΢�뼶��ʱ����
//#define NEED_10US_SLEEP  1    //��Ҫ10΢�뼶��ʱ����
#define NEED_20US_SLEEP  1    //��Ҫ20΢�뼶��ʱ����
//#define NEED_GETFIELD    1    //��ҪgetNField����

#ifdef NEED_5US_SLEEP
	void delay_5us();      //��ʱ5us
#endif
#ifdef NEED_10US_SLEEP
	void delay_10us();     //��ʱ10us
#endif
#ifdef NEED_20US_SLEEP
	void delay_20us();     //��ʱ20us
#endif
#ifdef NEED_MS_SLEEP
	void delay_ms(uint pMS);   //��ʱָ������ʱ��pMS
#endif

#ifdef NEED_GETFIELD
    //ȡ�õ�p_iIdx���������, p_iIdx(0..n)
	uchar getNField(char *p_caSrc, uchar p_iIdx, char p_cSplit, char *p_caDst);
#endif 

//////////////////////////////////////////////////
//memset  ʹ��ϵͳ����ʡ�ռ�
//#define NEED_STD_MEMCPY  1      //ϵͳ����memcpy
//#define NEED_STD_STRLEN  1      //ϵͳ����strlen

#ifdef NEED_STD_MEMCPY
	void memcpy_std(uchar *p_dst, uchar *p_src, uchar p_ln);   //p_src���Ȳ��ܳ���255�ֽ�
#endif
#ifdef NEED_STD_STRLEN
	uchar strlen_std(uchar *str);
#endif
	
#endif  //__COON_H__
