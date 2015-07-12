#include "beagleblack_gpio.h"

static char gpio_export_path[] = "/sys/class/gpio/export";
static char gpio_unexport_path[] = "/sys/class/gpio/unexport";

void gpio_export(int gpio_id) {
	FILE *export_stream = fopen(gpio_export_path, "w");
	char str_id[GPIO_ID_LENGTH];
	sprintf(str_id, "%d", gpio_id);
	fprintf(export_stream, "%s", str_id);
	fclose(export_stream);
}

void gpio_unexport(int gpio_id) {
	FILE *unexport_stream = fopen(gpio_unexport_path, "w");
	char str_id[GPIO_ID_LENGTH];
	sprintf(str_id, "%d", gpio_id);
	fprintf(unexport_stream, "%s", str_id);
	fclose(unexport_stream);
}

void gpio_set_direction(int gpio_id, char *direction) {
	char gpio_path_id[GPIO_PATH_LENGTH];
	FILE *gpio_stream;	
	sprintf(gpio_path_id, "/sys/class/gpio/gpio%d/direction", gpio_id);
	gpio_stream = fopen(gpio_path_id, "w");
	fprintf(gpio_stream, "%s", direction);
	fclose(gpio_stream);
}

void gpio_set_value(int gpio_id, char value) { 
	char gpio_path_id[GPIO_PATH_LENGTH];
	FILE *gpio_stream;	
	sprintf(gpio_path_id, "/sys/class/gpio/gpio%d/value", gpio_id);
	gpio_stream = fopen(gpio_path_id, "w");
	fprintf(gpio_stream, "%c", value);
	fclose(gpio_stream);
}

void gpio_init(int gpio_id, char* direction, char value) {
	gpio_export(gpio_id);
	gpio_set_direction(gpio_id, direction);
	if (!strcmp(direction, "out")) {
		gpio_set_value(gpio_id, value);	
	}
}
	
int gpio_exported(int gpio_id) {
	char gpio_path[GPIO_PATH_LENGTH];
	FILE *gpio_stream;
	sprintf(gpio_path, "/sys/class/gpio/gpio%d/value", gpio_id);
	gpio_stream = fopen(gpio_path, "r");
	if (!gpio_stream) {
		return 0;
	}
	fclose(gpio_stream);
	return 1;
}

int gpio_get_value(int gpio_id) {
	char gpio_path[GPIO_PATH_LENGTH];
	char value;
	FILE *gpio_stream;
	if(!gpio_exported(gpio_id)) {
		return -1;
	}
	sprintf(gpio_path, "/sys/class/gpio/gpio%d/value", gpio_id);
	gpio_stream = fopen(gpio_path, "r");
	fscanf(gpio_stream, "%c", &value);
	fclose(gpio_stream);
	return (value == '1')? 1 : 0; 
}






