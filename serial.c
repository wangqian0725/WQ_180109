#include "serial.h"
#include "coon.h"
#include <reg52.h>

/*
	ʹ���˴����ж�,��ʱ��1�ж�
    ��ʱ����ֵ���㹫ʽ:
	x = 2^n - (2^SMOD * fosc) / (32 * bps * 12 )
	        n: �����շ�������λ��
            SMOD: �����ʼӱ�λ��(PCON.7)
    x = 2^8 - (2^0 * 11.0592 * 10^6) / ( 32 * 9600 * 12) = 253 = 0xFD
	x = 2^8 - (2^0 * 12 * 10^6) / ( 32 * 9600 * 12 ) =
*/

uchar buff_serial[MAXLEN_BUFF_SERIAL]={0};
uchar pwrite_serial=0, pread_serial=0;

/*********************************************************************
 ԭ��: void init_serial()
 ����: ��ʼ������
*********************************************************************/
void init_serial()
{
	//�ö�ʱ��1������8λ�Զ�����ģʽ,���ڲ���������(�����ֶ�ʱ��0��Ϣλ������)
	TMOD = (TMOD & 0x0F) | 0x20;
	//�����ʲ�����(�������Ǵ�����Ϣλ������)
	PCON = PCON & 0x7F;
	//8λURT,�����ʿɱ�,(T1�����/n),�������
    SCON = 0x50;
	//������9600
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

	ES = 1;         //(IE.4)�������ж�

	//������ʱ��1
    TR1 = 1;
}

/*********************************************************************
 ԭ��: void write_serial(uchar *pStr, int pStrLen)
 ����: ��������
*********************************************************************/
#ifdef NEED_WIRTE_SERIAL
/*********************************************************************
 ԭ��: void writebyte_serial(uchar dat)
 ����: �򴮿ڷ���һ�ֽ�����
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
 ԭ��: void clear_serial()
 ����: ��մ��ڻ���
*********************************************************************/
#ifdef NEED_CLEAR_SERIAL
void clear_serial()
{
	pread_serial = pwrite_serial;
}
#endif

/*********************************************************************
 ԭ��: uchar read_serial(uchar *pStr)
 ����: �Ӵ��ڻ����ȡ����
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
 ԭ��: uchar read2_serial(uchar *pStr)
 ����: ����������,����������
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

//�����жϺ���, �����ݵ����ڻ���
void interrupt_serial() interrupt 4
{
	ES = 0;                //�رմ����ж�
	RI = 0;                //������н��ձ�־λ

	buff_serial[pwrite_serial] = SBUF;  //�Ӵ��ڻ�����ȡ������
	pwrite_serial = (pwrite_serial + 1) % MAXLEN_BUFF_SERIAL;

	ES = 1;    //�������ж�
}
