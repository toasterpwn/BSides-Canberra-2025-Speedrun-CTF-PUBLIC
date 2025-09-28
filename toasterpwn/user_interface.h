#include <stdint.h>

#define UI_NO_DIGIT (0xFF)
#define UI_KEY_STAR (0xE)
#define UI_KEY_HASH (0xF)

void ui_init();

uint8_t ui_get_hex(); // Read a digit or char from keypad (A -> 10, F -> 15)
uint32_t ui_get_number(); // Read up to a u32 in length, followed by a letter. Displays on bottom line
uint8_t ui_get_hex_timeout(uint32_t timeout_ms); // Wait for a key with a timeout


void ui_show(char* top_line, char* bottom_line); // Show text on top and bottom line
void ui_update(); // Update the UI!