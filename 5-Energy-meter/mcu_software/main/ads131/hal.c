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


#include "fnirsdata.h"

#define ADS_CS_SEL (1ULL<<ADS_CS)|(1ULL<<(ADS_CH))
#define ADS_CH_SEL (1ULL<<(ADS_CH))
#define ADS_SWOUT_SEL ((1ULL<<(ADS_CS))|(1ULL<<(ADS_MOSI))|(1ULL<<(ADS_CLK))|(1ULL<<(ADS_CH)))
#define ADS_SWIN_SEL ((1ULL<<(ADS_MISO))|(1ULL<<(ADS_EXT)))
#define ADS_EXT_SEL ((1ULL<<(ADS_EXT)))
extern FNIRSDATA g_fnirsData;
extern uint16_t g_isrTime, g_isrTimeP;
//****************************************************************************
//
// Internal variables
//
//****************************************************************************
//#define SWSPI 1
// Flag to inicate if a /DRDY interrupt has occurred
static volatile bool flag_nDRDY_INTERRUPT = false;
#define ESP_INTR_FLAG_DEFAULT 0
spi_device_handle_t spi;

static xQueueHandle gpio_evt_queue = NULL;
//
static void IRAM_ATTR
gpio_isr_handler(void *arg) {
  uint32_t gpio_num = (uint32_t) arg;
  // xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
  gpio_intr_disable(ADS_EXT);
  //
  fnirsdata_update(&g_fnirsData);
  g_isrTime++;
  gpio_intr_enable(ADS_EXT);
  //
  //

}
//
//

//****************************************************************************
//
// Internal function prototypes
//
//****************************************************************************
void InitGPIO(void);
void InitSPI(void);
void GPIO_DRDY_IRQHandler(void);
void startIsr(void);
void startIsr(void) {
  gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
  //hook isr handler for specific gpio pin
  // gpio_set_level(ADS_CS,1);
  gpio_isr_handler_add(ADS_EXT, gpio_isr_handler, (void *) ADS_EXT);
  //gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
  // xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
}
void initIsr2Adc(void) {
  gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
  //hook isr handler for specific gpio pin
  // gpio_set_level(ADS_CS,1);
  gpio_isr_handler_add(ADS_EXT, gpio_isr_handler, (void *) ADS_EXT);
  /*gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
   xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);*/
}

//****************************************************************************
//
// External Functions (prototypes declared in hal.h)
//
//****************************************************************************


//*****************************************************************************
//
//! Initializes MCU peripherals for interfacing with the ADC.
//!
//! \fn void InitADC(void)
//!
//! \return None.
//
//*****************************************************************************
void

InitADC(void) {
  // IMPORTANT: Make sure device is powered before setting GPIOs pins to HIGH state.

  // Initialize GPIOs pins used by ADS131M0x
  InitGPIO();
  //gpio_set_level(ADS_CH,1);

  // Initialize SPI peripheral used by ADS131M0x
  InitSPI();

  // Run ADC startup function
  adcStartup();
  initIsr2Adc();
  //startIsr();
}




//****************************************************************************
//
// Timing functions
//
//****************************************************************************



//*****************************************************************************
//
//! Provides a timing delay with 'ms' resolution.
//!
//! \fn void delay_ms(const uint32_t delay_time_ms)
//!
//! \param delay_time_ms is the number of milliseconds to delay.
//!
//! \return None.
//
//*****************************************************************************




//*****************************************************************************
//
//! Provides a timing delay with 'us' resolution.
//!
//! \fn void delay_us(const uint32_t delay_time_us)
//!
//! \param delay_time_us is the number of microseconds to delay.
//!
//! \return None.
//
//*****************************************************************************
volatile void delay_us(const uint32_t delay_time_us) {
  /* --- INSERT YOUR CODE HERE --- */
//delay_ms(delay_time_us);
  for (volatile int k = 0; k < delay_time_us; k++) {
    usleep(1);

  }

}




//****************************************************************************
//
// GPIO initialization
//
//****************************************************************************



//*****************************************************************************
//
//! Configures the MCU's GPIO pins that interface with the ADC.
//!
//! \fn void InitGPIO(void)
//!
//! \return None.
//
//*****************************************************************************
void InitGPIO(void) {
  /* --- INSERT YOUR CODE HERE --- */
  // NOTE: Not all hardware implementations may control each of these pins...


/*OUT PUT PIN-CS*/
#ifndef SWSPI
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
  //set as output mode
  io_conf.mode = GPIO_MODE_OUTPUT;

  io_conf.pin_bit_mask = ADS_CS_SEL;
  gpio_config(&io_conf);
/*INPUT PIN EXT*/

#endif
#ifdef SWSPI
  gpio_config_t io_conf;
io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
  //set as output mode
  io_conf.mode = GPIO_MODE_OUTPUT;

  io_conf.pin_bit_mask = ADS_SWOUT_SEL;
   gpio_config(&io_conf);
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
  //set as output mode
  io_conf.mode = GPIO_MODE_INPUT;

  io_conf.pin_bit_mask = ADS_SWIN_SEL;
  io_conf.intr_type = GPIO_PIN_INTR_DISABLE;


#endif
  io_conf.intr_type = GPIO_INTR_NEGEDGE;
  //bit mask of the pins, use GPIO4/5 here
  io_conf.pin_bit_mask = ADS_EXT_SEL;
  io_conf.pull_down_en = 0;
  //set as input mode
  io_conf.mode = GPIO_MODE_INPUT;
  //enable pull-up mode
  io_conf.pull_up_en = 1;
  gpio_config(&io_conf);
  gpio_set_level(ADS_CS, 1);
  gpio_set_level(ADS_CH, 1);
  /**/

}




//*****************************************************************************
//
// Interrupt handler for nDRDY GPIO
//
//*****************************************************************************



//*****************************************************************************
//
//! Interrupt handler for /DRDY falling edge interrupt.
//!
//! \fn void GPIO_DRDY_IRQHandler(void)
//!
//! \return None.
//
//*****************************************************************************
void GPIO_DRDY_IRQHandler(void) {
  /* --- INSERT YOUR CODE HERE --- */
  //NOTE: You many need to rename or register this interrupt function for your processor

  // Possible ways to handle this interrupt:
  // If you decide to read data here, you may want to disable other interrupts to avoid partial data reads.

  // In this example we set a flag and exit the interrupt routine. In the main program loop, your application can examine
  // all state flags and decide which state (operation) to perform next.

  /* Get the interrupt status from the GPIO and clear the status */

}




//****************************************************************************
//
// GPIO helper functions
//
//****************************************************************************



//*****************************************************************************
//
//! Reads that current state of the /CS GPIO pin.
//!
//! \fn bool getCS(void)
//!
//! \return boolean ('true' if /CS is high, 'false' if /CS is low).
//
//*****************************************************************************
bool getCS(void) {
  /* --- INSERT YOUR CODE HERE --- */
  return (bool) gpio_get_level(ADS_CS);
}

//*****************************************************************************
//
//! Reads that current state of the nSYNC/nRESET GPIO pin.
//!
//! \fn bool getSYNC_RESET(void)
//!
//! \return boolean ('true' if nSYNC/nRESET is high, 'false' if nSYNC/nRESET is low).
//
//*****************************************************************************
bool getSYNC_RESET(void) {
  /* --- INSERT YOUR CODE HERE --- */
  return (bool) 0;
}

//*****************************************************************************
//
//! Controls the state of the /CS GPIO pin.
//!
//! \fn void setCS(const bool state)
//!
//! \param state boolean indicating which state to set the /CS pin (0=low, 1=high)
//!
//! NOTE: The 'HIGH' and 'LOW' macros defined in hal.h can be passed to this
//! function for the 'state' parameter value.
//!
//! \return None.
//
//*****************************************************************************
void setCS(const bool state) {
  /* --- INSERT YOUR CODE HERE --- */

  // td(CSSC) delay
  if (state) {
    delay_us(1);
  }
  gpio_set_level(ADS_CS, state);
  if (!state) {
    delay_us(1);
  }
}

//*****************************************************************************
//
//! Controls the state of the nSYNC/nRESET GPIO pin.
//!
//! \fn void setSYNC_RESET(const bool state)
//!
//! \param state boolean indicating which state to set the nSYNC/nRESET pin (0=low, 1=high)
//!
//! NOTE: The 'HIGH' and 'LOW' macros defined in hal.h can be passed to this
//! function for the 'state' parameter value.
//!
//! \return None.
//
//*****************************************************************************
void setSYNC_RESET(const bool state) {

}

//*****************************************************************************
//
//! Toggles the "nSYNC/nRESET" pin to trigger a synchronization
//! (LOW, delay 2 us, then HIGH).
//!
//! \fn void toggleSYNC(void)
//!
//! \return None.
//
//*****************************************************************************
void toggleSYNC(void) {
}

//*****************************************************************************
//
//! Toggles the "nSYNC/nRESET" pin to trigger a reset
//! (LOW, delay 2 ms, then HIGH).
//!
//! \fn void toggleRESET(void)
//!
//! \return None.
//
//*****************************************************************************
void toggleRESET(void) {

}

//*****************************************************************************
//
//! Waits for the nDRDY interrupt or until the specified timeout occurs.
//!
//! \fn bool waitForDRDYinterrupt(const uint32_t timeout_ms)
//!
//! \param timeout_ms number of milliseconds to wait before timeout event.
//!
//! \return Returns 'true' if nDRDY interrupt occurred before the timeout.
//
//*****************************************************************************
bool waitForDRDYinterrupt(const uint32_t timeout_ms) {
  /* --- INSERT YOUR CODE HERE ---
   * Poll the nDRDY GPIO pin until it goes low. To avoid potential infinite
   * loops, you may also want to implement a timer interrupt to occur after
   * the specified timeout period, in case the nDRDY pin is not active.
   * Return a boolean to indicate if nDRDY went low or if a timeout occurred.
   */


  return (bool) 0;
}




//****************************************************************************
//
// SPI Communication
//
//****************************************************************************



//*****************************************************************************
//
//! Configures the MCU's SPI peripheral, for interfacing with the ADC.
//!
//! \fn void InitSPI(void)
//!
//! \return None.
//
//*****************************************************************************
void InitSPI(void) {
  /* --- INSERT YOUR CODE HERE ---
   * NOTE: The ADS131M0x operates in SPI mode 1 (CPOL = 0, CPHA = 1).
   */

  //
  // Enable the clock to SSI-3 module and configure the SSI Master
  //
#ifndef SWSPI
  esp_err_t ret;

  spi_bus_config_t buscfg = {
      .miso_io_num=ADS_MISO,
      .mosi_io_num=ADS_MOSI,
      .sclk_io_num=ADS_CLK,
      .quadwp_io_num=-1,
      .quadhd_io_num=-1,
      .max_transfer_sz=NUM_REGISTERS * 4
  };
  spi_device_interface_config_t devcfg = {
      .command_bits=0,
      .address_bits=0,
      .clock_speed_hz=1000000,
      .mode=1,                                //SPI mode 1
      .spics_io_num=-1,               //DISABLE THE auto cs,we use it manully
      .queue_size=2,                          //We want to be able to queue 7 transactions at a time
      //   .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
  };
  ret = spi_bus_initialize(VSPI_HOST, &buscfg, 0);
  ESP_ERROR_CHECK(ret);
  //Attach the LCD to the SPI bus
  ret = spi_bus_add_device(VSPI_HOST, &devcfg, &spi);
  ESP_ERROR_CHECK(ret);
#endif

}

//*****************************************************************************
//
//! Sends SPI byte array on MOSI pin and captures MISO data to a byte array.
//!
//! \fn void spiSendReceiveArrays(const uint8_t dataTx[], uint8_t dataRx[], const uint8_t byteLength)
//!
//! \param const uint8_t dataTx[] byte array of SPI data to send on MOSI.
//!
//! \param uint8_t dataRx[] byte array of SPI data captured on MISO.
//!
//! \param uint8_t byteLength number of bytes to send & receive.
//!
//! NOTE: Make sure 'dataTx[]' and 'dataRx[]' contain at least as many bytes of data,
//! as indicated by 'byteLength'.
//!
//! \return None.
//
//*****************************************************************************
void spiSendReceiveArrays(const uint8_t dataTx[], uint8_t dataRx[], const uint8_t byteLength) {
  /*  --- INSERT YOUR CODE HERE ---
   *
   *  This function should send and receive multiple bytes over the SPI.
   *
   *  A typical SPI send/receive sequence may look like the following:
   *  1) Make sure SPI receive buffer is empty
   *  2) Set the /CS pin low (if controlled by GPIO)
   *  3) Send command bytes to SPI transmit buffer
   *  4) Wait for SPI receive interrupt
   *  5) Retrieve data from SPI receive buffer
   *  6) Set the /CS pin high (if controlled by GPIO)
   */

  // Require that dataTx and dataRx are not NULL pointers
  assert(dataTx && dataRx);



  //spi_device_transmit(spi, &t);
  //dataRx=t.rx_data[0];
  // Set the nCS pin LOW
  setCS(LOW);
  /* spi_transaction_t t;
       memset(&t, 0, sizeof(t));
       t.length=8*byteLength;
       //t.flags = SPI_TRANS_USE_RXDATA;
       t.rx_buffer=dataRx;
       t.tx_buffer=dataTx;

      esp_err_t ret;

   ret=spi_device_polling_transmit(spi, &t);  //Transmit!
   assert(ret==ESP_OK);            //Should have had no issues.*/
  // Send all dataTx[] bytes on MOSI, and capture all MISO bytes in dataRx[]
  int i;
  for (i = 0; i < byteLength; i++) {
    dataRx[i] = spiSendReceiveByte(dataTx[i]);
  }




  // Set the nCS pin HIGH
  setCS(HIGH);
}

//*****************************************************************************
//
//! Sends SPI byte on MOSI pin and captures MISO return byte value.
//!
//! \fn uint8_t spiSendReceiveByte(const uint8_t dataTx)
//!
//! \param const uint8_t dataTx data byte to send on MOSI pin.
//!
//! NOTE: This function is called by spiSendReceiveArrays(). If it is called
//! directly, then the /CS pin must also be directly controlled.
//!
//! \return Captured MISO response byte.
//
//*****************************************************************************
uint8_t mySpiGet8(void) {
#ifndef SWSPI
  spi_transaction_t t;
  uint8_t dataRx[4];
  uint8_t tempd;
  memset(&t, 0, sizeof(t));
  t.length = 8 * 1;
  t.flags = SPI_TRANS_USE_RXDATA;
  //t.rx_buffer=dataRx[0];
  t.tx_buffer = NULL;
#if IS_POLLIN
  esp_err_t ret;

  ret = spi_device_polling_transmit(spi, &t);  //Transmit!
  assert(ret == ESP_OK);            //Should have had no issues.
#else
  spi_device_transmit(spi, &t);
#endif
  //assert( ret == ESP_OK );
  //spi_device_transmit(spi, &t);

  return t.rx_data[0];
#endif
#ifdef SWSPI
  int i;
  uint8_t ru=0;
   /*gpio_set_level(ADS_CH,0);
   delay_us(1);*/

   for(i=0;i<8;i++)
      {

         // delay_ms(1);
          gpio_set_level(ADS_CLK,1);
          delay_us(1);
          if(gpio_get_level(ADS_MISO))
              {
               ru|=1;

              }
          else
              {
                  ru|=0;
              }
          ru=ru<<1;
          // delay_us(1);
               gpio_set_level(ADS_CLK,0);
          delay_us(1);
      }
   return ru;
    //delay_us(1);




#endif

}
void mySpiSend8(uint8_t tdata) {
#ifndef SWSPI
  esp_err_t ret;
  //uint8_t data = SPI_SWAP_DATA_TX(tdata, 8);

//tb[3]=tdata;
  spi_transaction_t t;
  // t.flags = SPI_TRANS_USE_TXDATA;
  memset(&t, 0, sizeof(spi_transaction_t));       //Zero out the transaction
  t.length = 8;                   //Len is in bytes, transaction length is in bits.
  t.tx_buffer = &tdata;               //Data
  t.rx_buffer = NULL;
#if IS_POLLIN
  ret = spi_device_polling_transmit(spi, &t);  //Transmit!
  assert(ret == ESP_OK);            //Should have had no issues.
#else
  spi_device_transmit(spi, &t);
#endif
  // spi_device_transmit(spi, &t);
#endif
#ifdef SWSPI
  int i;
  uint8_t temp;
  temp=tdata;
  for(i=0;i<8;i++)
      {

         // delay_ms(1);
          gpio_set_level(ADS_CLK,1);
          delay_us(1);
          if((temp&0x80)!=0)
              {
               gpio_set_level(ADS_MOSI,1);

              }
          else
              {
                   gpio_set_level(ADS_MOSI,0);
              }
          temp=temp<<1;
          // delay_us(1);
               gpio_set_level(ADS_CLK,0);
          delay_us(1);
      }





#endif

}
uint8_t mySpiXfer8(uint8_t data) {
  esp_err_t ret;
  uint8_t ru;
  spi_transaction_t t;
  // t.flags = SPI_TRANS_USE_TXDATA;
  memset(&t, 0, sizeof(spi_transaction_t));       //Zero out the transaction
  t.length = 8;                   //Len is in bytes, transaction length is in bits.
  t.rxlength = 8;
  t.tx_buffer = &data;               //Data
  t.rx_buffer = &ru;

  ret = spi_device_polling_transmit(spi, &t);  //Transmit!
  assert(ret == ESP_OK);            //Should have had no issues.
  return ru;
}
uint8_t spiSendReceiveByte(const uint8_t dataTx) {

  return mySpiXfer8(dataTx);

}