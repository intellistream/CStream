#include "wifi.h"
#include <string.h>
#include "o12864.h"
#include "nvs.h"
#include "fat.h"
#include "esp_pm.h"
#include "gaiacli.h"
#define WIFI_SSID "KKKKg"
#define WIFI_PASS "123456zzz"
#define DEFAULT_PS_MODE WIFI_PS_MIN_MODEM
char g_cliIp[64];
int isConnected = 0;
const int WIFI_CONNECTED_BIT = BIT0;
void wifi_setStaAttr(wifi_config_t *cfg, uint8_t *ssid, uint8_t *passwd) {
  uint32_t ssidLen = 32;
  uint32_t i;
  if (ssidLen > MAX_SSID_LEN) {
    ssidLen = MAX_SSID_LEN;
  }
  uint32_t passwdLen = 64;
  if (passwdLen > MAX_PASSWD_LEN) {
    passwdLen = MAX_PASSWD_LEN;
  }
  for (i = 0; i < ssidLen; i++) {
    cfg->sta.ssid[i] = ssid[i];
  }
  cfg->sta.ssid[ssidLen - 1] = 0;
  for (i = 0; i < passwdLen; i++) {
    cfg->sta.password[i] = passwd[i];
  }
  cfg->sta.password[passwdLen - 1] = 0;
}
void wifi_setApAttr(wifi_config_t *cfg, uint8_t *ssid, uint8_t *passwd, uint8_t con) {
  uint32_t ssidLen = strlen((char *) ssid);
  uint32_t i;
  if (ssidLen > MAX_SSID_LEN) {
    ssidLen = MAX_SSID_LEN;
  }
  uint32_t passwdLen = strlen((char *) passwd);
  if (passwdLen > MAX_PASSWD_LEN) {
    passwdLen = MAX_PASSWD_LEN;
  }
  for (i = 0; i < ssidLen; i++) {
    cfg->ap.ssid[i] = (char) ssid[i];
  }
  cfg->ap.ssid[ssidLen] = 0;
  for (i = 0; i < passwdLen; i++) {
    cfg->ap.password[i] = (char) passwd[i];
  }
  cfg->ap.password[passwdLen] = 0;
  cfg->ap.max_connection = con;
  cfg->ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
}
static EventGroupHandle_t s_wifi_event_group;

static const char *TAG = "wifi softAP";
uint8_t g_ifWlanOk = 0;

static esp_err_t event_handler(void *ctx, system_event_t *event) {
  unsigned char str[64];
  switch (event->event_id) {
    case SYSTEM_EVENT_AP_STACONNECTED:
      ESP_LOGI(TAG, "station:"
      MACSTR
      " join, AID=%d",
          MAC2STR(event->event_info.sta_connected.mac),
          event->event_info.sta_connected.aid);
      /* netserver_init(&g_netServer,8217,(int8_t *)"192.168.4.1");
netserver_establishV4(&g_netServer); */
      OLED_ShowString(0, 40, (uint8_t *) "configuring");
      break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:

      break;
    case SYSTEM_EVENT_STA_START:
      //  ESP_LOGI(TAG, "SYSTEM_EVENT_STA_START");
      esp_wifi_connect();
      OLED_ShowString(0, 18, (unsigned char *) ("STA START"));
      break;
    case SYSTEM_EVENT_STA_GOT_IP:ESP_LOGI(TAG, "SYSTEM_EVENT_STA_GOT_IP");
      ESP_LOGI(TAG, "Got IP: %s\n",
               ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
      sprintf((char *) g_cliIp, "%s", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
      // OLED_ShowChar(0,16,'a');
      OLED_ShowString(0, 8, (unsigned char *) g_cliIp);
      isConnected = 1;
      xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
      gaiaCli_start();

      //g_ifWlanOk=1gaiaCli_start
      break;
    default:break;
  }
  return ESP_OK;
}

void wifi_init_sta() {
  s_wifi_event_group = xEventGroupCreate();

  tcpip_adapter_init();
  ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  /* wifi_config_t wifi_config = {
       .sta = {
           .ssid = "gaiaServer",
           .password = "k8k97gaia"
       },
   };*/
  wifi_config_t wifi_config = {
      .sta = {
          .ssid = "tonyserverU",
          .password = "tony753132"
      },
  };
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
  ESP_ERROR_CHECK(esp_wifi_start());

  ESP_LOGI(TAG, "wifi_init_sta finished.");
  //  ESP_LOGI(TAG, "connect to ap SSID:%s password:%s",
  //   EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
}

void wifi_init_softap(void) {
  s_wifi_event_group = xEventGroupCreate();

  tcpip_adapter_init();
  ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  wifi_config_t wifi_config = {
      .ap = {
          .ssid = "iomtconfig",
          .ssid_len = strlen("iomtconfig"),
          .password = "12345678",
          .max_connection = 4,
          .authmode = WIFI_AUTH_WPA_WPA2_PSK
      },
  };
  /* if (strlen(EXAMPLE_ESP_WIFI_PASS) == 0) {
       wifi_config.ap.authmode = WIFI_AUTH_OPEN;
   }*/
  //wifi_config_t wifi_config;
  uint8_t *nameTag, *ssidTag;
  uint8_t nameBuf[32], passwdBuf[64];
  if (fat_readFromFile("/spiflash/dn", nameBuf, 32) != 1) {
    fat_writeToFile("/spiflash/dn", (uint8_t *) "iconfig", 7);
    fat_readFromFile("/spiflash/dn", nameBuf, 32);

  }
  if (fat_readFromFile("/spiflash/dp", passwdBuf, 64) != 1) {
    fat_writeToFile("/spiflash/dp", (uint8_t *) "12345678", 8);
    fat_readFromFile("/spiflash/dp", passwdBuf, 8);
  }
  //  OLED_ShowString(0,48,(unsigned char*)nameBuf);
  // OLED_ShowString(0,48,(unsigned char*)passwdBuf);
  //wifi_setApAttr(&wifi_config,(uint8_t*)nameBuf,(uint8_t *)"12345678",4);

  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
  ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
  ESP_ERROR_CHECK(esp_wifi_start());
  esp_wifi_set_ps(DEFAULT_PS_MODE);
  /* netserver_init(&g_netServer,8217,(int8_t *)"192.168.4.1");
  netserver_establishV4(&g_netServer);*/
}
void wifi_init(void) {

  ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
  esp_wifi_set_storage(WIFI_STORAGE_FLASH);
  wifi_init_sta();
  //  wifi_init_softap();
}
void wifi_enterLowPower0(void) {

  esp_wifi_set_ps(DEFAULT_PS_MODE);
}

void wifi_enterNormalPower(void) {
  esp_wifi_set_ps(WIFI_PS_NONE);
}