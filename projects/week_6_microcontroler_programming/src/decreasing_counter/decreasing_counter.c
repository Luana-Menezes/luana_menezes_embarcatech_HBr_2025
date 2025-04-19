#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "inc/ssd1306.h"

#define BTN_A 5
#define BTN_B 6

#define DISPLAY_I2C_PORT i2c1
#define DISPLAY_I2C_SDA 14
#define DISPLAY_I2C_SCL 15

volatile int time_counter = 0;
volatile int btn_b_clicks_count = 0;
volatile bool counting_active = false;

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

void gpio_callback(uint gpio, uint32_t events) {
    if (gpio == BTN_A) {
        time_counter = 9;
        btn_b_clicks_count = 0;
        counting_active = true;
    } else if (gpio == BTN_B) {
        if (counting_active && time_counter > 0) {
            btn_b_clicks_count++;
        }
    }
}

void update_display(){
    displayClear();
    
    char buffer[20];

    snprintf(buffer, sizeof(buffer), "Counter: %d", time_counter);
    ssd1306_draw_string(display, 0, 0, buffer);
    
    snprintf(buffer, sizeof(buffer), "B presses: %d", btn_b_clicks_count);
    ssd1306_draw_string(display, 0, 16, buffer);
    
    render_on_display(display, &frame_area);
}

int main()
{
    stdio_init_all();

    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);

    displayInit();

    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled(BTN_B, GPIO_IRQ_EDGE_FALL, true);

    uint32_t last_time = to_ms_since_boot(get_absolute_time());

    while (true) {
        uint32_t current_time = to_ms_since_boot(get_absolute_time());
        uint32_t time_diff = current_time - last_time;

        if (time_diff >= 1000 && counting_active) {
            if(time_counter > 0){
                time_counter--;
                last_time = current_time;
            } else {
                counting_active = false;
            }
        }

        update_display();
        sleep_ms(10);
    }
    
    return 0;
}