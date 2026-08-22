/*** Includes ***/

#include "angle.h"


/*** Variables ***/

Servo mainServo;

int pos = 0;
int angle = 0;

bool angleToggle = false;


/*** Function Definitions ***/

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

void click(void) {
  for (int i = 0, pos = angle; pos < angle + 6; pos += 1, i++) {
    servo_Position(SERVO_PIN, pos);
    for (int j = 0; j < 4; j++) {
      select_Digit(sections[i].digit);
      write_Data(sections[i].shape);
      sleep_ms(5);
    }
  }
  for (int i = 6, pos = angle; pos > angle - 6; pos -= 1, i++) {
    servo_Position(SERVO_PIN, pos);
    for (int j = 0; j < 4; j++) {
      select_Digit(sections[i].digit);
      write_Data(sections[i].shape);
      sleep_ms(5);
    }
  }
}

bool angle_Button(void) {
        if (!gpio_get(ANGLE_SELECT_PIN)) {
          sleep_ms(20);
          if (!gpio_get(ANGLE_SELECT_PIN)) {
            angleToggle = !angleToggle;
            return true;
          }
        }
          else
            return false;
}

int set_Angle(int angle, int digits[]) {
      angle = map(analog_Read(SERVO_ANALOG), 0, 4095, MAXIMUM_ANGLE, MINIMUM_ANGLE);
      servo_Position(SERVO_PIN, angle);
      digits[1] = ((angle % 1000) / 100);
      digits[2] = ((angle % 100) / 10);
      digits[3] = (angle % 10);
      return angle;
}
