#ifndef ANGLE_H
#define ANGLE_H


/*** Includes ***/

#include "calculations.h"
#include "display.h"
#include "gpioF.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include <stdint.h>
#include <stdbool.h>


/*** Variables ***/

#define MINIMUM_ANGLE 10
#define MAXIMUM_ANGLE 170

extern bool angleToggle;

extern int pos;
extern int angle;

extern const int SERVO_PIN;
extern const int SERVO_ANALOG;
extern const int SERVO_SELECT_PIN;
extern const int ANGLE_SELECT_PIN;

typedef struct {
  uint gpio;
  uint slice;
  uint chan;
  uint speed;
  uint resolution;
  bool on;
  bool invert;
} Servo;
extern Servo mainServo;


/*** Function Prototypes ***/

bool angle_Button(void);
void click(void);
uint32_t pwm_Get_Wrap(uint slice_num);
void pwm_Set_Duty_H(uint slice_num, uint chan, int d);
uint32_t pwm_Set_Freq_Duty(uint slice_num,uint chan, uint32_t f, int d);
int set_Angle(int angle, int digits[]);
void servo_Init(uint gpio);
void servo_Off(Servo *s);
void servo_On(Servo *s);
void servo_Position(uint gpio, int angle);


#endif
