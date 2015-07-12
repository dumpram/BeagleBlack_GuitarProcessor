#include "beagleblack_gpio.h"

int main() {
   gpio_init(60, "in", '0');
   gpio_unexport(60);
   return 0;
}
