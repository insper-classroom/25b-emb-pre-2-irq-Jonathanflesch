#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile int btnstate;
void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
  } else if (events == 0x8) { // rise edge
  }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  while (true) {
    if(btnstate){
      printf("fall\n");
      btnstate = 0;
    }
    printf("rise\n");
}
}