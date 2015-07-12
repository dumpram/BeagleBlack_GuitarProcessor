/** @file beagleblack_lcd.h
 *
 * @brief source file for LCD1602A library for BeagleBone Black. Contains implementations 
 *	of functions. Documentation can be found in beagleblack_lcd.h header file. 
 * @author Ivan Pavic
 * @version 1.0
 */
#include "beagleblack_lcd.h"

void lcd_init(lcd_pinout *lcd) {
    gpio_init(lcd -> en, "out", '0');
    gpio_init(lcd -> rs, "out", '0');
    gpio_init(lcd -> db_7, "out", '0');
    gpio_init(lcd -> db_6, "out", '0');
    gpio_init(lcd -> db_5, "out", '0');
    gpio_init(lcd -> db_4, "out", '0');

    lcd_com(lcd, 0x33); 
    lcd_com(lcd, 0x32);

    lcd_com(lcd, LCD_DISPLAYCONTROL |  LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
    lcd_com(lcd, LCD_FUNCTIONSET | LCD_4BITMODE | LCD_1LINE | LCD_2LINE | LCD_5x8DOTS);
    lcd_com(lcd, LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
    lcd_clear(lcd);
}

void lcd_clear(lcd_pinout *lcd) {
    lcd_com(lcd, LCD_CLEARDISPLAY);
    usleep(4000);
}

void lcd_print(lcd_pinout *lcd, char *message) {
    int i, len;
    len = strlen(message);
    for (i = 0; i < len; i++) {
        lcd_delay();
        lcd_data(lcd, message[i]);
    }
}

void lcd_data(lcd_pinout *lcd, char message) {
    gpio_set_value(lcd -> rs, '1');
    lcd_send(lcd, message);
}

void lcd_new_line(lcd_pinout *lcd) {
    lcd_com(lcd, LCD_SETDDRAMADDR | LCD_2nd_ROW_OFFSET);
}

void lcd_set_cursor(lcd_pinout *lcd, int row, int col) {
    if (!row) {
        lcd_com(lcd, LCD_SETDDRAMADDR | col);
    } else {
        lcd_com(lcd, LCD_SETDDRAMADDR | (col + LCD_2nd_ROW_OFFSET));
    }
} 

void lcd_com(lcd_pinout *lcd, char message) {
    gpio_set_value(lcd -> rs, '0');
    lcd_send(lcd, message);
}

void lcd_send(lcd_pinout *lcd, char message) {
    char upper_bits = (message & 0xF0) >> 4;
    char lower_bits = (message & 0x0F);
    char value;
    
    value = ((upper_bits >> 3) & 0x1)? '1' : '0';
    gpio_set_value(lcd -> db_7, value);
    
    value = ((upper_bits >> 2) & 0x1)? '1' : '0';
    gpio_set_value(lcd -> db_6, value);
    
    value = ((upper_bits >> 1) & 0x1)? '1' : '0';
    gpio_set_value(lcd -> db_5, value);
    
    value = ((upper_bits >> 0) & 0x1)? '1' : '0';
    gpio_set_value(lcd -> db_4, value);
    
    lcd_toggle_enable(lcd);
    
    value = ((lower_bits >> 3) & 0x1)? '1' : '0';
    gpio_set_value(lcd -> db_7, value);
    
    value = ((lower_bits >> 2) & 0x1)? '1' : '0';
    gpio_set_value(lcd -> db_6, value);
    
    value = ((lower_bits >> 1) & 0x1)? '1' : '0';
    gpio_set_value(lcd -> db_5, value);
    
    value = ((lower_bits >> 0) & 0x1)? '1' : '0';
    gpio_set_value(lcd -> db_4, value);
    
    lcd_toggle_enable(lcd);
     
}

void lcd_delay() {
    int i = LCD_TOGGLE_ENABLE_DELAY;
    while(i--);

}

void lcd_toggle_enable(lcd_pinout *lcd) {
    gpio_set_value(lcd -> en, '0');
    lcd_delay();
    gpio_set_value(lcd -> en, '1');
    lcd_delay();
    gpio_set_value(lcd -> en, '0');
}

void lcd_deinit(lcd_pinout *lcd) {
    gpio_unexport(lcd -> en);
    gpio_unexport(lcd -> rs);
    gpio_unexport(lcd -> db_7);
    gpio_unexport(lcd -> db_6);
    gpio_unexport(lcd -> db_5);
    gpio_unexport(lcd -> db_4);
}
