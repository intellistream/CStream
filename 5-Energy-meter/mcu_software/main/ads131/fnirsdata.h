#include "ads131.h"
#include <stdint.h>
#define WLEN_645 0
#define WLEN_830 1
typedef struct FLIPAVGCORE {
  int32_t *buf;
  uint32_t len;
  uint32_t pos;
} FLIPAVGCORE;
void flipavgcore_init(FLIPAVGCORE *core, uint32_t len);
uint32_t flipavgcore_update(FLIPAVGCORE *core, int32_t data);
#define FL_CH0645 0
#define FL_CH1645 1
#define FL_CH2645 2
#define FL_CH3645 3
#define FL_CH0830 4
#define FL_CH1830 5
#define FL_CH2830 6
#define FL_CH3830 7
typedef struct FNIRSDATA {
  adc_channel_data rawData;
  int32_t t0830, t1830, t2830, t3830;
  int32_t t0645, t1645, t2645, t3645;
  FLIPAVGCORE flps[8];
  int8_t waveLen;
} FNIRSDATA;
void fnirsdata_init(FNIRSDATA *fd, uint32_t bufLen);
void fnirsdata_update(FNIRSDATA *fd);
void fnirsdata_toExistBin(FNIRSDATA *fd, uint8_t *data);