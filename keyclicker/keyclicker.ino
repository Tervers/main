#include <Servo.h>
#include <time.h>
#include <stdlib.h>

#define SERVO_PIN 22
#define ANALOG_PIN 26
#define ANGLE_SELECT_PIN 13
#define TIME_SELECT_PIN 12
//#define START_PIN 11

#define USER_MINIMUM_ANGLE  75
#define USER_MAXIMUM_ANGLE 126

#define dataPin 18
#define latchPin 20
#define clockPin 21
int comPin[] = {17, 16, 15, 14};

Servo mainServo;

int pos = 0;
int setAngle = USER_MINIMUM_ANGLE;
int checkAngle = 0;
int currentAngle = 0;
int currentAnalog = 0;

int seconds = 0;

int digit;
int digits[4];

bool startToggle = false;
bool timeToggle = false;
bool angleToggle = true;

int offset = 0;
         
byte num[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,    // characters 0-7
              0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};    // characters 8-9, A-F

void setup() {
  mainServo.attach(SERVO_PIN, 500, 2500);
  pinMode(ANGLE_SELECT_PIN, INPUT);
  pinMode(TIME_SELECT_PIN, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(comPin[i], OUTPUT);
  }
  Serial.begin(9600);
  delay(2000);
  Serial.println("Raspberry Pi Pico initialization completed!");
}

void loop() {
  while (timeToggle) {
    angleToggle = false;
    seconds = map(analogRead(ANALOG_PIN), 0, 1023, 0, 900);
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
    if (digitalRead(TIME_SELECT_PIN) == LOW)
      timeToggle = false;
  }

  while (angleToggle) {
    timeToggle = false;
    Serial.println("currentAnalog: ");
    Serial.println(currentAnalog = ((analogRead(ANALOG_PIN) / 10) * 10));
    setAngle = map(((analogRead(ANALOG_PIN) / 10) * 10), 0, 1023, USER_MINIMUM_ANGLE, USER_MAXIMUM_ANGLE);
    Serial.println("setAngle");
    Serial.println(setAngle);
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
    if (digitalRead(ANGLE_SELECT_PIN) == LOW)
      angleToggle = false;
  }

  checkAngle = setAngle;

  while (!timeToggle && !angleToggle) {
    for (pos = setAngle; pos < setAngle + 7 && pos < USER_MAXIMUM_ANGLE; pos += 1) {
      mainServo.write(pos);
      delay(20);
    }
    for (pos = setAngle; pos > setAngle - 7 && pos > USER_MINIMUM_ANGLE; pos -= 1) {
      mainServo.write(pos);
      delay(20);
    }
    delay(seconds);
    srand((unsigned) time(NULL));
    delay(offset = (rand() % 2000));
    setAngle = map(((analogRead(ANALOG_PIN) / 10) * 10), 0, 1023, USER_MINIMUM_ANGLE, USER_MAXIMUM_ANGLE);
    if (setAngle != checkAngle)
      angleToggle = true;
  }
}

void electDigitalDisplay(byte com) {
  // Close all single 7-segment display
  for (int i = 0; i < 4; i++) {
    digitalWrite(comPin[i], HIGH);
  }
  // Open the selected single 7-segment display
  digitalWrite(comPin[com], LOW);
}

void writeData(int value) {
  // Make latchPin output low level
  digitalWrite(latchPin, LOW);
  // Send serial data to 74HC595
  shiftOut(dataPin, clockPin, LSBFIRST, value);  // Make latchPin output high level
// Make latchPin output high level, then 74HC595 will update data to parallel output
  digitalWrite(latchPin, HIGH);
}
