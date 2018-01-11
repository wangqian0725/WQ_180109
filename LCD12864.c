#include "LCD12864.h"
#include "coon.h"
#include <reg52.h>
#include <intrins.h>

#define DATA_LCD12864  P0    //数据口

sbit RS_LCD12864  =  P2^7;      //片选
sbit RW_LCD12864  =  P2^6;      //液晶读/写控制
sbit EN_LCD12864  =  P2^5;      //液晶使能控制

/*********************************************************************
 原型: bit busy_LCD12864()
 功能: 检测液晶是否空闲
*********************************************************************/
bit busy_LCD12864()
{
	bit result;

	RS_LCD12864 = 0;
	RW_LCD12864 = 1;
	EN_LCD12864 = 1;
	delay_5us();
	result = (bit)(DATA_LCD12864&0x80);
	EN_LCD12864 = 0;
	return(result);
}

/*********************************************************************
 原型: void cmd_LCD12864(uchar pCmd, uint pMs)
 功能: 向LCD发送指令, EN高脉冲发送
 参数: pCmd   需要发送的指令字
       pMs    发送指令后等待的毫秒数
*********************************************************************/
void cmd_LCD12864(uchar pCmd, uint pMs)
{
	while(busy_LCD12864());
	RS_LCD12864 = 0;
	RW_LCD12864 = 0;

	EN_LCD12864 = 0;
	_nop_(); _nop_();
	DATA_LCD12864 = pCmd;
	_nop_(); _nop_();
	EN_LCD12864 = 1;
	_nop_(); _nop_();
	EN_LCD12864 = 0;

	delay_ms(pMs);
}

/*********************************************************************
 原型: void data_LCD12864(uchar pData, uint pMs)
 功能: 向LCD发送数据, EN高脉冲发送
 参数: pData   需要发送的数据
       pMs     发送数据后等待的毫秒数
*********************************************************************/
void data_LCD12864(uchar pData, uint pMs)
{
	while(busy_LCD12864());
	RS_LCD12864 = 1;
	RW_LCD12864 = 0;

	EN_LCD12864 = 0;
	DATA_LCD12864 = pData;
	_nop_(); _nop_();
	EN_LCD12864 = 1;
	_nop_(); _nop_();
	EN_LCD12864 = 0;

	delay_ms(pMs);
}

/*********************************************************************
 原型: void init_LCD()
 功能: 液晶初始化
*********************************************************************/
void init_LCD()
{
    //cmd_LCD12864(0x34, 1);      //扩充指令操作
    cmd_LCD12864(0x30, 1);      //基本指令操作
    cmd_LCD12864(0x01, 1);      //清除LCD的显示内容
	cmd_LCD12864(0x0C, 1);      //显示开,关光标
}

/*********************************************************************
 原型: void pos_LCD(uchar x, uchar y)
 功能: 设置显示位置
 参数: x    横向坐标
       y    纵向坐标
*********************************************************************/
void pos_LCD(uchar x, uchar y)
{
	if     (x == 0)     { x = 0x80; }
	else if(x == 1)     { x = 0x90; }
	else if(x == 2)     { x = 0x88; }
	else if(x == 3)     { x = 0x98; }

	cmd_LCD12864(x+y, 0);     //显示地址
}

/*********************************************************************
 原型: void show_str_LCD(uchar *pStr, uchar pLine, uchar pIdx)
 功能: 在指定位置开始显示指定字符串
 参数: pLine    行
       pIdx     列
*********************************************************************/
void show_str_LCD(uchar *pStr, uchar pLine, uchar pIdx)
{
	pos_LCD(pLine, pIdx);

	while(*pStr != 0)
	{
		data_LCD12864(*pStr, 1);
		pStr++;
	}
}

/*********************************************************************
 原型: void cls_LCD()
 功能: 清屏
*********************************************************************/
#ifdef NEED_CLS_LCD12864
void cls_LCD()
{
	//cmd_LCD12864(0x34, 1);      //扩充指令操作
	cmd_LCD12864(0x30, 1);      //基本指令操作
	cmd_LCD12864(0x01, 1);      //清屏
}
#endif

/*********************************************************************
 原型: void cursor_LCD(bit pFlag)
 功能: 打开/关闭光标, pFlag=1打开光标, 0关闭光标
*********************************************************************/
#ifdef NEED_CURSOR_LCD12864
void cursor_LCD(bit pFlag)
{
    cmd_LCD12864(0x30, 1);      //基本指令操作
	if( pFlag == 0 )
		cmd_LCD12864(0x0C, 1);      //显示开,关光标
	else
		cmd_LCD12864(0x0F, 1);      //显示开,开光标
}
#endif

/*********************************************************************
 原型: void flicker_LCD(uint pMs)
 功能: 全屏闪烁
 参数: pMs  闪烁间隔的毫秒数
*********************************************************************/
#ifdef NEED_FLICKER_LCD12864
void flicker_LCD(uint pMs)
{
   cmd_LCD12864(0x08, pMs);
   cmd_LCD12864(0x0c, pMs);
   cmd_LCD12864(0x08, pMs);
   cmd_LCD12864(0x0c, pMs);
}
#endif

/*********************************************************************
 原型: void image_LCD(uchar *pBmp)
 功能: 在指定位置开始显示指定字符串
 参数: x    横向坐标
       y    纵向坐标
*********************************************************************/
#ifdef NEED_IMAGE_LCD12864
/*void image_LCD(uchar *pBmp)
{
	uchar i=0, j=0;

	cmd_LCD12864(0x34, 0);        //扩充指令

	for(i=0; i<32; i++)
	{
		cmd_LCD12864(0x80+i, 0);    //先写入水平坐标值
		cmd_LCD12864(0x80, 0);      //写入垂直坐标值
		for(j=0; j<16; j++)            //再写入两个8位元的数据
			data_LCD12864(*pBmp++, 0);
	}

	for(i=0; i<32; i++)
	{
		cmd_LCD12864(0x80+i, 0);
		cmd_LCD12864(0x88, 0);
		for(j=0; j<16; j++)
			data_LCD12864(*pBmp++, 0);
	}
	cmd_LCD12864(0x36, 1);       //写完数据,开图形显示
}*/
void image_LCD(uint x, uint y, uint w, uint h, uchar *pBmp)
{
	uchar i=0, j=0;
	uchar y1=0, y2=0;

	cmd_LCD12864(0x34, 0);        //扩充指令

	//上半屏
	if( y<32 )  //需要在上半屏显示
	{
		y1 = y;
		if( (y+h)<32 )
			y2 = y + h;
		else
			y2 = 32;
		for(i=y1; i<y2; i++)
		{
			cmd_LCD12864(0x80+i, 0);         //先写水平坐标值
			cmd_LCD12864(0x80+(x/8), 0);     //再写垂直坐标值
			for(j=0; j<(w/8); j++)            //写入数据
				data_LCD12864(*pBmp++, 0);
		}
	}

	//下半屏
	if( 32<=(y+h) )  //需要在下半屏显示
	{
		if( y < 32 )
		{
			y1 = 0;
		}
		else
		{
			y1 = y - 32;
		}
		y2 = y + h - 32;
		for(i=y1; i<y2; i++)
		{
			cmd_LCD12864(0x80+i, 0);
			cmd_LCD12864(0x88+(x/8), 0);
			for(j=0; j<(w/8); j++)
				data_LCD12864(*pBmp++, 0);
		}
	}

	cmd_LCD12864(0x36, 1);       //写完数据,开图形显示
}
#endif
