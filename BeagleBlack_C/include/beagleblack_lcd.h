#ifndef _BEAGLEBLACK_LCD_H
#define _BEAGLEBLACK_LCD_H

#include "beagleblack_gpio.h"
#include <string.h>
#include <stdio.h>

// Commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT  0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00


#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// Move flags
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

//Function set flags
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


#define LCD_TOGGLE_ENABLE_DELAY 10000

typedef struct lcd_1602_4bus {
    int en;
    int rs;
    int db_7;
    int db_6;
    int db_5;
    int db_4;
} lcd_pinout;

void lcd_init(lcd_pinout *lcd);
void lcd_deinit(lcd_pinout *lcd);
void lcd_clear(lcd_pinout *lcd);
void lcd_print(lcd_pinout *lcd, char *message);
void lcd_data(lcd_pinout *lcd, char message);
void lcd_com(lcd_pinout *lcd, char message);
void lcd_send(lcd_pinout *lcd, char message);
void lcd_toggle_enable(lcd_pinout *lcd);
void lcd_delay();



#endif