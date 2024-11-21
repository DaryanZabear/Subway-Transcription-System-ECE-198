#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f1xx_hal.h"

void lcd_init(I2C_HandleTypeDef *hi2c);
void lcd_send_string(char *str);
void lcd_clear(void);
void lcd_goto_xy(uint8_t x, uint8_t y);

#endif
