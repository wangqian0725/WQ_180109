#include "serial.h"
#include "coon.h"
#include <reg52.h>

/*
	使用了串口中断,定时器1中断
    定时器初值计算公式:
	x = 2^n - (2^SMOD * fosc) / (32 * bps * 12 )
	        n: 单次收发的数据位数
            SMOD: 波特率加倍位数(PCON.7)
    x = 2^8 - (2^0 * 11.0592 * 10^6) / ( 32 * 9600 * 12) = 253 = 0xFD
	x = 2^8 - (2^0 * 12 * 10^6) / ( 32 * 9600 * 12 ) =
*/

uchar buff_serial[MAXLEN_BUFF_SERIAL]={0};
uchar pwrite_serial=0, pread_serial=0;

/*********************************************************************
 原型: void init_serial()
 功能: 初始化串口
*********************************************************************/
void init_serial()
{
	//置定时器1工作于8位自动重载模式,用于产生波特率(并保持定时器0信息位的设置)
	TMOD = (TMOD & 0x0F) | 0x20;
	//波特率不倍增(并保留非串口信息位的设置)
	PCON = PCON & 0x7F;
	//8位URT,波特率可变,(T1溢出率/n),允许接收
    SCON = 0x50;
	//波特率9600
	#ifdef  MCU_FREQUENCY_110592
		#ifdef BPS_9600
	    TH1 = 0xFd;
	    TL1 = 0xFd;
		#endif
		#ifdef BPS_2400
		TH1 = 0xF3;
		TL1 = 0xF3;
		#endif
	#endif
	#ifdef MCU_FREQUENCY_12
		#ifdef BPS_2400
		TH1 = 0xF3;
		TL1 = 0xF3;
		#endif
	#endif
	#ifdef MCU_STC1T_12
		#ifdef BPS_2400
		TH1 = 0xF3;
		TL1 = 0xF3;
		#endif
	#endif

	ES = 1;         //(IE.4)允许串行中断

	//启动定时器1
    TR1 = 1;
}

/*********************************************************************
 原型: void write_serial(uchar *pStr, int pStrLen)
 功能: 发送数据
*********************************************************************/
#ifdef NEED_WIRTE_SERIAL
/*********************************************************************
 原型: void writebyte_serial(uchar dat)
 功能: 向串口发送一字节数据
*********************************************************************/
void writebyte_serial(uchar dat)
{
	ES = 0;
	SBUF = dat;
	while(!TI);
	TI = 0;
	ES = 1;
}
void write_serial(uchar *pStr, int pStrLen)
{
	uint i=0;

	if( pStrLen == -1 )
	{
		for(i=0; pStr[i]!=0; i++)
			writebyte_serial(pStr[i]);
	}
	else
	{
		for(i=0; i<pStrLen; i++)
			writebyte_serial(pStr[i]);
	}
}
#endif

/*********************************************************************
 原型: void clear_serial()
 功能: 清空串口缓存
*********************************************************************/
#ifdef NEED_CLEAR_SERIAL
void clear_serial()
{
	pread_serial = pwrite_serial;
}
#endif

/*********************************************************************
 原型: uchar read_serial(uchar *pStr)
 功能: 从串口缓冲读取数据
*********************************************************************/
#ifdef NEED_READ_SERIAL
uchar read_serial(uchar *pStr)
{
	uchar ln=0;

	while( pread_serial != pwrite_serial )
	{
		pStr[ln] = buff_serial[pread_serial];
		ln++;
		pread_serial = (pread_serial + 1 ) % MAXLEN_BUFF_SERIAL;
	}
	return ln;
}
#endif

/*********************************************************************
 原型: uchar read2_serial(uchar *pStr)
 功能: 读串口数据,不丢弃数据
*********************************************************************/
#ifdef NEED_READ2_SERIAL
uchar read2_serial(uchar *pStr)
{
	uchar ln=0;
	uchar pread=0;

	pread = pread_serial;
	while( pread != pwrite_serial )
	{
		pStr[ln] = buff_serial[pread];
		ln++;
		pread = (pread + 1 ) % MAXLEN_BUFF_SERIAL;
	}
	return ln;
}
#endif

//串口中断函数, 读数据到串口缓冲
void interrupt_serial() interrupt 4
{
	ES = 0;                //关闭串行中断
	RI = 0;                //清除串行接收标志位

	buff_serial[pwrite_serial] = SBUF;  //从串口缓冲区取得数据
	pwrite_serial = (pwrite_serial + 1) % MAXLEN_BUFF_SERIAL;

	ES = 1;    //允许串口中断
}
