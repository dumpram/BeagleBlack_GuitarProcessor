#include "beagleblack_lcd.h"

void fillPinout(lcd_pinout *lcd) {
    lcd -> en = 68; 
    lcd -> rs = 67;
    lcd -> db_7 = 44;
    lcd -> db_6 = 26;
    lcd -> db_5 = 46;
    lcd -> db_4 = 65;
}

int main() {
    lcd_pinout lcd;
    fillPinout(&lcd);
    lcd_init(&lcd);
    
    //lcd_print(&lcd, "");
    lcd_com(&lcd, 0x80);
    lcd_print(&lcd, "Hello, LCD!");
    //lcd_print(&lcd, "Hello, LCD!");
    return 0;
}