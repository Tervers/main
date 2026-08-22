#ifndef DISPLAY_H
#define DISPLAY_H


/*** Includes ***/

#include <stdint.h>
#include <stdbool.h>


/*** Variables ***/

extern bool LSBFIRST;
extern bool MSBFIRST;

extern int digitValue;
extern int digits[];
extern const int DISPLAY_PINS[];
extern const int LATCH_PIN, DATA_PIN, CLOCK_PIN;

typedef enum {THOUSANDS, HUNDREDTHS, TENTHS, NONE} DP;
extern DP decimalPoint;

struct circle {
	int digit;
	uint8_t shape;
}; 
extern struct circle sections[12];


/*** Function Prototypes ***/

void select_Digit(uint8_t value);
void shift_Out(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);
void update_Display(int digits[], DP decimalPoint);
void write_Data(int value);


#endif
