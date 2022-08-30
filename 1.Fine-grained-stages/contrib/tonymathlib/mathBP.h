#ifndef _MATHBP_H_
#define _MATHBP_H_
#include "mathtype.h"
#ifdef __cplusplus
extern "C" {
#endif
//一个隐藏层的BP管理器
typedef struct BPMRH1 {
  u32 layel0, layel1, layel2;//第0层为输出层，此变量为维数,layel2为输入维数
  MATRIX *w0;//第0层权值，对应y
  MATRIX *w1;//第1层权值,对应x
  ddot learnrate;//学习率
  ddot (*activateFunc)(ddot);//激活函数
  ddot (*derFunc)(ddot);//激活函数的导数
} BPMRH1;
BPMRH1 *bpmrh1_new(u32 outd, u32 hided, u32 ind, ddot learn);
void bpmrh1_free(BPMRH1 *bpmr);
MATRIX *bpmrh1_genoutput_r(BPMRH1 *bpmr, MATRIX *x, MATRIX *y);//产生输出的函数，x的维数为layel2
MATRIX *bpmrh1_genoutput(BPMRH1 *bpmr, MATRIX *x);//产生输出的函数，x的维数为layel2
ddot bpmrh1_trainsingle(BPMRH1 *bpmr, MATRIX *x, MATRIX *d);//训练单次,x和d的行数应当相同
//ddot bpmrh1_trainsingle(BPMRH1 *bpmr,MATRIX *x,MATRIX *d,ddot error,ddot maxturn);/*训练单个样本,x为输入行向量,
//d为输出预期行向量*/

#ifdef __cplusplus
}
#endif

#endif