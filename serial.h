#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "coon_def.h"

/*
    说明: 1 此驱动使用了定时器1中断,使用此驱动的应用,不应该再使用定时器1于他途
	      2 此驱动定义了MAXLEN_BUFF_SERIAL字节的串口接收缓存
		  3 使用此驱动的应用应该再在应用启动时先执行init_serial, 然后在需要的时候执行EA=1
*/

#define VERSION_SERIAL  "Serial V4.0 150912"   //调整版本号定义

#define NEED_READ_SERIAL       1   //需要读串口方法
//#define NEED_READ2_SERIAL      1   //需要临时读串口方法(不丢弃已读数据)
//#define NEED_CLEAR_SERIAL      1   //清空串口缓存
#define NEED_WIRTE_SERIAL      1   //是否需要写串口方法

#ifdef NEED_CLEAR_SERIAL
	//清除串口接收缓存
	void clear_serial();
#endif

//初始化串口,在应用起动时调用,其后在需要的时候,调用EA=1
void init_serial();

#ifdef NEED_WIRTE_SERIAL
	//向串口写入一个字节数据
	void writebyte_serial(uchar dat);
	//向串口写一个字符串, 如果pStrLen=-1,表示取C字符串长度
	void write_serial(uchar *pStr, int pStrLen);
#endif

#ifdef NEED_READ_SERIAL
    //读当前串口接收缓存的所有数据,函数返回值为读到的数据长度
	uchar read_serial(uchar *pStr);
#endif
#ifdef NEED_READ2_SERIAL
	uchar read2_serial(uchar *pStr);
#endif

#endif  //__SERIAL_H__

