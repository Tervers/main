/*** Includes ***/

#include "gpioF.h"
#include "hardware/adc.h"


/*** Function Definitions ***/

uint16_t analog_Read(uint p) {
  uint16_t result = 0;
  if (p == TIME_ANALOG) {
    adc_select_input(0);
    result = adc_read();
  }
  else if (p == SERVO_ANALOG) {
    adc_select_input(1);
    result = adc_read();
  }
  return result;
}
