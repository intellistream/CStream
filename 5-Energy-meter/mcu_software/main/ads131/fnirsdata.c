#include "fnirsdata.h"
#include "mathtype.h"
void flipavgcore_init(FLIPAVGCORE *core, uint32_t len) {
  uint32_t i;
  core->buf = (int32_t *) malloc(len * sizeof(int32_t));
  core->len = len;
  core->pos = 0;
  for (i = 0; i < len; i++) {
    core->buf[i] = 0;
  }
}
uint32_t flipavgcore_update(FLIPAVGCORE *core, int32_t data) {

  int32_t i, maxpos, sum, avg;
  maxpos = core->len;
  int32_t max, min;
  int32_t *tbuf = core->buf;
  core->buf[core->pos++] = data;
  sum = 0;
  max = min = tbuf[0];
  for (i = 0; i < maxpos; i++) {
    if (tbuf[i] > max) {
      max = tbuf[i];
    }
    if (tbuf[i] < min) {
      min = tbuf[i];
    }
    sum += tbuf[i];
  }
  avg = sum / maxpos;
  if (core->pos == maxpos) {
    core->pos = 0;
  }
  return avg;
}
void fnirsdata_init(FNIRSDATA *fd, uint32_t bufLen) {
  uint8_t i;
  fd->waveLen = WLEN_645;
  for (i = 0; i < 8; i++) {
    flipavgcore_init(&fd->flps[i], bufLen);
  }
}
void fnirsdata_update(FNIRSDATA *fd) {
  readData(&fd->rawData);
  uint32_t t0, t1, t2, t3;

  if (fd->waveLen == WLEN_645) {
    t0 = flipavgcore_update(&fd->flps[FL_CH0645], fd->rawData.channel0);
    t1 = flipavgcore_update(&fd->flps[FL_CH1645], fd->rawData.channel1);
    t2 = flipavgcore_update(&fd->flps[FL_CH2645], fd->rawData.channel2);
    t3 = flipavgcore_update(&fd->flps[FL_CH3645], fd->rawData.channel2);
    fd->t0645 = t0;
    fd->t1645 = t1;
    fd->t2645 = t2;
    fd->t3645 = t3;
    fd->waveLen = WLEN_830;
    gpio_set_level(ADS_CH, 0);
  } else {
    t0 = flipavgcore_update(&fd->flps[FL_CH0830], fd->rawData.channel0);
    t1 = flipavgcore_update(&fd->flps[FL_CH1830], fd->rawData.channel1);
    t2 = flipavgcore_update(&fd->flps[FL_CH2830], fd->rawData.channel2);
    t3 = flipavgcore_update(&fd->flps[FL_CH3830], fd->rawData.channel2);
    fd->t0830 = t0;
    fd->t1830 = t1;
    fd->t2830 = t2;
    fd->t3830 = t3;
    fd->waveLen = WLEN_645;
    gpio_set_level(ADS_CH, 1);

  }

}
void fnirsdata_toExistBin(FNIRSDATA *fd, uint8_t *data) {
  int32_t *data32 = (int32_t *) data;
  data32[0] = fd->t0645;
  data32[1] = fd->t1645;
  data32[2] = fd->t2645;
  data32[3] = fd->t3645;
  data32[4] = fd->t0830;
  data32[5] = fd->t1830;
  data32[6] = fd->t2830;
  data32[7] = fd->t3830;
}