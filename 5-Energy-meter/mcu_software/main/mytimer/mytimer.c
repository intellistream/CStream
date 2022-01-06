#include "mytimer.h"
extern xQueueHandle s_timer_queue;
typedef struct {
  int timer_group;
  int timer_idx;
  int alarm_interval;
  bool auto_reload;
} example_timer_info_t;

/**
 * @brief A sample structure to pass events from the timer ISR to task
 *
 */
typedef struct {
  example_timer_info_t info;
  uint64_t timer_counter_value;
} example_timer_event_t;

void initTimerx(int timer_idx, double ms) {
  /* Select and initialize basic parameters of the timer */
  timer_group_t group = TIMER_GROUP_0;
  timer_config_t config = {
      .divider = TIMER_DIVIDER,
      .counter_dir = TIMER_COUNT_UP,
      .counter_en = TIMER_PAUSE,
      .alarm_en = TIMER_ALARM_EN,
      .auto_reload = true,
  }; // default clock source is APB
  double kv = ms * TIMER_SCALE / 1000.0;
  // uint64_t setv=(uint64_t)kv;
  timer_init(group, timer_idx, &config);
  timer_set_alarm_value(group, timer_idx, kv);
  timer_enable_intr(group, timer_idx);

  example_timer_info_t *timer_info = calloc(1, sizeof(example_timer_info_t));
  timer_info->timer_group = group;
  timer_info->timer_idx = timer_idx;
  timer_info->auto_reload = true;
  timer_info->alarm_interval = kv;
  timer_isr_callback_add(group, timer_idx, timer_group0_isr, timer_info, 0);

  timer_start(group, timer_idx);
}
bool IRAM_ATTR
timer_group0_isr(void *para) {
  example_timer_info_t *info = (example_timer_info_t *) para;
  if (info->timer_idx == TIMER_0) {
    t0Isr();
  } else if (info->timer_idx == TIMER_1) {
    t1Isr();
  }
  return true;
}

