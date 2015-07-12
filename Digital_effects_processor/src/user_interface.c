#include "user_interface.h"

sem_t lcdSem;

void lcd_fill_pinout(lcd_pinout *lcd) {
    lcd -> en = LCD_EN;
    lcd -> rs = LCD_RS;
    lcd -> db_7 = LCD_D7;
    lcd -> db_6 = LCD_D6;
    lcd -> db_5 = LCD_D5;
    lcd -> db_4 = LCD_D4;
}

void switch_init() {
    gpio_init(SWITCH_GPIO_1, "in", 0);
    gpio_init(SWITCH_GPIO_2, "in", 0);
    gpio_init(SWITCH_GPIO_3, "in", 0);
}

void update_process_lcd(processor_t *processor) {
  if(processor -> update) {
    fprintf(stderr, "UPDATE\n");
    processor -> update = 0;
  } else {
    return;
  }
  if(!(processor -> switch_state[2])) {
    return;
  }
  fprintf(stderr, "test");
  char dist_state[10], dly_state[10];
  if (!(processor -> switch_state[0])) {
    sprintf(dist_state, "%s", "ON");
  } else {
    sprintf(dist_state, "%s", "OFF");
  }
  fprintf(stderr, "test");
  if (!(processor -> switch_state[1])) {
    sprintf(dly_state, "%s", "ON");
  } else {
    sprintf(dly_state, "%s", "OFF");
  }
  fprintf(stderr, "test");
  char lcd_str[20];
  sprintf(lcd_str, "%s:%s %s:%s", "DIST", dist_state, "DLY", dly_state);
  fprintf(stderr, "test");
 
  lcd_disp(processor -> lcd, lcd_str);
  fprintf(stderr, "%s\n", lcd_str);
}

void lcd_disp(lcd_pinout *lcd, char *message) {
    //down_semaphore
    fprintf(stderr, "Ispisujem: %s\n", message);
    sem_wait(&lcdSem);
    lcd_clear(lcd);
    lcd_print(lcd, message);
    //up_semaphore
    sem_post(&lcdSem);
}

void *switch_interrupt_handler_1(void *arg) {
    // int temp = state;
    // fprintf(stderr, "POZDRAV!");
    // while(1) {
    //   sleep(1);
    //   state = gpio_get_value(SWITCH_GPIO_1);
    //     if (temp != state) {
    //       fprintf(stderr, "CHANGE OCCURED!\n");
    //       temp = state;
    //     }
    //   }
    return NULL;
}

void *switch_monitor(void *arg) {
  processor_t *processor = (processor_t *) arg;
  int temp_state[SWITCH_NUM], i;
  while(1) {
    usleep(20000);
    for (i = 0; i < SWITCH_NUM; i++) {
      temp_state[i] = gpio_get_value(processor -> switch_id_list[i]);
      if (temp_state[i] != processor -> switch_state[i]) {
        processor -> update = 1;
      }
      processor -> switch_state[i] = temp_state[i];
    }
    update_process_lcd(processor);
  }
  return NULL;
}

lcd_pinout *create_lcd() {
  lcd_pinout *forExport = (lcd_pinout *) malloc(sizeof(lcd_pinout));
  lcd_fill_pinout(forExport);
  lcd_init(forExport);
  sem_init(&lcdSem, 0, 1);
  return forExport;
}
