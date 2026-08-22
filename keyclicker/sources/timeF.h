#ifndef TIMEF_H
#define TIMEF_H


/*** Include ***/

#include "calculations.h"
#include <stdbool.h>


/*** Variables ***/

extern bool timeToggle;
extern bool filled;

extern const int TIME_SELECT_PIN;
extern const int OFFSET_SELECT_PIN;
extern const int OFFSET_LED_PINS[4];

typedef enum {OFF, LOW, MEDIUM, HIGH} OL;
extern OL offsetLevel;


/*** Function Prototypes ***/

int calc_Offset(OL offsetLevel, int seconds);
void offset_Select(void);
void set_Countdown(int countdown, int digits[]);
int set_Seconds(int seconds, int digits[]);
bool time_Button(void);


#endif
