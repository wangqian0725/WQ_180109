#ifndef __HX711_H__
#define __HX711_H__

#include "coon_def.h"

/* 电子称 */

#define VERSION_HX711  "HX711 V4.0 160414"   //增加100KG支持

//#define HX711_40KG     //40公斤电子称
#define HX711_100KG    //100公斤电子称

void init_HX711();        //执行初始化
ulng getWeight_HX711();   //称重, 返回物品重量, 单位克

#endif  //__HX711AD_H__
