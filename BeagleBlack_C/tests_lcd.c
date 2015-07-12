#include "beagleblack_lcd.h"

void fillPinout(lcd_pinout *lcd) {
    lcd -> en = 68; //P8_10
    lcd -> rs = 67; //P8_8
    lcd -> db_7 = 44; //P8_12
    lcd -> db_6 = 26; //P8_14
    lcd -> db_5 = 46; //P8_16
    lcd -> db_4 = 65; //P8_18
    
}


void lcd_init_test() {
    lcd_pinout lcd;
    fillPinout(&lcd);
    lcd_init(&lcd);
}

void lcd_write_test() {
    lcd_pinout lcd;
    fillPinout(&lcd);
    lcd_init(&lcd);
    lcd_print(&lcd, "Hello World!");
}

void lcd_clear_test() {
    lcd_pinout lcd;
    fillPinout(&lcd);
    lcd_clear(&lcd);
}

void lcd_deinit_test() {
    lcd_pinout lcd;
    fillPinout(&lcd);
    lcd_deinit(&lcd);
}

int main() {
    
    lcd_init_test();
    lcd_write_test();
    //lcd_clear_test();
    lcd_deinit_test();
    
    //lcd_print(&lcd, "");
    //lcd_com(&lcd, 0x80);
    //lcd_print(&lcd, "Hello, LCD!");
    //lcd_print(&lcd, "Hello, LCD!");
    return 0;
}