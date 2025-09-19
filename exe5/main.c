#include <stdio.h>

#include "hardware/gpio.h"
#include "pico/stdlib.h"

const int btn = 28;

volatile int state = 0;

void gpio_callback(uint gpio, uint32_t events){
    if(events & 0x4){
        state = 1;
    }
    if(events & 0x8){
        state = 0;
    }
}

int main() {
    stdio_init_all();
    gpio_init(btn);
    gpio_set_dir(btn, GPIO_IN);
    gpio_pull_up(btn);
    gpio_set_irq_enabled_with_callback(btn, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE,true, &gpio_callback);

    while (true) {
        if(state){
            absolute_time_t inicio = get_absolute_time();
            while(state){

            }
            absolute_time_t fim = get_absolute_time();

            uint64_t delta = absolute_time_diff_us(inicio,fim);

            if(delta>=800000){
                printf("Aperto longo!\n");
            }
            else{
                printf("Aperto curto!\n");
            }
        }
    }
}
