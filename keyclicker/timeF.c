/*** Includes ***/

#include "timeF.h"
#include "gpioF.h"
#include "hardware/gpio.h"
#include "pico/rand.h"
#include "pico/stdlib.h"
#include <string.h>


/*** Variables ***/

bool filled = false;
bool timeToggle = false;

OL offsetLevel = OFF;


/*** Functions Definitions ***/

void offset_Select(void) {
  while(1) {
    if (!gpio_get(OFFSET_SELECT_PIN)) {
      sleep_ms(20);
      if (!gpio_get(OFFSET_SELECT_PIN)) {
        sleep_ms(500);
        if (offsetLevel < 3)
          offsetLevel++;
        else
          offsetLevel = 0;
      }
    }
  }
}

int calc_Offset(OL offsetLevel, int seconds) {
      switch (offsetLevel) {
        case 0: if (gpio_get(OFFSET_LED_PINS[2]) == 1)
                  gpio_put(OFFSET_LED_PINS[2], 0);
                return 0;
        case 1: if (gpio_get(OFFSET_LED_PINS[0]) == 0)
                  gpio_put(OFFSET_LED_PINS[0], 1);
                return (seconds * (get_rand_32() % 21) * 10);
        case 2: if (gpio_get(OFFSET_LED_PINS[0]) == 1)
                  gpio_put(OFFSET_LED_PINS[0], 0);
                if (gpio_get(OFFSET_LED_PINS[1]) == 0)
                  gpio_put(OFFSET_LED_PINS[1], 1);
                return (seconds * (get_rand_32() % 51) * 10);
        case 3: if (gpio_get(OFFSET_LED_PINS[1]) == 1)
                  gpio_put(OFFSET_LED_PINS[1], 0);
                if (gpio_get(OFFSET_LED_PINS[2]) == 0)
                  gpio_put(OFFSET_LED_PINS[2], 1);
                // Variability based on 'Coupon Collector's Problem'
                bool collection[5];
                memset(collection, false, sizeof(collection));
                int attemptValue = 0;
                int failures = 0;
                filled = false;
                while (!filled) {
                  attemptValue = get_rand_32() % 5;
                  if (collection[attemptValue] == false)
                    collection[attemptValue] = true;
                  else
                    failures++;
                  for (int i = 0; i < 5; i++) {
                    if (collection[i] == false)
                      break;
                    else
                      filled = true;
                  }
                }
                return (seconds * failures * ((get_rand_32() % 100) + 1) * 10);
  }
}

bool time_Button(void) {
        if (!gpio_get(TIME_SELECT_PIN)) {
          sleep_ms(20);
          if (!gpio_get(TIME_SELECT_PIN)) {
            timeToggle = !timeToggle;
            return true;
          }
        }
          else
            return false;
}

int set_Seconds(int seconds, int digits[]) {
      seconds = map(analog_Read(TIME_ANALOG), 0, 4095, 60, 0);
      digits[1] = ((seconds % 1000) / 100);
      digits[2] = ((seconds % 100) / 10);
      digits[3] = (seconds % 10);
  return seconds;
}

void set_Countdown(int countdown, int digits[]) {
        if (countdown > 999999) {
          for (int i = 0; i < 4; i++) {
            digits[i] = 9;
          }
        }
        else {
          digits[0] = ((countdown % 1000000) / 100000);
          digits[1] = ((countdown % 100000) / 10000);
          digits[2] = ((countdown % 10000) / 1000);
          digits[3] = ((countdown % 1000) / 100);
        }
}
