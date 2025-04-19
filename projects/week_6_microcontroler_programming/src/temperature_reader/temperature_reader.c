#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define ADC_TEMPERATURE_CHANNEL 4

float adc_to_temperature(uint16_t adc_value) {
    // Constantes fornecidas no datasheet do RP2040
    const float conversion_factor = 3.3f / (1 << 12);  // Conversão de 12 bits (0-4095) para 0-3.3V
    float voltage = adc_value * conversion_factor;     // Converte o valor ADC para tensão
    float temperature = 27.0f - (voltage - 0.706f) / 0.001721f;  // Equação fornecida para conversão
    return temperature;
}

int main() {
    stdio_init_all();
    adc_init();

    // Seleciona o canal 4 do ADC (sensor de temperatura interno)
    adc_set_temp_sensor_enabled(true);  // Habilita o sensor de temperatura interno
    adc_select_input(ADC_TEMPERATURE_CHANNEL);  // Seleciona o canal do sensor de temperatura

    while (true) {
        uint16_t adc_value = adc_read();
        float temperature_celsius = adc_to_temperature(adc_value);

        printf("Temperature: %.2f °C\n", temperature_celsius);

        sleep_ms(1000);
    }

    return 0;
}
