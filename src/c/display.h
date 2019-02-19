#ifndef DISPLAY_H
#define DISPLAY_H

#include "custom_types.h"

void strencode2digit(char *str, int digit, bool singledigit); // TODO: REMOVE
void update_mode_visual(uint8_t old_m, uint8_t m);
void display_time(uint8_t old_mode);

#endif
