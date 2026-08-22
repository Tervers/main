#include "display.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

/* Display control values */
int digitValue;
int digits[4];
typedef enum {THOUSANDTHS, HUNDREDTHS, TENTHS, NONE} DP;
DP decimalPoint = NONE;

/* 74HC595 shift register control values */
bool LSBFIRST = 0;
bool MSBFIRST = 1;

/* Values that will draw a circle around the display */
struct circle {
  int digit;
  uint8_t shape;
} sections[12] = {
  {3, 0x04},
  {3, 0x08},
  {2, 0x08},
  {1, 0x08},
  {0, 0x08},
  {0, 0x10},
  {0, 0x20},
  {0, 0x01},
  {1, 0x01},
  {2, 0x01},
  {3, 0x01},
  {3, 0x02}
};

/* Hex values representing characters 0 through 9 */
uint8_t num[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void select_Digit(uint8_t value) {
  for (int i = 0; i < 4; i++) {
    gpio_put(DISPLAY_PINS[i], 1);    // Clear all 7-segment digits
  }
  gpio_put(DISPLAY_PINS[value], 0);  // Open the selected individual 7-segment display
}

void shift_Out(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value) {
  uint8_t i;
  for (i = 0; i < 8; i++)  {
    if (bitOrder == LSBFIRST)
      gpio_put(dataPin, !!(value & (1 << i)));
    else
      gpio_put(dataPin, !!(value & (1 << (7 - i))));
    gpio_put(clockPin, 1);
    gpio_put(clockPin, 0);
  }
}

void write_Data(int value) {
  gpio_put(LATCH_PIN, 0);
  shift_Out(DATA_PIN, CLOCK_PIN, LSBFIRST, value);  // Send serial data to 74HC595
  gpio_put(LATCH_PIN, 1); // High level will update data to parallel output (74HC595)
}

void update_Display(int digits[], DP decimalPoint) {
        for (int i = 0; i < 4; i++) {
          select_Digit(i);
          digitValue = digits[i];
          switch(decimalPoint) {
            case 0: if (i == 0)
                      write_Data(num[digitValue] | 0x80);
                    else
                      write_Data(num[digitValue]);
                    break;
            case 1: if (i == 1)
                      write_Data(num[digitValue] | 0x80);
                    else
                      write_Data(num[digitValue]);
                    break;
            case 2: if (i == 2)
                      write_Data(num[digitValue] | 0x80);
                    else
                      write_Data(num[digitValue]);
                    break;
            case 3: write_Data(num[digitValue]);
                    break;
          }
          sleep_ms(5);
          write_Data(0x00);
        }
}
