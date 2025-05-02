#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "temperature_reader.h"

#define ADC_TEMPERATURE_CHANNEL 4

float adc_to_celsius(uint16_t adc_value) {
    // Constantes fornecidas no datasheet do RP2040
    const float conversion_factor = 3.3f / (1 << 12);  // Conversão de 12 bits (0-4095) para 0-3.3V
    float voltage = adc_value * conversion_factor;     // Converte o valor ADC para tensão
    float temperature = 27.0f - ((voltage - 0.706f) / 0.001721f);  // Equação fornecida para conversão
    return temperature;
}

void init_temperature_sensor(void) {
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(ADC_TEMPERATURE_CHANNEL);
}

float read_temperature(void) {
    uint16_t adc_value = adc_read();
    return adc_to_celsius(adc_value);
}

#ifndef UNIT_TESTING
int main() {
    stdio_init_all();
    init_temperature_sensor();

    while (true) {
        float temperature_celsius = read_temperature();
        printf("Temperature: %.2f °C\n", temperature_celsius);
        sleep_ms(1000);
    }

    return 0;
}
#endif
