#include "ina226.h"

static gpio_num_t sda0 = 4;
static gpio_num_t scl0 = 3;
static gpio_num_t sda1 = 2;
static gpio_num_t scl1 = 1;
static i2c_port_t port0 = I2C_NUM_0;
static i2c_port_t port1 = I2C_NUM_1;
static uint32_t i2c_frequency = 400000;
void ina226_init0(void) {
  i2c_config_t conf = {
      .mode = I2C_MODE_MASTER,
      .sda_io_num = sda0,
      // .sda_pullup_en = GPIO_PULLUP_ENABLE,
      .scl_io_num = scl0,
      //.scl_pullup_en = GPIO_PULLUP_ENABLE,
      .master.clk_speed = i2c_frequency,
      // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
  };
  i2c_param_config(port0, &conf);
  i2c_driver_install(port0, conf.mode,
                     I2C_MASTER_RX_BUF_DISABLE,
                     I2C_MASTER_TX_BUF_DISABLE, 0);
}
void ina226_init1(void) {
  i2c_config_t conf = {
      .mode = I2C_MODE_MASTER,
      .sda_io_num = sda1,
      .sda_pullup_en = GPIO_PULLUP_ENABLE,
      .scl_io_num = scl1,
      .scl_pullup_en = GPIO_PULLUP_ENABLE,
      .master.clk_speed = i2c_frequency,
      // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
  };
  i2c_param_config(port1, &conf);
  i2c_driver_install(port1, conf.mode,
                     I2C_MASTER_RX_BUF_DISABLE,
                     I2C_MASTER_TX_BUF_DISABLE, 0);
}

uint16_t ina226_readReg(i2c_port_t port, uint8_t addr) {
  int ret;
  uint8_t dataMsb, dataLsb;
  uint16_t tdata = 0;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, SlaveAddress, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, addr, ACK_CHECK_EN);
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, SlaveAddress + 1, ACK_CHECK_EN);
  i2c_master_read_byte(cmd, &dataMsb, ACK_VAL);
  i2c_master_read_byte(cmd, &dataLsb, NACK_VAL);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(port, cmd, 0);
  i2c_cmd_link_delete(cmd);
  tdata = dataMsb;
  tdata = (tdata << 8) | dataLsb;
  return tdata;
}
void ina226_writeReg(i2c_port_t port, uint8_t addr, uint16_t val) {
  int ret;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, SlaveAddress, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, addr, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, (val >> 8) & 0xff, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, (val) & 0xff, ACK_CHECK_EN);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(port, cmd, 0);
  i2c_cmd_link_delete(cmd);

}
float ina226_getV(i2c_port_t port) {
  uint16_t rt = ina226_readReg(port, 0x02);
  float ru = rt;
  ru = ru * 1.25;
  return ru;
}
float ina226_getI(i2c_port_t port) {
  uint16_t rt = ina226_readReg(port, 0x04);
  float ru = rt;
  ru = ru * 0.2;
  return ru;

}
float ina226_getW(i2c_port_t port) {
  uint16_t rt = ina226_readReg(port, 0x03);
  float ru = rt;
  ru = ru * 5.0;
  return ru;
}