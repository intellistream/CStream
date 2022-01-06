#include "inadc.h"

void heartbeat_init(HEARTBEAT *hb) {
  hb->IBI = 600;
  hb->Pulse = 0;
  hb->QS = 0;
  hb->sampleCounter = 0;
  hb->lastBeatTime = 0;
  hb->Peak = 512;
  hb->Trough = 512;
  hb->thresh = 512;
  hb->amp = 100;
  hb->firstBeat = 1;
  hb->secondBeat = 0;
  hb->order = 0;
}
HEARTBEAT *heartbeat_new(void) {
  HEARTBEAT *hb;
  hb = (HEARTBEAT *) calloc(1, sizeof(HEARTBEAT));
  heartbeat_init(hb);
  return hb;

}
void heartbeat_refresh(uint32_t value, HEARTBEAT *hb) {
  int16_t N;
  uint8_t i;
  uint32_t runningTotal = 0;
  hb->Signal = value;             // read the hb->Pulse Sensor
  hb->sampleCounter += 2;                          // keep track of the time in mS with this variable
  N = hb->sampleCounter - hb->lastBeatTime;      // monitor the time since the last beat to avoid noise


  //	find the hb->Peak and trough of the hb->Pulse wave
  if (hb->Signal<hb->thresh && N>(hb->IBI / 5) * 3) {      // avoid dichrotic noise by waiting 3/5 of last hb->IBI
    if (hb->Signal < hb->Trough) {                         // T is the hb->Trough
      hb->Trough = hb->Signal;                           // keep track of lowest point in hb->Pulse wave
    }
  }

  if (hb->Signal > hb->thresh && hb->Signal > hb->Peak) {         // hb->thresh condition helps avoid noise
    hb->Peak = hb->Signal;                               // P is the hb->Peak
  }                                       // keep track of highest point in hb->Pulse wave

  //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
  // hb->Signal surges up in value every time there is a hb->Pulse
  if (N > 250) {                                  // avoid high frequency noise
    if ((hb->Signal > hb->thresh) && (hb->Pulse == false) && (N > (hb->IBI / 5) * 3)) {
      hb->Pulse = true;                              // set the hb->Pulse flag when we think there is a hb->Pulse
      //		blinkPin=0; 			  // turn on pin 13 LED
      hb->IBI = hb->sampleCounter - hb->lastBeatTime;          // measure time between beats in mS
      hb->lastBeatTime = hb->sampleCounter;              // keep track of time for next hb->Pulse

      if (hb->secondBeat) {                         // if this is the second beat, if secondBeat == TRUE
        hb->secondBeat = 0;                 // clear secondBeat flag
        for (i = 0; i <= 9; i++) {             // seed the running total to get a realisitic BPM at startup
          hb->rate[i] = hb->IBI;
        }
      }

      if (hb->firstBeat) {                         // if it's the first time we found a beat, if firstBeat == TRUE
        hb->firstBeat = 0;                     // clear firstBeat flag
        hb->secondBeat = 1;                     // set the second beat flag
        // EA=1; 							  // enable interrupts again
        return;                               // hb->IBI value is unreliable so discard it
      }

      for (i = 0; i <= 8; i++) {                  // shift data in the rate array
        hb->rate[i] = hb->rate[i + 1];                  // and drop the oldest hb->IBI value
        runningTotal += hb->rate[i];              // add up the 9 oldest hb->IBI values
      }

      hb->rate[9] = hb->IBI;                          // add the latest hb->IBI to the rate array
      runningTotal += hb->rate[9];                  // add the latest hb->IBI to runningTotal
      runningTotal /= 10;                      // average the last 10 hb->IBI values
      hb->BPM = 60000 / runningTotal;              // how many beats can fit into a minute? that's BPM!


      hb->QS = 1;                              // set Quantified Self flag
      // QS FLAG IS NOT CLEARED INSIDE THIS ISR
    }
  }

  if (hb->Signal < hb->thresh && hb->Pulse == true) {   // when the values are going down, the beat is over
    //	  blinkPin=1;			 // turn off pin 13 LED
    hb->Pulse = false;                           // reset the hb->Pulse flag so we can do it again
    hb->amp = hb->Peak - hb->Trough;                           // get amplitude of the hb->Pulse wave
    hb->thresh = hb->amp / 2 + hb->Trough;                    // set hb->thresh at 50% of the amplitude
    hb->Peak = hb->thresh;                              // reset these for next time
    hb->Trough = hb->thresh;
  }

  if (N > 2500) {                           // if 2.5 seconds go by without a beat
    hb->thresh = 512;                           // set hb->thresh default
    hb->Peak = 512;                              // set P default
    hb->Trough = 512;                                // set T default
    hb->lastBeatTime = hb->sampleCounter;           // bring the lastBeatTime up to date
    hb->firstBeat = 1;                       // set these to avoid noise
    hb->secondBeat = 0;                   // when we get the heartbeat back
  }
  if (hb->BPM > 200)hb->BPM = 200;          //����BPM�����ʾֵ
  if (hb->BPM < 30)hb->BPM = 30;              //����BPM�����ʾֵ



}


