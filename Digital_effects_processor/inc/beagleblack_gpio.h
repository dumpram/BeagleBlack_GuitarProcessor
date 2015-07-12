/** @file beagleblack_gpio.h
 *
 * @brief header file for GPIO library for BeagleBone Black. Contains declarations 
 *	of functions. Implementations can be found in beagleblack_gpio.c source file. 
	File contatins documentation of functions.
 * @author Ivan Pavic
 * @version 1.0
 */
#ifndef _BEAGLEBLACK_GPIO_H_
#define _BEAGLEBLACK_GPIO_H_

#include <stdio.h>
#include <string.h>

#define GPIO_ID_LENGTH 10
#define GPIO_PATH_LENGTH 64

/**
 * Function exports gpio with certain ID and makes it visible in userspace. 
 * In userspace character driver device is visible in /sys/class/gpio<id>/, where 
 * id is GPIO id of GPIO in question.
 * 
 * @param gpio_id: id of gpio for export   
 */
void gpio_export(int pin_id);
/**
 * Function unexports gpio with certain ID and makes it disappear from userspace. 
 *
 * @param gpio_id: id of gpio for unexport
 */
void gpio_unexport(int pin_id);
/**
 * Function sets value of gpio with given id to given value. If gpio mode is direction
 * is input change will not be applied.
 * 
 * @param pin_id: id of gpio which value is changing
 * @param value: new value of gpio
 *
 */
void gpio_set_value(int pin_id, char value);
/**
 * Functions sets directions of gpio with given id.
 * @param pin_id: id of gpio which directions is changing
 * @param direction: direction can be set either to 'in' or 'out'
 *		     which configures gpio direction to input or output
 */
void gpio_set_direction(int pin_id, char* direction);
/**
 * Function intializes gpio with given id, sets direction and value if
 * direction is set to output.
 * @param gpio_id: id of gpio to initialize
 * @param direction: direction can be set either to 'in' or 'out'
 *		     which configures gpio direction to input or output
 * @param value: new value of gpio
 * 	  
 */
void gpio_init(int gpio_id, char* direction, char value);
/**
 * Function checks if gpio is exported.
 * @retval returns 1 if it is exported, 0 otherwise
 */
int gpio_exported(int gpio_id);
/**
 * Function gets value of gpio with given id.
 * @param gpio_id: id of gpio in question
 * @retval returns 1 if gpio is set high, 0 otherwise.
 */
int gpio_get_value(int gpio_id);

#endif
