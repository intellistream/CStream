#ifndef _MYKEYS_H_
#define _MYKEYS_H_
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>
#include "esp_system.h"
#include "soc/gpio_struct.h"
#include "driver/gpio.h"
#include "freertos/queue.h"
#define MYKEY1 (16)
#define MYKEY2 (17)
#define MYKEY3 (18)
#define MYKEYS_SEL (1ULL<<MYKEY1)|(1ULL<<MYKEY2)|(1ULL<<MYKEY3)
void mykeys_init(void);

void key1_isr_handler(void *arg);
void key2_isr_handler(void *arg);
void key3_isr_handler(void *arg);
#endif