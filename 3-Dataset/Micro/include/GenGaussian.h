#ifndef _GENGAUSSIAN_H_
#define _GENGAUSSIAN_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <tonymathlib/mathtype.h>
#ifdef __cplusplus
extern "C" {
#endif
uint64_t gaussian64(double mu, double sigma);
uint32_t gaussian32(double mu, double sigma);
void genGaussian32Bin(char *fname, double sigma, uint64_t times);
void genGaussian64Bin(char *fname, double sigma, uint64_t times);
void genGaussianFloatBin(char *fname, double sigma, uint64_t times);
void genGaussian32Csv(char *fname, double sigma, uint64_t times);
void genGaussian64Csv(char *fname, double sigma, uint64_t times);
#ifdef __cplusplus
}
#endif
#endif