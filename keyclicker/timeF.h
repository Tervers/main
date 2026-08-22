#ifndef TIMEF_H
#define TIMEF_H


/*** Include ***/

#include "calculations.h"
#include <stdbool.h>


/*** Variables ***/

extern const int TIME_SELECT_PIN;
extern const int OFFSET_SELECT_PIN;
extern const int OFFSET_LED_PINS[4];

extern bool timeToggle;
extern bool filled;

typedef enum {OFF, LOW, MEDIUM, HIGH} OL;
extern OL offsetLevel;


/*** Function Prototypes ***/

int set_Seconds(int seconds, int digits[]);
int calc_Offset(OL offsetLevel, int seconds);
void set_Countdown(int countdown, int digits[]);
bool time_Button(void);
void offset_Select(void);


#endif
