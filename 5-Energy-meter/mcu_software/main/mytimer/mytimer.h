#ifndef _MYTIMER_H_
#define _MYTIMER_H_
#include <stdio.h>
#include "esp_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#define TIMER_DIVIDER         16  //  Hardware timer clock divider
#define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds

typedef struct {
  int type;  // the type of timer's event
  int timer_group;
  int timer_idx;
  uint64_t timer_counter_value;
} timer_event_t;

void initTimerx(int timer_idx, double ms);
bool timer_group0_isr(void *para);
void t0Isr(void);
void t1Isr(void);

#endif

