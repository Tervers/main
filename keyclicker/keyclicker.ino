#include <Servo.h>
#include <time.h>
#include <stdlib.h>

#define SERVO_PIN 22
#define SERVO_ANALOG 26
#define TIME_ANALOG 28
#define ANGLE_SELECT_PIN 13
#define TIME_SELECT_PIN 19

#define USER_MINIMUM_ANGLE  75
#define USER_MAXIMUM_ANGLE 155

#define DATA_PIN 18
#define LATCH_PIN 20
#define CLOCK_PIN 21
const int COM_PIN[] = {17, 16, 15, 14};

Servo mainServo;

int pos = 0;
int setAngle = USER_MINIMUM_ANGLE;

int seconds = 0;
int offset = 0;

int digit;
int digits[4];

bool startToggle = false;
bool timeToggle = false;
bool angleToggle = false;
         
byte num[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,    // characters 0-7
              0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};    // characters 8-9, A-F

void setup() {
  mainServo.attach(SERVO_PIN, 500, 2500);
  pinMode(ANGLE_SELECT_PIN, INPUT_PULLUP);
  pinMode(TIME_SELECT_PIN, INPUT_PULLUP);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(COM_PIN[i], OUTPUT);
  }

  setAngle = map(((analogRead(SERVO_ANALOG) / 10) * 10), 0, 1023, USER_MINIMUM_ANGLE, USER_MAXIMUM_ANGLE);
  digits[1] = ((setAngle % 1000) / 100);
  digits[2] = ((setAngle % 100) / 10);
  digits[3] = (setAngle % 10);
  for (int i = 1; i < 4; i++) {
    electDigitalDisplay(i);
    digit = digits[i];
    writeData(num[digit]);
    delay(5);
    writeData(0xff);      
  }
}

void loop() {
  if (digitalRead(ANGLE_SELECT_PIN) == LOW) {
    delay(20);
    if (digitalRead(ANGLE_SELECT_PIN) == LOW) {
      angleToggle = true;
    }
  }
  if (digitalRead(TIME_SELECT_PIN) == LOW) {
    delay(20);
    if (digitalRead(TIME_SELECT_PIN) == LOW) {
      timeToggle = true;
    }
  }
  if (!timeToggle && !angleToggle)
    startToggle = true;  

  while (startToggle) {
    for (pos = setAngle; pos < setAngle + 7; pos += 1) {
      mainServo.write(pos);
      delay(20);
    }
    for (pos = setAngle; pos > setAngle - 7; pos -= 1) {
      mainServo.write(pos);
      delay(20);
    }
    delay(seconds * 1000);
    srand((unsigned) time(NULL));
    delay(offset = (rand() % 2000));
    if (digitalRead(TIME_SELECT_PIN) == LOW)
      timeToggle = true;
    if (digitalRead(ANGLE_SELECT_PIN) == LOW)
      angleToggle = true;
  }

  while (timeToggle) {
    seconds = map(analogRead(TIME_ANALOG), 0, 1023, 0, 60);
    digits[1] = ((seconds % 1000) / 100);
    digits[2] = ((seconds % 100) / 10);
    digits[3] = (seconds % 10);
    for (int i = 1; i < 4; i++) {
      electDigitalDisplay(i);
      digit = digits[i];
      writeData(num[digit]);
      delay(5);
      writeData(0xff);      
    }
    if (digitalRead(TIME_SELECT_PIN) == LOW) {
        timeToggle = false;
      }
  }

  while (angleToggle) {
    setAngle = map(((analogRead(SERVO_ANALOG) / 10) * 10), 0, 1023, USER_MINIMUM_ANGLE, USER_MAXIMUM_ANGLE);
    mainServo.write(setAngle);
    digits[1] = ((setAngle % 1000) / 100);
    digits[2] = ((setAngle % 100) / 10);
    digits[3] = (setAngle % 10);
    for (int i = 1; i < 4; i++) {
      electDigitalDisplay(i);
      digit = digits[i];
      writeData(num[digit]);
      delay(5);
      writeData(0xff);      
    }
    if (digitalRead(ANGLE_SELECT_PIN) == LOW) {
        angleToggle = false;
    }
  }
}

void electDigitalDisplay(byte com) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(COM_PIN[i], HIGH);
  }
  digitalWrite(COM_PIN[com], LOW);
}

void writeData(int value) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, value);
  digitalWrite(LATCH_PIN, HIGH);
}
