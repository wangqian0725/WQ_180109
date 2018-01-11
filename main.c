#include "LCD12864.h"
#include "HCSR04.h"
#include "coon.h"
#include "serial.h"
#include "HX711.h"
#include "IndepKey.h"
#include "keys.h"
#include <reg52.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ulng  g_lWeight=0;
float g_fHigh=0;
float g_fVal=0;

void show(int flag)
{
	int  i1=0, i2=0;
	char s[17]={0};

	if( flag == 0 )   //显示待机状态
	{
		show_str_LCD("  体型测量仪    ", 0, 0);
		show_str_LCD("                ", 1, 0);
		show_str_LCD("                ", 2, 0);
		show_str_LCD("                ", 3, 0);
	}
	if( flag == 1 )  //显示身高
	{
		memset(s, 0, sizeof(s));
		sprintf(s, "身高: %03dCM     ", (int)g_fHigh);
		show_str_LCD(s, 1, 0);
	}
	if( flag == 2 )  //显示体重
	{	
		memset(s, 0, sizeof(s));
		i1 = (int)(g_lWeight/1000);
		i2 = g_lWeight%1000/10;
		sprintf(s, "体重: %03d.%02dKG  ", i1, i2);
		show_str_LCD(s, 2, 0);
	}
	if( flag == 3 )  //显示体型
	{
		memset(s, 0, sizeof(s));
		sprintf(s, "体型指数: %0.2f ", g_fVal);
		show_str_LCD(s, 3, 0);
	}
}

void main() 
{ 
	int key=0;

	init_LCD();
	init_HX711();

	show( 0 );

	while( 1 )
	{
		key = getkey_IndepKey();
		if( key == 0 ) continue;

		if( key == STD_KEY_IDX_1 )
		{
			init_HX711();	//重量校准
			show_str_LCD("    校准完成    ", 3, 0);
			delay_ms(1000);
			show_str_LCD("                ", 3, 0);
		}

		if( key == STD_KEY_IDX_2 ) //进入测量状态
		{
			key = 0;

			//获取身高
			while( 1 )
			{
				g_fHigh = 200 - get_HCSR04();
				show( 1 );	
				if( getkey_IndepKey() == STD_KEY_IDX_2 ) break;
			}

			//获得体重
			while( 1 )
			{
				g_lWeight = getWeight_HX711();
				show( 2 );
				if( getkey_IndepKey() == STD_KEY_IDX_2 ) break;
			}

			//计算体型
			g_fHigh = g_fHigh / 100;  //变为米
			g_fVal = ((float)g_lWeight/1000) / (g_fHigh * g_fHigh);
			show( 3 );

			while( 1 )
			{
				if( getkey_IndepKey() == STD_KEY_IDX_2 ) break;
			}
		}

		show( 0 );	
	}
}

