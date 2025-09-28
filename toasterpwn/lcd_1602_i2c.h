#pragma once

void lcd_init();
void lcd_set_cursor(int line, int position);
void lcd_string(const char *s);