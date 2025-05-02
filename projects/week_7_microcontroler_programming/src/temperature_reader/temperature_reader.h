#pragma once

#include <stdint.h>

float adc_to_celsius(uint16_t adc_value);
void init_temperature_sensor(void);
float read_temperature(void);

