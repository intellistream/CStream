#ifndef _NVS_H_
#define _NVS_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
void initNvs(void);
int32_t readConfigI32(const char *key);
void writeConfigI32(const char *key, int32_t value);
size_t readConfigStr(const char *key, char *out_value);
void writeConfigStr(const char *key, char *out_value);
#endif