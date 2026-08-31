#ifndef __OLED_SSD1306_H
#define __OLED_SSD1306_H
#include <stdint.h>

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *str);

#endif

