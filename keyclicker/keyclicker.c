/* Library includes */
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "pico/time.h"
//#include <pthread.h>
#include "pico/multicore.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Pin number defines */
#define ANGLE_SELECT_PIN 13
#define DATA_PIN 18
#define TIME_SELECT_PIN 19
#define LATCH_PIN 20
#define CLOCK_PIN 21
#define SERVO_PIN 22
#define SERVO_ANALOG 26
#define TIME_ANALOG 28
#define OFFSET_SELECT_PIN 12
const int DISPLAY_PINS[] = {17, 16, 15, 14};
const int OFFSET_LED_PINS[] = {9, 10, 11};

/* Servo arm angle restrictions */
#define MINIMUM_ANGLE 10
#define MAXIMUM_ANGLE 170

/* 74HC595 shift register control values */
bool LSBFIRST = 0;
bool MSBFIRST = 1;

/* Servo control values */
typedef struct {
  uint gpio;
  uint slice;
  uint chan;
  uint speed;
  uint resolution;
  bool on;
  bool invert;
} Servo;
Servo mainServo;
int pos = 0;
int setAngle = 0;

/* Time control values */
int timer = 0;
int countdown = 0;
int seconds = 0;
uint32_t now = 0;
uint32_t stop = 0;
enum {OFF, LOW, MEDIUM, HIGH} offsetLevel;
int offsetAmount = 0;
bool filled = false;

/* Display control values */
int digitValue;
int digits[4];

/* Loop control values */
bool startToggle = false;
bool timeToggle = false;
bool angleToggle = false;

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

/* Prototypes */
void select_Digit(uint8_t value);
void write_Data(int value);
void set_Digits(int value);
void write_Display(int value, int a[]);
void pwm_Set_Duty_H(uint slice_num, uint chan, int d);
void servo_Init(uint gpio);
void servo_On(Servo *s);
void servo_Off(Servo *s);
void servo_Position(uint gpio, int angle);
uint16_t analog_Read(uint p);
long map(long x, long in_min, long in_max, long out_min, long out_max);
uint32_t pwm_Get_Wrap(uint slice_num);
uint32_t pwm_Set_Freq_Duty(uint slice_num,uint chan, uint32_t f, int d);
void shift_Out(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);
void offset_Select(void);

/* Start */
int main(void) {

  /* Initialize srand to generate random values */
  srand((unsigned) time(NULL));

  /* Initialize Pins */
  stdio_init_all();
  adc_init();
  gpio_init(ANGLE_SELECT_PIN);
  gpio_set_dir(ANGLE_SELECT_PIN, GPIO_IN);
  gpio_pull_up(ANGLE_SELECT_PIN);
  gpio_init(TIME_SELECT_PIN);
  gpio_set_dir(TIME_SELECT_PIN, GPIO_IN);
  gpio_pull_up(TIME_SELECT_PIN);
  gpio_init(LATCH_PIN);
  gpio_set_dir(LATCH_PIN, GPIO_OUT);
  gpio_init(CLOCK_PIN);
  gpio_set_dir(CLOCK_PIN, GPIO_OUT);
  gpio_init(DATA_PIN);
  gpio_set_dir(DATA_PIN, GPIO_OUT);
  gpio_init(SERVO_PIN);
  gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
  adc_gpio_init(SERVO_ANALOG);
  adc_gpio_init(TIME_ANALOG);
  for (int i = 0; i < 4; i++) {
    gpio_init(DISPLAY_PINS[i]);
    gpio_set_dir(DISPLAY_PINS[i], GPIO_OUT);
  }
  for (int i = 0; i < 2; i++) {
    gpio_init(OFFSET_LED_PINS[i]);
    gpio_set_dir(OFFSET_LED_PINS[i], GPIO_OUT);
  }

  /* Initialize servo */
  servo_Init(SERVO_PIN);
  servo_On(&mainServo);

  /* Initialize potentiometer positions */
  setAngle = map(analog_Read(SERVO_ANALOG), 0, 4095, MAXIMUM_ANGLE, MINIMUM_ANGLE);
  seconds = map(analog_Read(TIME_ANALOG), 0, 4095, 60, 0);

  /* Initialize offset thread */
	multicore_launch_core1(offset_Select);

  /* Entire program loop */
  while(1) {

    /* Main keyclicker loop */
    while (!timeToggle && !angleToggle) {
      for (int i = 0, pos = setAngle; pos < setAngle + 6; pos += 1, i++) {
	servo_Position(SERVO_PIN, pos);
	for (int j = 0; j < 4; j++) {
	  select_Digit(sections[i].digit);
	  write_Data(sections[i].shape);
	  now = to_ms_since_boot(get_absolute_time());
	  sleep_ms(5);
	}
      }
      for (int i = 6, pos = setAngle; pos > setAngle - 6; pos -= 1, i++) {
	servo_Position(SERVO_PIN, pos);
	for (int j = 0; j < 4; j++) {
	  select_Digit(sections[i].digit);
	  write_Data(sections[i].shape);
	  sleep_ms(5);
	}
      }
      now = to_ms_since_boot(get_absolute_time());
      timer = (now + (seconds * 1000) + offsetAmount);
      while (to_ms_since_boot(get_absolute_time()) < (now + (seconds * 1000) + offsetAmount)) {
	countdown = timer - to_ms_since_boot(get_absolute_time());
	if (countdown > 9999) {
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
	for (int i = 0; i < 4; i++) {
	  select_Digit(i);
	  digitValue = digits[i];
	  if (i == 2) 
	    write_Data(num[digitValue] | 0x80);
	  else 
	    write_Data(num[digitValue]);
	  sleep_ms(5);
	  write_Data(0x00);      
	}
	for (int i = 0; i < 4; i++) {
	  select_Digit(i);
	  write_Data(0x00);
	}
	if (!gpio_get(TIME_SELECT_PIN)) {
	  sleep_ms(20);
	  if (!gpio_get(TIME_SELECT_PIN)) {
	    timeToggle = true;
	    startToggle = false;
	    break;
          }
        }
        if (!gpio_get(ANGLE_SELECT_PIN)) {
	  sleep_ms(20);
	  if (!gpio_get(ANGLE_SELECT_PIN)) {
	    angleToggle = true;
	    startToggle = false;
	    break;
	  }
        }
      }
    }
    sleep_ms(200);

    /* Time delay select loop */
    while (timeToggle) {
      seconds = map(analog_Read(TIME_ANALOG), 0, 4095, 60, 0);
      digits[1] = ((seconds % 1000) / 100);
      digits[2] = ((seconds % 100) / 10);
      digits[3] = (seconds % 10);
      for (int i = 1; i < 4; i++) {
	select_Digit(i);
	digitValue = digits[i];
	write_Data(num[digitValue]);
	sleep_ms(5);
	write_Data(0x00);      
      }
      if (!gpio_get(TIME_SELECT_PIN)) {
	sleep_ms(20);
	if (!gpio_get(TIME_SELECT_PIN)) 
	  timeToggle = false;
      }
    }
		
    /* Servo arm angle select loop */
    while (angleToggle) {
      setAngle = map(analog_Read(SERVO_ANALOG), 0, 4095, MAXIMUM_ANGLE, MINIMUM_ANGLE);
      servo_Position(SERVO_PIN, setAngle);
      digits[1] = ((setAngle % 1000) / 100);
      digits[2] = ((setAngle % 100) / 10);
      digits[3] = (setAngle % 10);
      for (int i = 1; i < 4; i++) {
	select_Digit(i);
	digitValue = digits[i];
	write_Data(num[digitValue]);
	sleep_ms(5);
	write_Data(0x00);      
      }
      if (!gpio_get(ANGLE_SELECT_PIN)) {
	sleep_ms(20);
	if (!gpio_get(ANGLE_SELECT_PIN)) {
	  angleToggle = false;
	}
      }
    }
  }
}

/* Function Definitions */
void pwm_Set_Duty_H(uint slice_num, uint chan, int d) {  // d is 0-10000
  pwm_set_chan_level(slice_num, chan, pwm_Get_Wrap(slice_num) * d / 10000);
}

void servo_Init(uint gpio) {
  gpio_set_function(gpio, GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(gpio);
  pwm_set_clkdiv(slice_num, 125.0f);  // Configure for 50Hz frequency output
  pwm_set_wrap(slice_num, 19999);
  pwm_set_enabled(slice_num, true);
}

void servo_Position(uint gpio, int angle) {
  if (angle < MINIMUM_ANGLE)
    angle = MINIMUM_ANGLE;
  if (angle > MAXIMUM_ANGLE)
    angle = MAXIMUM_ANGLE;
  // Linear map: 0 deg -> 500, 180 deg -> 2500
  uint32_t duty_count = 500 + (angle * 2000 / 180);
  pwm_set_gpio_level(gpio, duty_count);
}

void servo_On(Servo *s) {
  pwm_set_enabled(s->slice, true);
  s->on = true;
}

void servo_Off(Servo *s) {
  pwm_set_enabled(s->slice, false);
  s->on = false;
}

uint16_t analog_Read(uint p) {
  uint16_t result = 0;
  if (p == SERVO_ANALOG) {
    adc_select_input(0);
    result = adc_read();
  }
  else if (p == TIME_ANALOG) {
    adc_select_input(2);
    result = adc_read();
  }
  return result;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

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

uint32_t pwm_Get_Wrap(uint slice_num) {
  if (slice_num < 0 || slice_num >= NUM_PWM_SLICES) {
    return 0;
  }
  return pwm_hw->slice[slice_num].top;
}

uint32_t pwm_Set_Freq_Duty(uint slice_num, uint chan, uint32_t f, int d) {
  uint32_t clock = 125000000;
  uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);
  if (divider16 / 16 == 0)
    divider16 = 16;
  uint32_t wrap = clock * 16 / divider16 / f - 1;
  pwm_set_clkdiv_int_frac(slice_num, divider16/16, divider16 & 0xF);
  pwm_set_wrap(slice_num, wrap);
  pwm_set_chan_level(slice_num, chan, wrap * d / 100);
  return wrap;
}

void write_Data(int value) {
  gpio_put(LATCH_PIN, 0);
  shift_Out(DATA_PIN, CLOCK_PIN, LSBFIRST, value);  // Send serial data to 74HC595
  gpio_put(LATCH_PIN, 1); // High level will update data to parallel output (74HC595)
}

void offset_Select(void) {
  while(1) {
    if (!gpio_get(OFFSET_SELECT_PIN)) {
      sleep_ms(20);
      if (!gpio_get(OFFSET_SELECT_PIN)) {
	switch (offsetLevel) {
	  case 0: offsetLevel++;
	          gpio_put(OFFSET_LED_PINS[offsetLevel], 1);
		  break;
	  case 1: case 2:
		  gpio_put(OFFSET_LED_PINS[offsetLevel], 0);
	          gpio_put(OFFSET_LED_PINS[++offsetLevel], 1);
		  break;
	  case 3: gpio_put(OFFSET_LED_PINS[offsetLevel], 0);
		  offsetLevel = 0;
		  break;
        }
      }
    }
    switch (offsetLevel) {
      case 0: offsetAmount = 0;
	      break;
      case 1: if (seconds == 0)
                seconds = 1;
	      offsetAmount = (seconds * (rand() % 21) * 10);
	      break;
      case 2: if (seconds == 0)
                seconds = 1;
	      offsetAmount = (seconds * (rand() % 51) * 10);
	      break;
      /* Variability based on 'Coupon Collector's Problem' */
      case 3: if (seconds == 0)
                seconds = 1;
              int attemptValue = 0;
	      int failures = 0;
	      bool collection[5];
              while (!filled) {
		attemptValue = rand() % 5;
		if (collection[attemptValue] == false)
		  collection[attemptValue] == true;
		else
		  failures++;
		for (int i = 0; i < 5; i++) {
                  if (collection[i] == false)
		    break;
		  else
	            filled = true;
		}
	      }
	      offsetAmount = (seconds * failures * ((rand() % 100) + 1) * 10);
	      break;
    }
  }
}
