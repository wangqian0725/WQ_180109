#include "coon.h"
#include <intrins.h>

/*********************************************************************
 ԭ��: void delay_5us()
 ����: ��ʱ5us
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
 ԭ��: void delay_10us()
 ����: ��ʱ10us
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
 ԭ��: void delay_20us()
 ����: ��ʱ20us
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
 ԭ��: void delay_ms(uint pMS)
 ����: ��ʱָ���ĺ���ʱ��pMS, ��ʱ���С��1%
 ����: pMS     ��ʱ�ĺ�����
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
 ԭ��: uchar getNField(char *p_caSrc, uchar p_iIdx, char p_cSplit, char *p_caDst)
 ����: ȡ�õ�p_iIdx���������, p_iIdx(0..n)
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
		iEnd++;  //��Ҫ,�������һ�����Ƿָ�������� 
	}
	
	memcpy_std(p_caDst, p_caSrc+iStart, iEnd - iStart);

	return iEnd - iStart;
}
#endif

#ifdef NEED_STD_MEMCPY
/*********************************************************************
 ԭ��: void memcpy_std(uchar *p_dst, uchar *p_src, uchar p_ln)
 ����: ȡ�õ�p_iIdx���������, p_iIdx(0..n)
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
 ԭ��: uchar strlen_std(uchar *str)
 ����: ȡANSCII�ַ�������
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
 ԭ��: void char2hex(char *src, int ln, char *dst)
 ����: ���ַ�����չΪ16������ʽ
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

