#include "IndepKey.h"
#include "coon_def.h"
#include "coon.h"
#include "keys.h"
#include <reg52.h>

sbit indep_key_1=P3^6;
sbit indep_key_2=P3^7;

/*********************************************************************
 原型: uchar getkey_IndepKey()
 功能: 检测当前是否有独立按键按下
 返回: 按下的独立按键编号(1..n),没有按键则返回0
*********************************************************************/
uchar getkey_IndepKey()
{
	//按键1
	if( indep_key_1 == 0 )       //检测到按键按下(可能)
	{
		delay_ms(10);          //延迟10ms,此延时用于去抖
		if( indep_key_1 == 0 )        //检测到低电平,确定有按键按下
		{
			while( indep_key_1 == 0 ) ;  //等待按键释放
			return STD_KEY_IDX_1;
		}
	}

	//按键2
	if( indep_key_2 == 0 )       //检测到按键按下(可能)
	{
		delay_ms(10);          //延迟10ms,此延时用于去抖
		if( indep_key_2 == 0 )        //检测到低电平,确定有按键按下
		{
			while( indep_key_2 == 0 ) ;  //等待按键释放
			return STD_KEY_IDX_2;
		}
	}

	return 0;
}