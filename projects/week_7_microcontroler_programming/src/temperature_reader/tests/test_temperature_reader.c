#include "unity/unity.h"
#include "../temperature_reader.h"
#include "pico/stdlib.h"
#include <stdio.h>

void setUp(void) {
}

void tearDown(void) {
}

void test_adc_to_temperature(void) {
    //0.706V adc_value = 0.706 / 3.3 * 4096 ≈ 876
    float temperature = adc_to_celsius(876);
    TEST_ASSERT_FLOAT_WITHIN(0.5f, 27.0f, temperature);
}

int main(void) {
    stdio_init_all();
    
    for (int i = 0; i < 100; i++) {
        if (stdio_usb_connected()) {
            break;
        }
        sleep_ms(100);
    }

    printf("\n\n\n");
    printf("****************\n");
    printf("*  UNIT TEST   *\n");
    printf("****************\n\n");
    
    sleep_ms(2000);
    
    printf("Starting tests...\n");
    UNITY_BEGIN();
    
    printf("Running test_adc_to_temperature...\n");
    RUN_TEST(test_adc_to_temperature);
    
    int result = UNITY_END();
    printf("\nTests complete. Result: %s\n", result == 0 ? "PASS" : "FAIL");
    
    while (true) {
        sleep_ms(1000);
    }
    
    return result;
}