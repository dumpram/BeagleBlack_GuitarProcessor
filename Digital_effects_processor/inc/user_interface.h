/** @file user_interface.h
 *
 * @brief header file for user interface of Digital Effects Processor application. 
 *	Contains declarations of functions. Implementations can be found in user_interface.c 
 *	source file. File contatins documentation of functions.
 * @author Ivan Pavic
 * @version 1.0
 */

#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_


#include <linux/inotify.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "beagleblack_lcd.h"
#include "beagleblack_gpio.h"
#include "digital_effects.h"

#define SWITCH_NUM 3

#define SWITCH_GPIO_1 67 //P8_8
#define SWITCH_GPIO_2 68 //P8_10
#define SWITCH_GPIO_3 44 //P8_12

#define LCD_EN 69 //P8_9
#define LCD_RS 66 //P8_7
#define LCD_D7 45 //P8_11
#define LCD_D6 47 //P8_15
#define LCD_D5 27 //P8_17
#define LCD_D4 65 //P8_18

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )


/**
 * Fills pinout for lcd. For documentation of lcd_pinout structures and functions
 * refer to beagleblack_lcd.h header file.
 * @param lcd: lcd_pinout to fill
 */
void lcd_fill_pinout(lcd_pinout *lcd);
/** 
 * Creates LCD structure. Additionally initializes semaphore for writing to LCD so
 * only one thread can write on LCD at the time.
 * @retval returns pointer to lcd_pinout structure
 */
lcd_pinout *create_lcd();
/**
 * Displays given message on given LCD structure.
 * @param lcd: pointer to lcd_pinout structure
 * @param message: string for display on LCD
 */
void lcd_disp(lcd_pinout *lcd, char *message);
/**
 * Function updates LCD of given process if necessary.
 * @param process: pointer to process 
 * @note For documentation of processor_t structure refer to digital_effects.h header file.
 */
void update_process_lcd(processor_t *process);
/**
 * Initializes switches.
 */
void switch_init();
/* DEPRECATED */
void *switch_interrupt_handler_1(void *arg);
void switch_interrupt_handler_2();
void switch_interrupt_handler_3();
/* END OF DEPRECATED */

/** Monitors switch activity. 
 * @param arg: needs to be explictly cast to processor_t structure
 */
void *switch_monitor(void *arg);

#endif
