#ifndef _SETTING_H
#define _SETTING_H
#define ACCURACY 1e-12//精度 
#define ERRORCODE printf("error!")//错误代码 
#define PI 3.1415926535897932//圆周率取值 
#define STHNEW(n) malloc(n)//内存分配函数的名字
#define  STHFREE(n, p) free(n)

#define testmodule
/*如果要使用硬件优化,则在本文件中添加硬件优化的代码,
并根据需要打开下面的宏定义开关 */
/*警告:这只是用于x86平台的配置选项*/
#define HARDWARE_SQRT 1
//#define HARDWARE_POW 
//#define HARDWARE_LN 
#define HARDWARE_SIN 1
#define HARDWARE_COS 1
//#define HARDWARE_ARCSIN
//#define HARDWARE_ARCTAN
//#define HARDWARE_SINH
#define DEBUG_MODE
#ifdef DEBUG_MODE
#define SYS_OUT printf
#else
void virPrintf(const char *__fmt, ...);
#define SYS_OUT virPrintf
#endif
#endif
