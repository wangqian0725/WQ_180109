#ifndef __HX711_H__
#define __HX711_H__

#include "coon_def.h"

/* ���ӳ� */

#define VERSION_HX711  "HX711 V4.0 160414"   //����100KG֧��

//#define HX711_40KG     //40������ӳ�
#define HX711_100KG    //100������ӳ�

void init_HX711();        //ִ�г�ʼ��
ulng getWeight_HX711();   //����, ������Ʒ����, ��λ��

#endif  //__HX711AD_H__
