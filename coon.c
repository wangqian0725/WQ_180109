#include "coon.h"
#include <intrins.h>

/*********************************************************************
 原型: void delay_5us()
 功能: 延时5us
*********************************************************************/
#ifdef NEED_5US_SLEEP
void delay_5us()
{
	#ifdef MCU_FREQUENCY_12
		_nop_();
	#endif

	#ifdef MCU_FREQUENCY_110592
		;
	#endif
}
#endif

/*********************************************************************
 原型: void delay_10us()
 功能: 延时10us
*********************************************************************/
#ifdef NEED_10US_SLEEP
void delay_10us()
{
	#ifdef MCU_FREQUENCY_12
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
	#endif

	#ifdef MCU_FREQUENCY_110592
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
	#endif
}
#endif

/*********************************************************************
 原型: void delay_20us()
 功能: 延时20us
*********************************************************************/
#ifdef NEED_20US_SLEEP
void delay_20us()
{
	#ifdef MCU_FREQUENCY_12
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
	#endif

	#ifdef MCU_FREQUENCY_110592
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_();
		_nop_();    _nop_(); 
	#endif
}
#endif

#ifdef NEED_MS_SLEEP
/*********************************************************************
 原型: void delay_ms(uint pMS)
 功能: 延时指定的毫秒时间pMS, 延时误差小于1%
 参数: pMS     延时的毫秒数
*********************************************************************/
void delay_ms(uint pMS)
{
	uchar i=0;
	uchar j=0;

	#ifdef MCU_FREQUENCY_12
	    if( pMS < 10 )   j=121;
		else if( pMS < 100 ) j=122;
		else j=123;
	
		while(pMS--)
		{
			for(i=0; i<j; i++);
		}
	#endif

	#ifdef MCU_FREQUENCY_110592
	    if( pMS < 10 )   j=111;
		else if( pMS < 100 ) j=112;
		else j=113;
	
		while(pMS--)
		{
			for(i=0; i<j; i++);
		}
	#endif
}
#endif

#ifdef NEED_GETFIELD
/*********************************************************************
 原型: uchar getNField(char *p_caSrc, uchar p_iIdx, char p_cSplit, char *p_caDst)
 功能: 取得第p_iIdx个域的数据, p_iIdx(0..n)
*********************************************************************/
uchar getNField(char *p_caSrc, uchar p_iIdx, char p_cSplit, char *p_caDst)
{
	uchar i=0;
	uchar iIdx=0;
	uchar iStart=0;
	uchar iEnd=0;

	for(i=0; p_caSrc[i]!=0; i++)
	{
        iEnd = i;
		if( p_caSrc[i] == p_cSplit )
		{
			if( p_iIdx == iIdx ) break;
            
            iStart = i+1;
            iIdx++;
		}
		iEnd++;  //重要,修正最后一个不是分隔符的情况 
	}
	
	memcpy_std(p_caDst, p_caSrc+iStart, iEnd - iStart);

	return iEnd - iStart;
}
#endif

#ifdef NEED_STD_MEMCPY
/*********************************************************************
 原型: void memcpy_std(uchar *p_dst, uchar *p_src, uchar p_ln)
 功能: 取得第p_iIdx个域的数据, p_iIdx(0..n)
*********************************************************************/
void memcpy_std(uchar *p_dst, uchar *p_src, uchar p_ln)
{
	uchar i=0;

	for(i=0; i<p_ln; i++)
		p_dst[i] = p_src[i];
}
#endif

#ifdef NEED_STD_STRLEN
/*********************************************************************
 原型: uchar strlen_std(uchar *str)
 功能: 取ANSCII字符串长度
*********************************************************************/
uchar strlen_std(uchar *str)
{
	uchar i=0;
	while( str[i++] != 0 ) ;
	return i-1;
}
#endif

#ifdef NEED_CHAR2HEX
/*********************************************************************
 原型: void char2hex(char *src, int ln, char *dst)
 功能: 将字符串扩展为16进制形式
*********************************************************************/
void char2hex(char *src, int ln, char *dst)
{
    int d=0, d1=0, d2=0, i=0;
    
    for(i=0; i<ln; i++)
    {
        d = src[i]&0xFF;
        d1 = d / 16;
        d2 = d % 16;
        if(  0<=d1 && d1<=9  ) dst[i*2+0] = d1+0x30;
        if( 10<=d1 && d1<=15 ) dst[i*2+0] = d1+0x41-10;
        if(  0<=d2 && d2<=9  ) dst[i*2+1] = d2+0x30;
        if( 10<=d2 && d2<=15 ) dst[i*2+1] = d2+0x41-10;
    }
}
#endif

