#include "fat.h"

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "o12864.h"
void initSpiFat(void) {
  static const char *TAG = "example";
  esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiflash",
      .partition_label = NULL,
      .max_files = 100,
      .format_if_mount_failed = true
  };
  char str[64];
  // Use settings defined above to initialize and mount SPIFFS filesystem.
  // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
  esp_err_t ret = esp_vfs_spiffs_register(&conf);
  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      ESP_LOGE(TAG, "Failed to mount or format filesystem");
    } else if (ret == ESP_ERR_NOT_FOUND) {
      ESP_LOGE(TAG, "Failed to find SPIFFS partition");
    } else {
      ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
    }
    return;
  }
  size_t total = 0, used = 0;
  ret = esp_spiffs_info(NULL, &total, &used);
  if (ret != ESP_OK) {
    ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
  } else {
    ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    /*sprintf(str,"t=%d,u=%d", total, used);
     OLED_ShowString(0,48,(unsigned char*)str);*/
  }
}
//1 for success
int8_t fat_writeToFile(char *fname, uint8_t *data, uint32_t size) {
  FILE *f = fopen(fname, "wb");
  if (f == NULL) {

    return 0;
  }
  fwrite(data, size, 1, f);
  fclose(f);
  return 1;
}
int8_t fat_readFromFile(char *fname, uint8_t *data, uint32_t size) {
  FILE *f = fopen(fname, "rb");
  if (f == NULL) {

    return 0;
  }
  fread(data, size, 1, f);
  fclose(f);
  return 1;
}
#define PIN_NUM_MISO 22
#define PIN_NUM_MOSI 21
#define PIN_NUM_CLK  23
#define PIN_NUM_CS   25
void initSdCard(void) {

}