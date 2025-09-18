#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile int btnstate = 1;
volatile int btnchange = 0;
void btn_callback(uint gpio, uint32_t events) {
  if (events & GPIO_IRQ_EDGE_FALL) {
    btnstate = 0;// fall edge
    btnchange = 1;
  } 
  if (events & GPIO_IRQ_EDGE_RISE) {
    btnstate = 1; // rise edge
    btnchange = 1;
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
    if(btnchange){
      int n = btnstate;
      btnchange = 0;
      if(n==0){printf("fall\n");}
      else{printf("rise\n");}
    }
      
}
}