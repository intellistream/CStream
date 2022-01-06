#ifndef _INADC_H_
#define _INADC_H_
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include <stdint.h>
#define DEFAULT_VREF    1149

#define NO_OF_SAMPLES   8          //Multisampling
typedef struct HEARTBEAT {
  uint16_t BPM;                     // used to hold the pulse rate
  uint32_t Signal;                 // holds the incoming raw data
  uint16_t IBI;             // holds the time between beats, must be seeded!
  uint8_t Pulse;    // true when pulse wave is high, false when it's low
  uint8_t QS;        // becomes true when Arduoino finds a beat.
  int16_t rate[10];                      // array to hold last ten IBI values
  uint32_t sampleCounter;           // used to determine pulse timing
  uint32_t lastBeatTime;           // used to find IBI
  int16_t Peak;                     // used to find peak in pulse wave, seeded
  int16_t Trough;                       // used to find trough in pulse wave, seeded
  int16_t thresh;                  // used to find instant moment of heart beat, seeded
  int16_t amp;                  // used to hold amplitude of pulse waveform, seeded
  uint8_t firstBeat;          // used to seed rate array so we startup with reasonable BPM
  uint8_t secondBeat;      // used to seed rate array so we startup with reasonable BPM
  uint8_t order;
} HEARTBEAT;
void initAdc0(void);
uint32_t getAdc0(void);
void initAdc1(void);
uint32_t getAdc1(void);
void heartbeat_init(HEARTBEAT *hb);
HEARTBEAT *heartbeat_new(void);
void heartbeat_refresh(uint32_t value, HEARTBEAT *hb);
#endif
