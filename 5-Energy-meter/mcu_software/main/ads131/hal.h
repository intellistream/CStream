/**
 * \copyright Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_


//****************************************************************************
//
// Standard libraries
//
//****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "soc/gpio_struct.h"
#include "driver/gpio.h"

#define IS_POLLIN 1
//****************************************************************************
//
// Insert processor specific header file(s) here
//
//****************************************************************************

/*  --- INSERT YOUR CODE HERE --- */




//*****************************************************************************
//
// Pin definitions (MSP432E401Y)
//
//*****************************************************************************
#define ADS_CS (GPIO_NUM_5)
#define ADS_MOSI (GPIO_NUM_0)
#define ADS_MISO (GPIO_NUM_13)

#define ADS_CLK (GPIO_NUM_4)
#define ADS_EXT (GPIO_NUM_18)
#define ADS_CH (GPIO_NUM_19)


//*****************************************************************************
//
// Function Prototypes
//cd
//*****************************************************************************

void InitADC(void);
extern void delay_ms(unsigned int ms);
void delay_us(const uint32_t delay_time_us);
void setCS(const bool state);
void setSYNC_RESET(const bool state);
void toggleSYNC(void);
void toggleRESET(void);
void spiSendReceiveArrays(const uint8_t DataTx[], uint8_t DataRx[], const uint8_t byteLength);
uint8_t spiSendReceiveByte(const uint8_t dataTx);
bool waitForDRDYinterrupt(const uint32_t timeout_ms);

// Functions used for testing only
bool getCS(void);
void tonyAdc_setCS(uint8_t state);
bool getSYNC_RESET(void);
void setSYNC_RESET(const bool state);
void mySpiSend8(uint8_t tdata);
uint8_t mySpiGet8(void);
uint8_t mySpiSGn(uint8_t *tbuf, uint8_t *rbuf, uint32_t len);
void initIo2Adc(void);
void initSpi2Adc(void);
void initIsr2Adc(void);
void disableIsr2Adc(void);

#define CS_CHOOSE               (0)

/** Alias used for setting GPIOs pins to the logic "low" state */
#define CS_FREE               (1)
//*****************************************************************************
//
// Macros
//
//*****************************************************************************
/** Alias used for setting GPIOs pins to the logic "high" state */
#define HIGH                ((bool) true)

/** Alias used for setting GPIOs pins to the logic "low" state */
#define LOW                 ((bool) false)
typedef struct TDATA_RECV {
  uint32_t ch0, ch1, ch2, ch3;

} TDATA_RECV;

#endif /* INTERFACE_H_ */
