#ifndef _MYUART_H_
#define  _MYUART_H_
//use uart2,tx=33,rx=32
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include <stdint.h>
#define ECHO_TEST_TXD  (GPIO_NUM_33)
#define ECHO_TEST_RXD  (GPIO_NUM_32)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)
#define BUF_SIZE (1024)
void initMyUart(void);
void myUartSend(uint8_t *data, uint32_t lenth);
#endif