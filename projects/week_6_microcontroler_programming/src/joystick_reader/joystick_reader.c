#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "inc/ssd1306.h"


#define DISPLAY_I2C_PORT i2c1
#define DISPLAY_I2C_SDA 14
#define DISPLAY_I2C_SCL 15

#define JOYSTICK_X_PIN 26
#define JOYSTICK_Y_PIN 27
#define JOYSTICK_BTN_PIN 22

uint16_t x_value = 0;
uint16_t y_value = 0;

void joystInit() {
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);
}

struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

uint8_t display[ssd1306_buffer_length];

void displayClear() {
    memset(display, 0, ssd1306_buffer_length);
    render_on_display(display, &frame_area);
}

void displayInit(){
    i2c_init(DISPLAY_I2C_PORT, ssd1306_i2c_clock * 1000);
  
    gpio_set_function(DISPLAY_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(DISPLAY_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(DISPLAY_I2C_SDA);
    gpio_pull_up(DISPLAY_I2C_SCL);

    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area);
    displayClear();
}

void update_display(){
    displayClear();
    
    char buffer[20];

    snprintf(buffer, sizeof(buffer), "X: %d", x_value);
    ssd1306_draw_string(display, 0, 0, buffer);
    
    snprintf(buffer, sizeof(buffer), "Y: %d", y_value);
    ssd1306_draw_string(display, 0, 16, buffer);
    
    render_on_display(display, &frame_area);
}

int main()
{
    stdio_init_all();
    joystInit();
    displayInit();

    while(true){
        adc_select_input(0); //GPIO26 está no ADC0
        x_value = adc_read(); //0-4095
        
        adc_select_input(1); //GPIO27 está no ADC1
        y_value = adc_read(); //0-4095

        update_display();
        sleep_ms(10);
    }

    return 0;
}