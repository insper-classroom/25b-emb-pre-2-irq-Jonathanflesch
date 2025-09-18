#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int pinled = 4;
const int pinbtn = 28; 

volatile int btnstate;
volatile int change = 0;

void gpio_callback(uint gpio, uint32_t events){
  if(events & 0x4){
    btnstate = 1;
  }
}


int main() {

  stdio_init_all();
  gpio_init(pinled);
  gpio_set_dir(pinled, GPIO_OUT);
  gpio_init(pinbtn);
  gpio_set_dir(pinbtn, GPIO_IN);
  gpio_pull_up(pinbtn);
  gpio_set_irq_enabled_with_callback(pinbtn, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);


  while (true) {
    if(btnstate){
      btnstate = 0;
      change ^= 1;
      gpio_put(pinled, change);
  }
}
}
