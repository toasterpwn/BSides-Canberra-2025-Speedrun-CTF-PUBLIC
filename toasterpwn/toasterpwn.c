#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "user_interface.h"


typedef struct {
    uint32_t cooking_time;
    uint32_t cooling_time;
    char* name;
    char* message;
} profile_t;

profile_t profiles[] = {
    {0}, // Empty slot so we dont need -1 everywhere
    {.name = "White", .message="Enjoy your bread", .cooking_time=0, .cooling_time=5},
    {.name = "Golden", .message="Enjoy your slightly cooked toast", .cooking_time=15, .cooling_time=5},
    {.name = "Golden Brown", .message="Enjoy your toast", .cooking_time=30, .cooling_time=5},
    {.name = "Browned", .message="Enjoy your toast", .cooking_time=45, .cooling_time=5}, 
    {.name = "Charred", .message="Enjoy your toast, atleast the edible parts", .cooking_time = 60, .cooling_time=5},
    {.name = "Beyond Charred", .message="bsides{now_try_it_on_remote!}", .cooking_time=3600, .cooling_time=5},
    {.name = "User 1", .message="Enjoy your toast!", .cooking_time = 0, .cooling_time=10},
    {.name = "User 2", .message="Enjoy your toast!", .cooking_time = 0, .cooling_time=10},
    {.name = "User 3", .message="Enjoy your toast!", .cooking_time = 0, .cooling_time=10},
};


int main() {
    stdio_init_all();
    ui_init();

    profile_t* current_profile = NULL;
    bool showing_standby = true;

    ui_show("toasterpwn (The BSides Canberra Speedrun CTF Challenge)", "By HexF");

    while(1) {
        

        if(current_profile != NULL) {
            char profile_info[32] = {0};
            snprintf(profile_info, 31, "Cook: %d s, Cool: %d s", current_profile->cooking_time, current_profile->cooling_time);
            ui_show(current_profile->name, profile_info);
            showing_standby = false;
        }


        uint8_t menu_input = ui_get_hex_timeout(5000);

        if (menu_input == UI_NO_DIGIT && !showing_standby) {
            // Timeout
            ui_show("toasterpwn (The BSides Canberra Speedrun CTF Challenge)", "By HexF");
            current_profile = NULL;
            showing_standby = true;
        } else if (menu_input == UI_KEY_HASH && current_profile != NULL) {
            uint32_t delay_ms = (current_profile->cooking_time + current_profile->cooling_time) * 1000;

            char progress_line[17] = "----------------";
            ui_show(NULL, progress_line);

            for(size_t i=0; i < 16; i++) {
                sleep_ms(delay_ms / 16);
                progress_line[i] = 'X';
                ui_show(NULL, progress_line);
            }

            ui_show(NULL, current_profile->message);
            current_profile = NULL;
        } else if (menu_input == UI_KEY_STAR) {
            showing_standby = false;
            current_profile = NULL;

            ui_show("Edit: Profile #?", NULL);

            uint32_t profile_num = ui_get_number();

            if(profile_num == 0) {
                ui_show("No profile selected", "");
                continue;
            }

            profile_t* profile = &profiles[profile_num];

            if(profile == &profiles[1] || profile == &profiles[2] || profile == &profiles[3] ||
                profile == &profiles[4] || profile == &profiles[5] || profile == &profiles[6]) {
                    ui_show("Non-user profile selected", "");
                    continue;
            }


            ui_show("Edit: Cook Time?", NULL);
            profile->cooking_time = ui_get_number();

            ui_show("Edit: Cool Time?", NULL);
            profile->cooling_time = ui_get_number();

            ui_show("Edit: Success", "");
        } else if (menu_input <= 9) {
            current_profile = &profiles[menu_input];
        }
    }



    
}