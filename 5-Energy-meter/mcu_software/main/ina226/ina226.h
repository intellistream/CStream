#ifndef _INA226_H_
#define _INA226_H_
#include <stdio.h>
#include "argtable3/argtable3.h"
#include "driver/i2c.h"
#include "esp_console.h"
#include "esp_log.h"
#define I2C_MASTER_FREQ_HZ     800000
#define    SlaveAddress    0x80    //IIC写入时的地址字节数据，+1为读取
#define I2C_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define WRITE_BIT  I2C_MASTER_WRITE /*!< I2C master write */
#define READ_BIT   I2C_MASTER_READ  /*!< I2C master read */
#define ACK_CHECK_EN   0x1     /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS  0x0     /*!< I2C master will not check ack from slave */
#define ACK_VAL    0x0         /*!< I2C ack value */
#define NACK_VAL   0x1         /*!< I2C nack value */
void ina226_init0(void);
void ina226_init1(void);
uint16_t ina226_readReg(i2c_port_t port, uint8_t addr);
void ina226_writeReg(i2c_port_t port, uint8_t addr, uint16_t val);
float ina226_getV(i2c_port_t port);
float ina226_getI(i2c_port_t port);
float ina226_getW(i2c_port_t port);
#endif