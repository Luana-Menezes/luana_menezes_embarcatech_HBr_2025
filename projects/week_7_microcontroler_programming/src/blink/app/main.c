#include "pico/stdlib.h"
#include <stdio.h>
#include "../include/hal_led_bultin.h"


int main() {
    stdio_init_all();

    if (hal_led_init() != 0) {
        printf("Failed to initialize LED.\n");
        return -1;
    }

    while (true) {
        hal_led_toggle();
        sleep_ms(500);
    }

    return 0;
}