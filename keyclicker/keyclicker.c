/* Library includes */ 
#include "sources/angle.h"
#include "sources/calculations.h"
#include "sources/display.h"
#include "sources/gpioF.h"
#include "sources/timeF.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

/* Pin number defines */
const int SERVO_PIN = 0;
const int OFFSET_LED_PINS[] = {1, 2, 3};
const int OFFSET_SELECT_PIN = 4;
const int DISPLAY_PINS[] = {9, 8, 7, 6};
const int LATCH_PIN = 11;
const int CLOCK_PIN = 12;
const int DATA_PIN = 13;
const int TIME_SELECT_PIN = 20;
const int ANGLE_SELECT_PIN = 21;
const int SERVO_ANALOG = 26;
const int TIME_ANALOG = 27;

/* Time control values */
int timer = 0;
int countdown = 0;
int seconds = 0;
uint32_t now = 0;

/* Start */
int main(void) {

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
  gpio_init(OFFSET_SELECT_PIN);
  gpio_set_dir(OFFSET_SELECT_PIN, GPIO_IN);
	gpio_pull_up(OFFSET_SELECT_PIN);
  adc_gpio_init(SERVO_ANALOG);
  adc_gpio_init(TIME_ANALOG);
  for (int i = 0; i < 4; i++) {
    gpio_init(DISPLAY_PINS[i]);
    gpio_set_dir(DISPLAY_PINS[i], GPIO_OUT);
  }
  for (int i = 0; i < 2; i++) {
    gpio_init(OFFSET_LED_PINS[i]);
    gpio_set_dir(OFFSET_LED_PINS[i], GPIO_OUT);
		gpio_put(OFFSET_LED_PINS[i], 0);
  }

  /* Initialize servo */
  servo_Init(SERVO_PIN);
  servo_On(&mainServo);

  /* Initialize potentiometer positions */
  angle = map(analog_Read(SERVO_ANALOG), 0, 4095, MAXIMUM_ANGLE, MINIMUM_ANGLE);
  seconds = map(analog_Read(TIME_ANALOG), 0, 4095, 60, 0);

  /* Initialize offset thread */
	multicore_launch_core1(offset_Select);

  /* Entire program loop */
  while(1) {

  	/* Main keyclicker loop */
  	while (!timeToggle && !angleToggle) {
			click();
			int offsetAmount = calc_Offset(offsetLevel, seconds);
			float secondsShift = seconds;
			switch (offsetLevel) {
				case 0: break;
				case 1: secondsShift *= 0.90f; break;
				case 2: secondsShift *= 0.75f; break;
				case 3: secondsShift *= 0.50f; break;
			}
    	now = to_ms_since_boot(get_absolute_time());
    	timer = (now + (secondsShift * 1000.0f) + offsetAmount);
    	while (to_ms_since_boot(get_absolute_time()) < timer) {
				countdown = timer - to_ms_since_boot(get_absolute_time());
				set_Countdown(countdown, digits);
				update_Display(digits, TENTHS);
				if (time_Button() || angle_Button())
					break;
  		}
		}
  	sleep_ms(200);

  	/* Time delay select loop */
  	while (timeToggle) {
			seconds = set_Seconds(seconds, digits);
			update_Display(digits, NONE);
			time_Button();
			if (!timeToggle)
				sleep_ms(200);
  	}
			
  	/* Servo arm angle select loop */
  	while (angleToggle) {
			angle = set_Angle(angle, digits);
			update_Display(digits, NONE);
			angle_Button();
			if (!angleToggle)
				sleep_ms(200);
  	}
	}
}
