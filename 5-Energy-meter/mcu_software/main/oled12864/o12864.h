/*
 * o12864.h
 *
 *  Created on: 2019��4��27��
 *      Author: TONY
   for esp32 using idf
 */

#ifndef OLED12864_O12864_H_
#define OLED12864_O12864_H_
#define OLED_CMD  0 //д����
#define OLED_DATA 1 //д����
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "soc/gpio_struct.h"
#include <stdint.h>
#define OLED_CMD  0
#define OLED_DATA 1
#define  u8 uint8_t
#define  u32 uint32_t
#define     OLED_SSD1306_SCLK_PIN_NUM       (41) //sclk-25*/
#define     OLED_SCLK_Set()                gpio_set_level(OLED_SSD1306_SCLK_PIN_NUM,1)
#define     OLED_SCLK_Clr()           gpio_set_level(OLED_SSD1306_SCLK_PIN_NUM,0)
#define     OLED_SSD1306_SDIN_PIN_NUM       (40) //sdin 14
#define     OLED_SDIN_Set()            gpio_set_level(OLED_SSD1306_SDIN_PIN_NUM,1)
#define     OLED_SDIN_Clr()                gpio_set_level(OLED_SSD1306_SDIN_PIN_NUM,0)
#define     OLED_SSD1306_DC_PIN_NUM         (38) //dc-26

#define     OLED_DC_Set()             gpio_set_level(OLED_SSD1306_DC_PIN_NUM,1)
#define     OLED_DC_Clr()             gpio_set_level(OLED_SSD1306_DC_PIN_NUM,0)
#define     OLED_SSD1306_CE_PIN_NUM         (42) //cs -25
#define     OLED_CS_Set()              gpio_set_level(OLED_SSD1306_CE_PIN_NUM,1)
#define     OLED_CS_Clr()               gpio_set_level(OLED_SSD1306_CE_PIN_NUM,0)
#define     OLED_SSD1306_RST_PIN_NUM        (39) //rst 27
#define     OLED_RST_Set()                gpio_set_level(OLED_SSD1306_RST_PIN_NUM,1)
#define     OLED_RST_Clr()            gpio_set_level(OLED_SSD1306_RST_PIN_NUM,0)

#define SIZE 6
#define XLevelL     0x02
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     131
#define Y_WIDTH     64
//-----------------OLED�˿ڶ���----------------

void delay_ms(unsigned int ms);

//OLED�����ú���
void OLED_WR_Byte(u8 dat, u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x, u8 y, u8 t);
void OLED_Fill(u8 x1, u8 y1, u8 x2, u8 y2, u8 dot);
void OLED_ShowChar(u8 x, u8 y, u8 chr);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size2);
void OLED_ShowString(u8 x, u8 y, u8 *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x, u8 y, u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);
//ϵͳ��ʾ��Ϣ

#endif /* OLED12864_O12864_H_ */
