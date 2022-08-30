#ifndef _RDTSC_H_
#define _RDTSC_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
int rdtsc_init(void);
uint64_t rdtsc_new(void);
uint64_t rdtsc_ns(uint64_t before, uint64_t after);
uint64_t rdtsc_us(uint64_t before, uint64_t after);
uint64_t rdtsc_ms(uint64_t before, uint64_t after);
uint64_t rdtsc_s(uint64_t before, uint64_t after);

#ifdef __cplusplus
}
#endif
#endif