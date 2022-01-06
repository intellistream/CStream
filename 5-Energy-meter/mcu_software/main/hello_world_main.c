/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "lcd.h"
#include "ina226.h"
#include "mykeys.h"
#include "mytimer.h"

extern uint8_t g_workSt;
extern double g_power, g_peak;
//#include "ble_spp_server_demo.h"
#include "myusb.h"
//gaia
#include <stdint.h>
#include "driver/temp_sensor.h"
uint16_t g_runTime = 0;
uint16_t g_isrTime = 0;
uint16_t g_isrTimeP = 0;
uint8_t g_isTxData = 0;
uint16_t g_ly68Id = 0;
double g_i0, g_v0, g_i1, g_v1, g_w1;

temp_sensor_config_t temp_sensor;

void tempSensor_init(void) {
  temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
  temp_sensor_get_config(&temp_sensor);
  // ESP_LOGI(TAG, "default dac %d, clk_div %d", temp_sensor.dac_offset, temp_sensor.clk_div);
  temp_sensor.dac_offset = TSENS_DAC_DEFAULT; // DEFAULT: range:-10℃ ~  80℃, error < 1℃.
  temp_sensor_set_config(temp_sensor);
  temp_sensor_start();
}
float tsens_out;
void t0Isr(void) {
  //while (g_isrTimeP==1);
  g_isrTimeP = 1;

}
void sys_display(void) {
  char str[64];


  //g_isrTime=0;
}
void t1Isr(void) {
  //sys_display();
}
void app_main() {
//    printf("Hello world!\n");
  uint8_t tru, pru;
  esp_chip_info_t chip_info;

  char fatRead[64];
  char pRead, NowRead;
  char str[64];

  lcd_init();

  ina226_init1();

  myusb_init();
  mykeys_init();
//tempSensor_init();
  //xTaskCreate(usb_thread, "sockcli", 4096, NULL, 5, NULL);

  g_isrTimeP = 0;
  g_isrTime = 0;
  ina226_writeReg(1, 5, 2560);
  /*sprintf(str,"%x,%x,%f",ina226_readReg(1,0),ina226_readReg(1,0xfe),ina226_getV(1));
  lcd_showString(0,20,(unsigned char*)str,YELLOW);*/
  lcd_showString(0, 50, (unsigned char *) "INA226 power meter", YELLOW);
  //initTimerx(TIMER_1,1000.0);
  //delay_ms(1000);
  initTimerx(TIMER_0, 1.0);
  //TickType_t lasttick = xTaskGetTickCount();
  while (1) {
    if (g_isrTimeP == 0) {
      continue;
    }
    g_isrTime++;
    g_v1 = ina226_getV(1);
    g_i1 = ina226_getI(1);
    g_w1 = ina226_getW(1);
    anaPower();
    if (g_isrTime == 1000) {
      // temp_sensor_read_celsius(&tsens_out);
      g_runTime++;
      g_isrTime = 0;

      if (g_workSt) {
        sprintf(str, "R:%6.2lf J,peak=%6.2f mW", g_power, g_peak);
      } else {
        sprintf(str, "S:%6.2lf J,peak=%6.2f mW", g_power, g_peak);
      }
      // temp_sensor_read_celsius(&tsens_out);
      //	OLED_ShowString(0,10,(unsigned char *)str);
      lcd_showString(0, 70, (unsigned char *) str, YELLOW);
      sprintf(str, "U=%6.2f mV       ", g_v1);
      lcd_showString(0, 10, (unsigned char *) str, YELLOW);
      sprintf(str, "I=%6.2f mA        ", g_i1);
      lcd_showString(0, 30, (unsigned char *) str, YELLOW);
      sprintf(str, "P=%6.2f mW        ", g_w1);
      lcd_showString(0, 50, (unsigned char *) str, YELLOW);

      //sys_display();//
    }
    g_isrTimeP = 0;

    //vTaskDelayUntil(&lasttick, 1);
    //  delay_ms(1);
    /*	*/




    //  printf("t=%d",g_runTime);
    // g_runTime++;
  }

}

#define BLINK_GPIO 21
/*
void app_main(void)
{
   
    gpio_reset_pin(BLINK_GPIO);
    
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
       
        printf("Turning off the LED\n");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
       
        printf("Turning on the LED\n");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
*/
