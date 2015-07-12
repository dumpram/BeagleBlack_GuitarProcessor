#include "beagleblack_gpio.h"

#define TESTS_COUNT 3

int gpio_export_unexport_test() {
    gpio_init(60, "out", '0');
    if(!gpio_exported(60)) {
        printf("Test nije zadovoljen: GPIO nije exportan!\n");
        return 1;
    }
    gpio_unexport(60);
    if(gpio_exported(60)) {
        printf("Test nije zadovoljen: GPIO je exportan!\n");
        return 1;
    }
    return 0; 
}

int gpio_get_test() {
    gpio_init(60, "out", '0');
    if(gpio_get_value(60)) {
        printf("Test nije zadovljen: GPIO treba biti u nuli!");
        gpio_unexport(60);
        return 1;
    } 
    gpio_unexport(60);
    return 0;
}

int gpio_set_test() {
    gpio_init(60, "out", '0');
    gpio_set_value(60, '1');
    if(gpio_get_value(60) != 1) {
        printf("Test nije zadovljen: GPIO treba biti u jedinici!\n");
        gpio_unexport(60);
        return 1;   
    }
    gpio_unexport(60);
    return 0;
}

int (*functions[TESTS_COUNT])(void);

void init_functions() {
    functions[0] = gpio_export_unexport_test;
    functions[1] = gpio_get_test;
    functions[2] = gpio_set_test;
}

int main() {
    int i;
    init_functions();
    for(i = 0; i < TESTS_COUNT; i++) {
        if(!((*functions[i])())) {
            printf("Test %d successful!\n", i + 1);
        } else {
            return 1;
        }
    }
    return 0;   
}