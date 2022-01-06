#include "mykeys.h"
#include "ledfade.h"
uint16_t g_k1Time;
uint8_t isK1Isr;
uint8_t g_fadeSt = 0;
#include "myusb.h"
#define LEDC_TEST_DUTY         (4000)
#define LEDC_TEST_FADE_TIME    (2000)
TaskHandle_t ledTask;
ledc_channel_config_t ledc_channel =
    {
        .channel    = LEDC_LS_CH0_CHANNEL,
        .duty       = 0,
        .gpio_num   = LEDC_LS_CH0_GPIO,
        .speed_mode = LEDC_LS_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_LS_TIMER,
        .intr_type  = LEDC_INTR_FADE_END,
    };
ledc_timer_config_t ledc_timer = {
    .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
    .freq_hz = 5000,                      // frequency of PWM signal
    .speed_mode = LEDC_LS_MODE,           // timer mode
    .timer_num = LEDC_LS_TIMER,            // timer index
    .clk_cfg = LEDC_AUTO_CLK,              // Auto select the source clock
};
static xQueueHandle gpio_evt_queue = NULL;
static void IRAM_ATTR
gpio_isr_handler(void *arg) {
  uint32_t gpio_num = (uint32_t) arg;
  xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void gpio_task_example(void *arg) {
  uint32_t io_num;
  for (;;) {
    if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
      //printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
      switch (io_num) {
        case MYKEY1:printf("k1 down\r\n");
          startMes();
          break;
        case MYKEY2:printf("k2 down\r\n");

          break;
        case MYKEY3:printf("k3 down\r\n");
          stopMes();
          break;
        default:break;
      }
    }
  }
}
void led_task_example(void *arg) {
  stopShow();
  while (1) {
    ledc_set_fade_with_time(ledc_channel.speed_mode,
                            ledc_channel.channel, LEDC_TEST_DUTY, LEDC_TEST_FADE_TIME);
    ledc_fade_start(ledc_channel.speed_mode,
                    ledc_channel.channel, LEDC_FADE_NO_WAIT);
    vTaskDelay(LEDC_TEST_FADE_TIME / portTICK_PERIOD_MS);

    ledc_set_fade_with_time(ledc_channel.speed_mode,
                            ledc_channel.channel, 0, LEDC_TEST_FADE_TIME);
    ledc_fade_start(ledc_channel.speed_mode,
                    ledc_channel.channel, LEDC_FADE_NO_WAIT);
    vTaskDelay(LEDC_TEST_FADE_TIME / portTICK_PERIOD_MS);
  }

}
void mykeys_init(void) {
  uint64_t tv = 1;
  tv = tv << 18;
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_NEGEDGE;
  //bit mask of the pins, use GPIO4/5 here
  io_conf.pin_bit_mask = MYKEYS_SEL | tv;
  io_conf.pull_down_en = 0;
  //set as input mode
  io_conf.mode = GPIO_MODE_INPUT;
  //enable pull-up mode
  io_conf.pull_up_en = 1;
  gpio_config(&io_conf);
  //create a queue to handle gpio event from isr
  gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
  //install gpio isr service
  gpio_install_isr_service(0);
  ledFade_init();
  printf("fade done\r\n");
  gpio_isr_handler_add(MYKEY1, gpio_isr_handler, (void *) MYKEY1);
  gpio_isr_handler_add(MYKEY2, gpio_isr_handler, (void *) MYKEY2);
  gpio_isr_handler_add(MYKEY2, gpio_isr_handler, (void *) MYKEY3);
  xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
  //  gpio_isr_handler_add(MYKEY3, key3_isr_handler, (void*) MYKEY3);
  g_k1Time = 0;
}

void ledFade_init(void) {
  int ch;

  /*
   * Prepare and set configuration of timers
   * that will be used by LED Controller
   */

  // Set configuration of timer0 for high speed channels
  ledc_timer_config(&ledc_timer);
  //ledc_channel
  ledc_channel_config(&ledc_channel);
  ledc_fade_func_install(0);
  ledc_set_fade_with_time(ledc_channel.speed_mode,
                          ledc_channel.channel, LEDC_TEST_DUTY, LEDC_TEST_FADE_TIME);
  ledc_fade_start(ledc_channel.speed_mode,
                  ledc_channel.channel, LEDC_FADE_NO_WAIT);

  xTaskCreate(led_task_example, "led_task_example", 4096, NULL, 10, &ledTask);
}
void startShow() {
  vTaskResume(ledTask);
  ledc_timer_resume(ledc_channel.speed_mode, LEDC_LS_TIMER);
}

void stopShow() {
  vTaskSuspend(ledTask);
  ledc_timer_pause(ledc_channel.speed_mode, LEDC_LS_TIMER);

}