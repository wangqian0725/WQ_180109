#include "HCSR04.h"
#include "coon.h"
#include <reg52.h>

sbit echo_HCSR04=P1^5;
sbit trig_HCSR04=P1^4;
bit  flag_HCSR04=0;

/*********************************************************************
 原型: float read_HCSR04()
 功能: 执行一次距离测量,并返回测量结果
 返回: 测量到的距离, 单位为厘米
*********************************************************************/
float read_HCSR04()
{
	float s=0.0;

	TMOD = (TMOD & 0xF0) | 0x01;
	ET0 = 1;  //允许T0中断
	TH0 = 0;
	TL0 = 0;

	trig_HCSR04 = 1;
	delay_20us();
	trig_HCSR04 = 0;
	
	while(!echo_HCSR04);   //当RX为零时等待
	TR0=1;                 //开启计数
	while(echo_HCSR04);    //当RX为1计数并等待
	TR0=0;                 //关闭计数

	if(flag_HCSR04 == 0)         //超出测量
	{
		s = ((TH0*256+TL0)*1.87)/100;  //算出来是CM
		if( s < 10 ) 
			s = s - 0.4;
		else if( s < 20 )
			s = s - 0.8;
	}
	else
	{
		flag_HCSR04 = 0;
	}
	return s;
}

/*********************************************************************
 原型: float get_HCSR04()
 功能: 将9次测量结果排序,取中间1次
*********************************************************************/
float get_HCSR04()
{
	int i=0, j=0, m=0;
	float xdata dat[9]={0};

	for(i=0; i<9; i++)
	{
		dat[i] = read_HCSR04();
		delay_ms(20);
	}

	for(i=0; i<8; i++)
	{
		for(j=i; j<9; j++)
		{
			if( dat[j] < dat[i] )
			{
				m = dat[i];
				dat[i] = dat[j];
				dat[j] = m;
			}
		}
	}	
	return dat[4];
}

/*********************************************************************
 原型: void interrupt_HCSR04()
 功能: 中断程序, 测量失败时触发
*********************************************************************/
void interrupt_HCSR04() interrupt 1
{
	flag_HCSR04 = 1; //中断溢出标志
}

