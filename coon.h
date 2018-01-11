#ifndef __COON_H__
#define __COON_H__

#include "coon_def.h"

//#define VERSION_COON  "coon V1.0"  //第一次编写
//#define VERSION_COON  "coon V2.0"  //优化代码空间,2015-5-3 
#define VERSION_COON  "coon V2.1"  //优化代码空间,2015-5-4

#define NEED_MS_SLEEP    1    //需要毫秒级延时函数
#define NEED_5US_SLEEP   1    //需要5微秒级延时函数
//#define NEED_10US_SLEEP  1    //需要10微秒级延时函数
#define NEED_20US_SLEEP  1    //需要20微秒级延时函数
//#define NEED_GETFIELD    1    //需要getNField方法

#ifdef NEED_5US_SLEEP
	void delay_5us();      //延时5us
#endif
#ifdef NEED_10US_SLEEP
	void delay_10us();     //延时10us
#endif
#ifdef NEED_20US_SLEEP
	void delay_20us();     //延时20us
#endif
#ifdef NEED_MS_SLEEP
	void delay_ms(uint pMS);   //延时指定毫秒时间pMS
#endif

#ifdef NEED_GETFIELD
    //取得第p_iIdx个域的数据, p_iIdx(0..n)
	uchar getNField(char *p_caSrc, uchar p_iIdx, char p_cSplit, char *p_caDst);
#endif 

//////////////////////////////////////////////////
//memset  使用系统函数省空间
//#define NEED_STD_MEMCPY  1      //系统函数memcpy
//#define NEED_STD_STRLEN  1      //系统函数strlen

#ifdef NEED_STD_MEMCPY
	void memcpy_std(uchar *p_dst, uchar *p_src, uchar p_ln);   //p_src长度不能超过255字节
#endif
#ifdef NEED_STD_STRLEN
	uchar strlen_std(uchar *str);
#endif
	
#endif  //__COON_H__
