#ifndef __COON_DEF_H__
#define __COON_DEF_H__

typedef bit bool;
#define true 1
#define false 0

#define MAXLEN_BUFF_SERIAL  20     //串口缓冲区大小

//数据类型
#define uchar unsigned char   //无符号字符型
#define uint unsigned int     //无符号整型
#define ulng unsigned long    //无符号长整型

//设备数据交互模式
#define PARALLEL_MODE 1       //并行模式
#define SERIAL_MODE   2       //串行模式

#define MCU_FREQUENCY_12  (12)            //12M处理器主频
//#define MCU_FREQUENCY_110592  (11.0592)   //11.0592M处理器主频
//#define MCU_STC1T_12                      //STC1T

//#define BPS_9600  1		   //9600波特率
#define BPS_2400  1			 //2400波特率

#endif //__COON_DEF_H__
