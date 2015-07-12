#include "beagleblack_lcd.h"

#define LCD_EN 69 //P8_9
#define LCD_RS 66 //P8_7
#define LCD_D7 45 //P8_11
#define LCD_D6 47 //P8_15
#define LCD_D5 27 //P8_17
#define LCD_D4 65 //P8_18

void lcd_fill_pinout(lcd_pinout* lcd) {
    lcd -> en = LCD_EN;
    lcd -> rs = LCD_RS;
    lcd -> db_7 = LCD_D7;
    lcd -> db_6 = LCD_D6;
    lcd -> db_5 = LCD_D5;
    lcd -> db_4 = LCD_D4;
}

int main() {
    lcd_pinout lcd;
    int i;
    lcd_fill_pinout(&lcd);
    lcd_init(&lcd);
    
    // for(i = 0; i < 15; i++) {
    //     lcd_com(&lcd, LCD_SETDDRAMADDR | i);
    //     printf("%x\n", LCD_SETDDRAMADDR | i);
    //     lcd_print(&lcd, "x");
    // }
    
    lcd_print(&lcd, "Freq: ");
    // for(i = 0; i < 15; i++) {
    //     lcd_com(&lcd, LCD_SETDDRAMADDR + 0x40 | i);
    //     printf("%x\n", LCD_SETDDRAMADDR + 0x40 | i);
    //     lcd_print(&lcd, "");
    // }
    
    lcd_com(&lcd, LCD_SETDDRAMADDR | 0x7);
    lcd_com(&lcd, LCD_SETDDRAMADDR + 0x40);
    lcd_print(&lcd, "--->---|-------");
    
    lcd_deinit(&lcd);
}