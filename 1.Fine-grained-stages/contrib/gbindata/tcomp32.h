#ifndef _TCOMP32_H_
#define _TCOMP32_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif
uint32_t tcomp32_compress(uint8_t *source, uint8_t *dest, uint32_t len);
uint32_t tcomp32_decompress(uint8_t *source, uint8_t *dest, uint32_t len);
#ifdef __cplusplus
}
#endif

#endif