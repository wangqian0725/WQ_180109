
#ifndef __INDEPKEY_H__
#define __INDEPKEY_H__

/*
   说明: 此驱动的按键原理为按键闭合时低电平导通
*/

#include "coon_def.h"

#define VERSION_INDEPKEY "IndepKey V4.0 150912"

//检查当前是否有独立按键被按下,释放按键时返回对应的按键序号,序号定义见keys.h
uchar getkey_IndepKey();

#endif  //__INDEPKEY_H__

