#include "../include/driver_led_builtin.h"

static bool led_state = false;

int hal_led_init(){
    return driver_led_init();
}

void hal_led_toggle(){
    led_state = !led_state;
    driver_set_led_state(led_state);
}