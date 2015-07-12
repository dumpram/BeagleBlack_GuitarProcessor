#ifndef _BEAGLEBLACK_GPIO_H_
#define _BEAGLEBLACK_GPIO_H_

#include <stdio.h>
#include <string.h>

#define GPIO_ID_LENGTH 10
#define GPIO_PATH_LENGTH 64



void gpio_export(int pin_id);
void gpio_unexport(int pin_id);
void gpio_set_value(int pin_id, char value);
void gpio_set_direction(int pin_id, char* direction);
void gpio_init(int gpio_id, char* direction, char value);
int gpio_exported(int gpio_id);
int gpio_get_value(int gpio_id);

//void toggle_gpio_value(int pin_id);



#endif
