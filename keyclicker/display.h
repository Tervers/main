#ifndef DISPLAY_H
#define DISPLAY_H

extern int digitValue;
extern int digits[];
typedef enum {THOUSANDS, HUNDREDTHS, TENTHS, NONE} DP;
extern DP decimalPoint;

extern bool LSBFIRST;
extern bool MSBFIRST;

struct circle {
	int digit;
	uint8_t shape;
} sections[];
extern circle sections;

void write_Data(int value);
void shift_Out(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);
void select_Digit(uint8_t value);
void update_Display(int digits[], DP decimalPoint);

#endif
