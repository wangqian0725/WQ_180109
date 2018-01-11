#ifndef __LCD12864_H__
#define __LCD12864_H__

#include "coon_def.h"

#define VERSION_12864 "LCM12864 V4.0 150912"   //统一接口
//#define NEED_CLS_LCD12864       1   //是否需要清屏方法
//#define NEED_POS_LCD12864         1   //需要坐标设置方法,该方法必有
//#define NEED_CURSOR_LCD12864    1   //是否需要显示光标
//#define NEED_FLICKER_LCD12864   1   //全屏闪烁
//#define NEED_IMAGE_LCD12864     1   //图形显示

//初始化液晶,应用启动时调用
void init_LCD();
//从液晶指定行(0..n-1)的指定列(0..m-1)开始,显示指定的字符串,不处理换行
void show_str_LCD(uchar *pStr, uchar pLine, uchar pIdx);

#ifdef NEED_CLS_LCD12864   //清屏
	void cls_LCD();
#endif

#ifdef NEED_POS_LCD12864  //定位光标
	void pos_LCD(uchar pLine, uchar pIdx);
#endif

#ifdef NEED_CURSOR_LCD12864  //是否需要显示光标,pFlag=1显示光标, 0关闭光标
	void cursor_LCD(bit pFlag);
#endif

#ifdef NEED_FLICKER_LCD12864  //全屏闪烁
	void flicker_LCD(uint pMs);
#endif

#ifdef NEED_IMAGE_LCD12864  //图形显示
	void image_LCD(uint x, uint y, uint w, uint h, uchar *pBmp);
#endif

#endif

