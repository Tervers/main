#ifndef DISPLAY_H
#define DISPLAY_H

void write_Data(int value);
void shift_Out(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);
void select_Digit(uint8_t value);
void update_Display(int digits[], DP decimalPoint);

#endif
