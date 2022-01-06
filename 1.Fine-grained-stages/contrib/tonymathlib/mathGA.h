#ifndef _MATHGA_H_
#define _MATHGA_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "mathtype.h"
typedef struct GACORE GACORE;
typedef struct GACORE{

u32 sizepop; // population amount
u32 maxgen;  //max generation allowed
ddot pcross ; // probility for cross
ddot pmutation ;//probility for mutation
u32 lenchrom ; // lenth of chromosome
MATRIX *each_chrom;//each entity's chromosome
ddot *each_fitness;
ddot *each_chosenp;//probility of chosen
ddot *best_chroms;
ddot *worst_chroms;
ddot *gen_best;
ddot gmax,gmin;
u32 gmax_index,gmin_index;
ddot bound_down ; // 
ddot bound_up;
ddot (*fitnessFunc)(ddot *chrom,u32 len);//the fuction of vector distance
m8 (*selectFunc)(GACORE *gacore);//the function for  single select,default is rou
m8 (*crossFunc)(GACORE *gacore);//the function for  single cross,default is randcross
m8 (*mutationFunc)(GACORE *gacore);//the function for  single cross,default is randcross
}GACORE;

//user-interface funtions
m8 GACORE_init(GACORE *gacore,u32 tsizepop,u32 tmaxgen,ddot tpcross ,ddot tpmutation ,u32 tlenchrom ,ddot tdown,ddot tup,\
ddot (*fitnessFunc)(ddot *chrom,u32 len));
void GACORE_deinit(GACORE *gacore);
m8 GACORE_runEvolution(GACORE *gacore);
//default process functions
m8 GACORE_singleRouSelect(GACORE *gacore);//轮盘赌,最大值
m8 GACORE_singleRouSelect_min(GACORE *gacore);//轮盘赌,最小值
m8 GACORE_singleRandCross(GACORE *gacore);//随机交叉
m8 GACORE_singleRandMutation(GACORE *gacore);//随机变异

#ifdef __cplusplus
 }
#endif
#endif