#ifndef _DUPLICATE_H_
#define _DUPLICATE_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
//rand in u64
#ifdef __cplusplus
extern "C" {
#endif
void duplicateFile(char *fname, char *outName, uint64_t times);
void extractFile(char *fname, char *outName, uint64_t extLen);
void extractStock(char *fname, char *outName, uint64_t extLen);
uint8_t *loadByteFile(char *fname, uint32_t *lenP);
int8_t writeByteFileAppend(char *fname, uint32_t size, uint8_t *data);
int8_t writeByteFile(char *fname, uint32_t size, uint8_t *data);
#ifdef __cplusplus
}
#endif
#endif