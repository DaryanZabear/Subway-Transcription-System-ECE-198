#include "lcd.h"
#include "stm32f4xx_hal.h"

// Define your GPIO pins (adjust to your setup)
#define LCD_RS GPIO_PIN_0
#define LCD_RW GPIO_PIN_1
#define LCD_E GPIO_PIN_2
#define LCD_DATA_PORT GPIOB  // Use the appropriate GPIO port for data lines

void LCD_Init(void) {
    // Initialize the GPIO pins for control and data lines
    HAL_GPIO_WritePin(LCD_DATA_PORT, LCD_RS, GPIO_PIN_RESET); // Example for controlling RS pin
    // Further initialization here...
}

void LCD_Clear(void) {
    // Send the clear command to the LCD
    LCD_SendCommand(0x01);
    HAL_Delay(2);  // Wait for clear to complete
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = 0x00;
    if (row == 0) address = col;
    else if (row == 1) address = 0x40 + col;

    LCD_SendCommand(0x80 | address);
}

void LCD_Print(char *str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}

// Helper functions to send commands and data
void LCD_SendCommand(uint8_t command) {
    HAL_GPIO_WritePin(LCD_DATA_PORT, LCD_RS, GPIO_PIN_RESET);  // Set RS to 0 for command
    // Send the command to the data pins
}

void LCD_SendData(uint8_t data) {
    HAL_GPIO_WritePin(LCD_DATA_PORT, LCD_RS, GPIO_PIN_SET);  // Set RS to 1 for data
    // Send the data to the data pins
}
