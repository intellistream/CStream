#ifndef _MATHTYPE_H_
#define _MATHTYPE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "mathsetting.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define OUT printf
#ifndef u8
typedef uint8_t u8;
#endif
#ifndef m8
typedef int8_t m8;
#endif
#ifndef u16
typedef uint16_t u16;
#endif
#ifndef m16
typedef int16_t m16;
#endif
#ifndef u32
typedef uint32_t u32;
#endif
#ifndef m32
typedef int32_t m32;
#endif
#ifndef m64
typedef int64_t m64;
#endif
#ifndef u64
typedef uint64_t u64;
#endif
#ifndef sdot//单精度浮点 
typedef float sdot;
#endif
#ifndef ddot//单精度浮点 
typedef double ddot;
#endif

typedef struct MATRIX {

  u32 column, row;
  ddot **content;
} MATRIX;

typedef struct MATRIX_BIN_HEAD {
  u32 column, row;
} MATRIX_BIN_HEAD;
//数学函数定义 
ddot sqrt(ddot num);
ddot curt(ddot num);
ddot pow(ddot num, ddot m);
ddot epow(ddot num);
ddot ln(ddot num);
ddot sin(ddot num);
ddot arcsin(ddot num);
ddot cos(ddot num);
ddot arccos(ddot num);
ddot tan(ddot num);
ddot arctan(ddot num);
ddot sinh(ddot num);
ddot cosh(ddot num);
ddot tanh(ddot num);
ddot asin(ddot num);
//其它类型
ddot tabs(ddot a);
m64 tfix(ddot a);
m64 tround(ddot a);
ddot trem(ddot a, ddot b);
ddot tsrand(u64 seed);
ddot trand(void); //0~1 均匀分布
ddot tgaussian(void);//N(0,1) 高斯
//矩阵功能的定义
void matrix_out(MATRIX *m);
void tvector_out(ddot *vec, u32 n);
/*因为输出的都是新矩阵，所以务必做好内存释放的工作*/
MATRIX *matrix_new_zero(u32 row, u32 column);//零矩阵
MATRIX *matrix_new_null(u32 row, u32 column);//未初始化的矩阵
MATRIX *matrix_new_i(u32 n);//n维单位矩阵 
MATRIX *matrix_copy(MATRIX *m);//复制m的数值并生成新矩阵 
u32 matrix_free(MATRIX *m);
MATRIX *matrix_trans(MATRIX *m);//转置 
MATRIX *matrix_add(MATRIX *m, MATRIX *n);//加法
MATRIX *matrix_cacuEle(MATRIX *m, MATRIX *n, uint8_t type);//对应元素四则运算
MATRIX *matrix_opNum(MATRIX *m, ddot num, uint8_t type);//对应元素与数字四则运算
u32 matrix_change_r(MATRIX *m, u32 a, u32 b);//行交换
u32 matrix_change_c(MATRIX *m, u32 a, u32 b);//列交换
MATRIX *matrix_dot(MATRIX *m, MATRIX *n);//点乘
MATRIX *matrix_inv(MATRIX *naturalmat);//求逆
u32 matrix_diy(ddot (*func)(ddot), MATRIX *m);//用自定函数对矩阵的每一个元素进行处理

MATRIX *matrix_diy2(MATRIX *a, MATRIX *b, ddot (*func)(ddot, ddot));
MATRIX *matrix_diy2_d(MATRIX *a, MATRIX *b, ddot (*func)(ddot, ddot));
/*注意，矩阵不同于数a=matrix_xxxx(a)的用法会造成内存浪费
因此，下面的这些函数尤为重要*/
MATRIX *matrix_add_d(MATRIX *m, MATRIX *n);//加法并 破坏原有矩阵m
MATRIX *matrix_cacuEle_d(MATRIX *m, MATRIX *n, uint8_t type); //对应元素四则运算并 破坏原有矩阵m
MATRIX *matrix_opNum_d(MATRIX *m, ddot num, uint8_t type);//对应元素与数字四则运算 破坏
MATRIX *matrix_trans_d(MATRIX *m);//转置并销毁原有的矩阵 
MATRIX *matrix_dot_d(MATRIX *m, MATRIX *n);//点乘并销毁原有矩阵m
MATRIX *matrix_inv_d(MATRIX *m);//求逆并销毁原有矩阵 
//高级功能
ddot *matrix_meanRow(MATRIX *m);
ddot *matrix_meanCol(MATRIX *m);
ddot tvector_avg(ddot *v, u32 n);
MATRIX *matrix_cov(MATRIX *m);
MATRIX *matrix_lowTriangle(MATRIX *m);
MATRIX *matrix_lowTriangle_d(MATRIX *m);
//字符和二进制io
//bin 支持
u8 matrix_toExistBin(MATRIX *m, u8 *binData);
u8 *matrix_toNewBin(MATRIX *m);
MATRIX *matrix_fromBin(u8 *binData, u64 readLen);
u64 matrix_binSize(MATRIX *m);
u64 binHeader_expectSize(MATRIX_BIN_HEAD *header);
//std ascil file 支持
u8 matrix_toStdAscFile(MATRIX *m, m8 *fname);
MATRIX *matrix_fromStdAscFile(m8 *fname);

MATRIX *matrix_fromOctaveStyle(m8 *ostring);
MATRIX *matrix_fromLineString(m8 *lineString, u32 len);
m8 *string_fromMatrix(MATRIX *a);
ddot tstr2ddot(m8 *str);
#ifdef __cplusplus
}
#endif

#endif
