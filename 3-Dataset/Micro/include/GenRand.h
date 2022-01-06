#ifndef _GENRAND_H_
#define _GENRAND_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <tonymathlib/mathtype.h>
#ifdef __cplusplus
extern "C" {
#endif
//rand in u64
void genRandBin(char *fname, uint64_t maxRange, uint64_t times);
void genRandCsv(char *fname, uint64_t maxRange, uint64_t times);
void genFullRandFile(char *fname, uint64_t times);
#ifdef __cplusplus
}
#endif

#endif