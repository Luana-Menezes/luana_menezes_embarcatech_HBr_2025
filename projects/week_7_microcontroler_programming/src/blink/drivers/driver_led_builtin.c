#include "pico/cyw43_arch.h"

#include "pico/stdlib.h"

int driver_led_init(){
  if (cyw43_arch_init()) {
      return -1;
  }
  
  return 0;
}

void driver_set_led_state(bool state) {
  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
}