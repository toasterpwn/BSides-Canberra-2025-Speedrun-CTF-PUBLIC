#include "pico/time.h"
#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "user_interface.h"
#include "lcd_1602_i2c.h"

#define UI_TEXT_MAX_LENGTH (64)
#define DISPLAY_WIDTH (16)
#define DISPLAY_WRAPAROUND_GAP (3)

uint8_t keypad_col_pins[] = {0,1,2,3};
uint8_t keypad_row_pins[] = {4,5,6,7};
uint16_t keypad_held_keys = 0;
size_t keypad_held_for[16] = {0};
char keypad_keymap[] = {
    0x1, 0x2, 0x3, 0xA,
    0x4, 0x5, 0x6, 0xB,
    0x7, 0x8, 0x9, 0xC,
    0xE, 0x0, 0xF, 0xD
};


static uint8_t next_digit = UI_NO_DIGIT; 

static char display_line_buffers[2][UI_TEXT_MAX_LENGTH + DISPLAY_WRAPAROUND_GAP + 1] = {0};
static uint8_t display_line_offsets[2] = {0, 0};

static uint32_t display_next_update_ms = 0;


void ui_init() {
    i2c_init(i2c1, 1000 * 1000);
    gpio_set_function(26, GPIO_FUNC_I2C);
    gpio_set_function(27, GPIO_FUNC_I2C);
    gpio_pull_up(26);
    gpio_pull_up(27);

    lcd_init();

    for (size_t i = 0; i < 4; i++)
    {
        gpio_init(keypad_row_pins[i]);
        gpio_init(keypad_col_pins[i]);

        gpio_set_dir(keypad_col_pins[i], GPIO_OUT);
        gpio_put(keypad_col_pins[i], false);

        gpio_set_dir(keypad_row_pins[i], GPIO_IN);
        gpio_pull_down(keypad_row_pins[i]);
    }
}

uint8_t ui_get_hex_timeout(uint32_t timeout_ms){
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    uint32_t end_time = current_time + timeout_ms;
    while(next_digit == UI_NO_DIGIT && current_time < end_time) {
        ui_update();
        current_time = to_ms_since_boot(get_absolute_time());
    }

    uint8_t digit = next_digit;
    next_digit = UI_NO_DIGIT;
    return digit;
}

uint8_t ui_get_hex(){
    return ui_get_hex_timeout(60*60*1000); // 1 hour should be good
}

uint32_t ui_get_number(){
    uint32_t current_number = 0;
    char current_number_str[DISPLAY_WIDTH + 1] = {0};

    snprintf(current_number_str, DISPLAY_WIDTH, "%d", current_number);
    ui_show(NULL, current_number_str);

    while(1) {
        uint8_t next_digit = ui_get_hex();

        if(next_digit < 10) { // Digit for display!
            if(current_number < 1000000000) { 
                current_number *= 10;
                current_number += next_digit;
            }
        } else {
            break; 
        }

        snprintf(current_number_str, DISPLAY_WIDTH, "%d", current_number);
        ui_show(NULL, current_number_str);
    }


    return current_number;
}

void ui_show(char* top_line, char* bottom_line) {
    for (uint8_t i = 0; i < 2; i++)
    {
        char* line_input = i == 0 ? top_line : bottom_line;

        if(line_input != NULL){
            uint8_t line_length = strlen(line_input);

            memset(display_line_buffers[i], 0, UI_TEXT_MAX_LENGTH);
            strncpy(display_line_buffers[i], line_input, UI_TEXT_MAX_LENGTH);

            if(line_length > DISPLAY_WIDTH) {
                memset(display_line_buffers[i] + line_length, ' ', DISPLAY_WRAPAROUND_GAP);
            }

            display_line_offsets[i] = 0;
        }
    }
    

    display_next_update_ms = 0;
    ui_update();
}


void ui_update_display_line(uint8_t line_num) {
    // Compute current display content
    char line_data[DISPLAY_WIDTH+1] = {0};
    char line_data_space_padded[DISPLAY_WIDTH+1] = {0};

    uint8_t length = strlen(display_line_buffers[line_num]);
    bool scrolls = length > DISPLAY_WIDTH;

    if(scrolls){
        uint8_t offset = display_line_offsets[line_num];

        if(offset + DISPLAY_WIDTH > length) {
            uint8_t remaining_chars = length - offset;
            // Wraps around
            strncpy(line_data, display_line_buffers[line_num] + offset, remaining_chars);
            strncpy(line_data + remaining_chars, display_line_buffers[line_num], DISPLAY_WIDTH - remaining_chars);
        } else {
            strncpy(line_data, display_line_buffers[line_num] + offset, DISPLAY_WIDTH);
        }

        display_line_offsets[line_num] += 1;
        display_line_offsets[line_num] %= length;
    } else {
        strncpy(line_data, display_line_buffers[line_num], DISPLAY_WIDTH);
    }
    

    

    // Serial Output
    printf("\033[s"); // Save cursor pos
    printf("\033[%d;%df", line_num + 1, 1); // Set cursor to start of line
    printf("\033[0K"); // Erase entire line
    printf("%s", line_data);
    printf("\033[u"); // Restore line


    lcd_set_cursor(line_num, 0);
    snprintf(line_data_space_padded,DISPLAY_WIDTH, "%s                ", line_data);
    lcd_string(line_data_space_padded);
}

void ui_update_button_matrix() { 
    static size_t col_num = 0;
   
    for (size_t row_num = 0; row_num < 4; row_num++)
    {
        size_t key_idx = 4 * row_num + col_num;
        bool is_set = gpio_get(keypad_row_pins[row_num]);
        bool is_set_stored = (keypad_held_keys >> key_idx) & 1;
        if(is_set == is_set_stored) {
            keypad_held_for[key_idx]++;

            if(keypad_held_for[key_idx] == 10 && !is_set) {
                next_digit = keypad_keymap[key_idx];
            }
        } else {
            keypad_held_for[key_idx] = 0;
            keypad_held_keys ^= 1 << key_idx;
        }

        

    }

    col_num += 1;
    col_num %= 4;

     
    // Turn off prev cols
    uint32_t clr_bits = 0;
    for (size_t i = 0; i < 4; i++)
    {
        clr_bits |= (1 << keypad_col_pins[i]);
    }
    gpio_clr_mask(clr_bits);
    gpio_put(keypad_col_pins[col_num], 1);
    sleep_us(250);

}

void ui_update() {
    // TODO: poll button matrix
    ui_update_button_matrix();

    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if(current_time > display_next_update_ms) {
        display_next_update_ms = current_time + 250;
        
        ui_update_display_line(0);
        ui_update_display_line(1);
    }

    // Check Serial Input
    int input_char = getchar_timeout_us(0);
    if(input_char >= '0' && input_char <= '9') {
        // Digit
        next_digit = input_char - '0';
    } else if(input_char >= 'A' && input_char <= 'F') {
        // Hex Digit Upper
        next_digit = input_char - 'A' + 10;
    } else if(input_char >= 'a' && input_char <= 'f') {
        // Hex Digit Lower
        next_digit = input_char - 'a' + 10;
    } else if(input_char == '#' || input_char == '\n') {
        next_digit = UI_KEY_HASH;
    } else if(input_char == '*') {
        next_digit = UI_KEY_STAR;
    }
}