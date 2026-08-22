#ifndef GPIO_H
#define GPIO_H


/*** Includes ***/

#include "pico/stdlib.h"
#include <stdint.h>


/*** Variables ***/

extern const int SERVO_ANALOG;
extern const int TIME_ANALOG;


/*** Function Prototypes ***/

uint16_t analog_Read(uint p);


#endif
