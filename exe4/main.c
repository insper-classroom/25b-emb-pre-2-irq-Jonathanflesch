#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int pinledr = 4;
const int pinledg = 6;

const int btnr = 28;
const int btng = 26;

volatile int btnrstate;
volatile int btngstate;

void gpio_callback(uint gpio, uint32_t events){
  if(gpio == btnr && events & 0x4){
    btnrstate = 1;
  }
  if(gpio == btng && events & 0x8){
    btngstate = 1;
  }
}

int main() {
  stdio_init_all();
  gpio_init(pinledr);
  gpio_set_dir(pinledr, GPIO_OUT);
  gpio_init(pinledg);
  gpio_set_dir(pinledg, GPIO_OUT);
  gpio_init(btnr);
  gpio_set_dir(btnr, GPIO_IN);
  gpio_pull_up(btnr);
  gpio_init(btng);
  gpio_set_dir(btng, GPIO_IN);
  gpio_pull_up(btng);
  gpio_set_irq_enabled_with_callback(btnr, GPIO_IRQ_EDGE_RISE |GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
  gpio_set_irq_enabled(btng, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
  
  int toggle1 = 0;
  int toggle2 = 0;
  while (true) {
    if(btnrstate){
      btnrstate = 0;
      toggle1 ^= 1;
      gpio_put(pinledr, toggle1);
    }
    if(btngstate){
      btngstate = 0;
      toggle2 ^= 1;
      gpio_put(pinledg, toggle2);
    }
  }
}
