#include "HX711.h"
#include <reg52.h>
#include <intrins.h>

sbit CLK_HX711=P2^1;
sbit DAT_HX711=P2^0;

ulng g_ulEEmpty=0;   //存放设备毛重

/*********************************************************************
 原型: ulng read_HX711AD()
 功能: 读取模块返回的24字节数据
 返回: 读到的数据
*********************************************************************/
ulng read_HX711()
{
	ulng count;
	unsigned char i;

	DAT_HX711 = 1;
	_nop_();  _nop_();  _nop_();
	CLK_HX711 = 0;

	count = 0;
	while( DAT_HX711 );
	for(i=0; i<24; i++)
	{
		CLK_HX711 = 1;
		count = count << 1;
		CLK_HX711 = 0;
		if( DAT_HX711 ) count++;
	}

	CLK_HX711 = 1;
	count = count^0x800000;
	_nop_();  _nop_();  _nop_();
	CLK_HX711 = 0;

	return count;
}

/*********************************************************************
 原型: void init_HX711AD()
 功能: 初始化HX711AD, 取得设备毛重
*********************************************************************/
void init_HX711()
{
	g_ulEEmpty = read_HX711();
	g_ulEEmpty = g_ulEEmpty / 100;
}

/*********************************************************************
 原型: ulng getWeight_HX711AD()
 功能: 称重
*********************************************************************/
ulng getWeight_HX711()
{
	ulng ul;

	ul = read_HX711();
	ul = ul / 100;

	if(ul > g_ulEEmpty)
	{
		ul = ul - g_ulEEmpty;    //获取实物的AD采样数值。

		#ifdef HX711_40KG  //40公斤
		ul = (ulng)((float)ul / 1.07 + 0.05 ); 	//+0.05是为了四舍五入百分位
		#endif

		#ifdef HX711_100KG  //100公斤
		ul = (ulng)((float)ul * 2.4589 + 0.05 ); 	//+0.05是为了四舍五入百分位
		#endif

		return ul;
	}

	return 0;
}




