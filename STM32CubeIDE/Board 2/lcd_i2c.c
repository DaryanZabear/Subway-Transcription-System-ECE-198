#include "lcd_i2c.h"
#include "string.h"

// Define the LCD's I2C address (commonly 0x3F or 0x27)
#define LCD_ADDR 0x3F << 1  // Adjust if necessary

static I2C_HandleTypeDef *lcd_i2c;

void lcd_init(I2C_HandleTypeDef *hi2c) {
    lcd_i2c = hi2c;
    HAL_Delay(50);

    // LCD initialization commands
    uint8_t init_cmd[] = {0x00, 0x38, 0x0C, 0x06, 0x01}; // Mode: 8-bit, 2-line, display on, cursor off, increment mode
    for (int i = 0; i < sizeof(init_cmd); i++) {
        HAL_I2C_Master_Transmit(lcd_i2c, LCD_ADDR, &init_cmd[i], 1, HAL_MAX_DELAY);
        HAL_Delay(5);
    }
}

void lcd_send_string(char *str) {
    while (*str) {
        uint8_t data[] = {0x40, *str++};  // 0x40 indicates data (not command)
        HAL_I2C_Master_Transmit(lcd_i2c, LCD_ADDR, data, 2, HAL_MAX_DELAY);
    }
}

void lcd_clear(void) {
    uint8_t cmd = 0x01;  // Clear display command
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_ADDR, &cmd, 1, HAL_MAX_DELAY);
    HAL_Delay(2);  // Wait for the command to execute
}

void lcd_goto_xy(uint8_t x, uint8_t y) {
    uint8_t pos = 0x80 + (y * 0x40) + x;  // Compute the position
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_ADDR, &pos, 1, HAL_MAX_DELAY);
}
