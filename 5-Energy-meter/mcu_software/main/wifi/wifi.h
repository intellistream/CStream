#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <stdint.h>
#define MAX_SSID_LEN 32

#define MAX_PASSWD_LEN 64
void wifi_setStaAttr(wifi_config_t *cfg, uint8_t *ssid, uint8_t *passwd);
void wifi_setApAttr(wifi_config_t *cfg, uint8_t *ssid, uint8_t *passwd, uint8_t con);
void wifi_init(void);
void wifi_enterLowPower0(void);
void wifi_enterNormalPower(void);