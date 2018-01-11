#include "IndepKey.h"
#include "coon_def.h"
#include "coon.h"
#include "keys.h"
#include <reg52.h>

sbit indep_key_1=P3^6;
sbit indep_key_2=P3^7;

/*********************************************************************
 ԭ��: uchar getkey_IndepKey()
 ����: ��⵱ǰ�Ƿ��ж�����������
 ����: ���µĶ����������(1..n),û�а����򷵻�0
*********************************************************************/
uchar getkey_IndepKey()
{
	//����1
	if( indep_key_1 == 0 )       //��⵽��������(����)
	{
		delay_ms(10);          //�ӳ�10ms,����ʱ����ȥ��
		if( indep_key_1 == 0 )        //��⵽�͵�ƽ,ȷ���а�������
		{
			while( indep_key_1 == 0 ) ;  //�ȴ������ͷ�
			return STD_KEY_IDX_1;
		}
	}

	//����2
	if( indep_key_2 == 0 )       //��⵽��������(����)
	{
		delay_ms(10);          //�ӳ�10ms,����ʱ����ȥ��
		if( indep_key_2 == 0 )        //��⵽�͵�ƽ,ȷ���а�������
		{
			while( indep_key_2 == 0 ) ;  //�ȴ������ͷ�
			return STD_KEY_IDX_2;
		}
	}

	return 0;
}