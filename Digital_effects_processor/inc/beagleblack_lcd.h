/** @file beagleblack_lcd.h
 *
 * @brief header file for LCD1602A library for BeagleBone Black. Contains declarations 
 *	of functions. Implementations can be found in beagleblack_lcd.c source file. 
	File contatins documentation of functions.
 * @author Ivan Pavic
 * @version 1.0
 */
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
#define LCD_2nd_ROW_OFFSET 0x40

/**
 * Structure represents LCD1602 with 4 data signals and 
 * enable and reset pin.
 */
typedef struct lcd_1602_4bus {
    int en;
    int rs;
    int db_7;
    int db_6;
    int db_5;
    int db_4;
} lcd_pinout;
/**
 * Initializes given GPIO pins in given lcd_pinout.
 * @param lcd: lcd_pinout for initialization
 * @note lcd_pinout must be filled before initialization.
 */
void lcd_init(lcd_pinout *lcd);
/**
 * Deinitializes given GPIO pins in given lcd_pinout.
 * @param lcd: lcd_pinout for deinitialization
 * @note lcd_pinout must be filled before deinitialization.
 */
void lcd_deinit(lcd_pinout *lcd);
/**
 * Clears given lcd display.
 * @param lcd: lcd_pinout for LCD which needs to be cleared
 */
void lcd_clear(lcd_pinout *lcd);
/**
 * Prints given message to lcd display.
 * @param lcd: lcd_pinout for printing
 * @param message: string for printing
 */
void lcd_print(lcd_pinout *lcd, char *message);
/**
 * Sends data to LCD.
 * @param lcd: lcd_pinout for sending data
 * @param message: data to be sent
 */
void lcd_data(lcd_pinout *lcd, char message);
/**
 * Sends command to LCD.
 * @param lcd: lcd_pinout for sending command
 * @param message: command to be sent
 */
void lcd_com(lcd_pinout *lcd, char message);
/**
 * Sends command or data to LCD depending on control signals.
 * @param lcd: lcd_pinout for sending stuff
 * @param message: data or command to be sent
 */
void lcd_send(lcd_pinout *lcd, char message);
/**
 * LCD cursor goes to new line. Changes position in DDRAM memory.
 */
void lcd_new_line(lcd_pinout *lcd);
/** 
 * Sets cursor of given LCD to row and column given.
 * @param lcd: lcd_pinout for selecting row and column
 * @param row: row position to set
 * @param col: column position to set
 */
void lcd_set_cursor(lcd_pinout *lcd, int row, int col);
/**
 * Function toggles enable signal of given LCD.
 * @param lcd: lcd_pinout
 */
void lcd_toggle_enable(lcd_pinout *lcd);
/**
 * Auxilliary function for creating delay between miscellaneous LCD functions(e.g. 
 * LCD clear operations takes long time)
 */
void lcd_delay();



#endif
