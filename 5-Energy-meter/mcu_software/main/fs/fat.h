#ifndef _FAT_H_
#define _FAT_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_system.h"
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
void initSpiFat(void);
void initSdCard(void);
int8_t fat_writeToFile(char *fname, uint8_t *data, uint32_t size);
int8_t fat_readFromFile(char *fname, uint8_t *data, uint32_t size);

#endif