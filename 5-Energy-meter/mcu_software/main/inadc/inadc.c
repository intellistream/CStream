#include "inadc.h"
static esp_adc_cal_characteristics_t *g_adcChars;

void initAdc0(void) {
  adc_power_on();
  adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_7);
  adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_6);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC_CHANNEL_7, ADC_ATTEN_DB_11);
  adc1_config_channel_atten(ADC_CHANNEL_6, ADC_ATTEN_DB_11);
  g_adcChars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_value_t
      val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, DEFAULT_VREF, g_adcChars);

}
uint32_t getAdc0(void) {

  uint32_t adc_reading = 0;
  uint32_t voltage = 0;
  for (int i = 0; i < NO_OF_SAMPLES; i++) {

    adc_reading += adc1_get_raw((adc1_channel_t) ADC_CHANNEL_7);
  }
  adc_reading /= NO_OF_SAMPLES;
  voltage = esp_adc_cal_raw_to_voltage(adc_reading, g_adcChars);

  return adc_reading;
}

uint32_t getAdc1(void) {

  uint32_t adc_reading = 0;
  uint32_t voltage = 0;
  for (int i = 0; i < NO_OF_SAMPLES; i++) {

    adc_reading += adc1_get_raw((adc1_channel_t) ADC_CHANNEL_6);
  }
  adc_reading /= NO_OF_SAMPLES;
  voltage = esp_adc_cal_raw_to_voltage(adc_reading, g_adcChars);

  return voltage;
}