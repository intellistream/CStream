#include "nvs.h"
#include "o12864.h"
void initNvs(void) {
  char str[64];
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }

}
int32_t readConfigI32(const char *key) {
  esp_err_t err;
  nvs_handle my_handle;
  int32_t readv;
  nvs_open("cfg", NVS_READONLY, &my_handle);
  nvs_get_i32(my_handle, key, &readv);
  nvs_close(my_handle);
  return readv;
}
void writeConfigI32(const char *key, int32_t value) {
  nvs_handle my_handle;
  nvs_open("cfg", NVS_READWRITE, &my_handle);
  nvs_set_i32(my_handle, key, value);
  nvs_commit(my_handle);
  nvs_close(my_handle);
}
size_t readConfigStr(const char *key, char *out_value) {
  nvs_handle my_handle;
  size_t len;
  nvs_open("cfg", NVS_READONLY, &my_handle);
  nvs_get_str(my_handle, key, out_value, &len);
  // nvs_commit(my_handle);
  nvs_close(my_handle);
  return len;
}
void writeConfigStr(const char *key, char *out_value) {
  nvs_handle my_handle;
  size_t len;
  nvs_open("cfg", NVS_READWRITE, &my_handle);
  nvs_set_str(my_handle, key, out_value);
  nvs_commit(my_handle);
  nvs_close(my_handle);
}