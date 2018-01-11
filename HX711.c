#include "HX711.h"
#include <reg52.h>
#include <intrins.h>

sbit CLK_HX711=P2^1;
sbit DAT_HX711=P2^0;

ulng g_ulEEmpty=0;   //����豸ë��

/*********************************************************************
 ԭ��: ulng read_HX711AD()
 ����: ��ȡģ�鷵�ص�24�ֽ�����
 ����: ����������
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
 ԭ��: void init_HX711AD()
 ����: ��ʼ��HX711AD, ȡ���豸ë��
*********************************************************************/
void init_HX711()
{
	g_ulEEmpty = read_HX711();
	g_ulEEmpty = g_ulEEmpty / 100;
}

/*********************************************************************
 ԭ��: ulng getWeight_HX711AD()
 ����: ����
*********************************************************************/
ulng getWeight_HX711()
{
	ulng ul;

	ul = read_HX711();
	ul = ul / 100;

	if(ul > g_ulEEmpty)
	{
		ul = ul - g_ulEEmpty;    //��ȡʵ���AD������ֵ��

		#ifdef HX711_40KG  //40����
		ul = (ulng)((float)ul / 1.07 + 0.05 ); 	//+0.05��Ϊ����������ٷ�λ
		#endif

		#ifdef HX711_100KG  //100����
		ul = (ulng)((float)ul * 2.4589 + 0.05 ); 	//+0.05��Ϊ����������ٷ�λ
		#endif

		return ul;
	}

	return 0;
}




