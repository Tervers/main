#ifndef ANGLE_H
#define ANGLE_H

#include "pico/stdlib.h"
#include <stdbool.h>

/* Servo arm angle restrictions */
#define MINIMUM_ANGLE 10
#define MAXIMUM_ANGLE 170

/* Servo control values */
extern bool angleToggle;

extern int pos;
extern int angle;

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

void servo_Init(uint gpio);
void servo_On(Servo *s);
void servo_Off(Servo *s);
void servo_Position(uint gpio, int angle);
void click(void);
void pwm_Set_Duty_H(uint slice_num, uint chan, int d);
uint32_t pwm_Get_Wrap(uint slice_num);
uint32_t pwm_Set_Freq_Duty(uint slice_num,uint chan, uint32_t f, int d);
bool angle_Button(void);
int set_Angle(int angle, int digits[]);

#endif
