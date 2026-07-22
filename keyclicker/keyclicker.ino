// make function that reads ANGLE_SELECT_PIN value into a variable to be checked by while()
#include <Servo.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define SERVO_PIN     22
#define ANALOG_PIN 26
#define ANGLE_SELECT_PIN 13

#define MINIMUM_ANGLE  75
#define MAXIMUM_ANGLE 165

Servo mainServo;  // create servo object to control a servo

int pos = 0;         // variable to store the servo position
int topAngle = MINIMUM_ANGLE;   // angle servo will lower to
int setAngle = 0;
int digit;
int digits[4];
bool angleToggle = false;

int offset = 0;      // added time to randomize keyclicks

int dataPin = 18;   
int latchPin = 20;
int clockPin = 21;          
int comPin[] = {17, 16, 15, 14};// Common pin (CATHODE*) of 4 digit 7-segment display

byte num[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,    // characters 0-7
              0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};    // characters 8-9, A-F

bool counter[3];    // VLAs not accepted?

void setup() {
  mainServo.attach(SERVO_PIN, 500, 2500);
  pinMode(ANGLE_SELECT_PIN, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(comPin[i], OUTPUT);
  }
}

void loop() {
  while(!angleToggle) {
    topAngle = map((analogRead(ANALOG_PIN)), 0, 1023, MINIMUM_ANGLE, MAXIMUM_ANGLE);
    digits[1] = ((topAngle % 1000) / 100);
    digits[2] = ((topAngle % 100) / 10);
    digits[3] = (topAngle % 10);
    for (int i = 1; i < 4; i++) {
      electDigitalDisplay(i);
      digit = digits[i];
      writeData(num[digit]);
      delay(5);
      writeData(0xff);
      //if(digitalRead(ANGLE_SELECT_PIN) == HIGH)
        //i = 1;
    }
  }

  setAngle = topAngle;

  while(1) {
    if(setAngle != map((analogRead(ANALOG_PIN)), 0, 1023, MINIMUM_ANGLE, MAXIMUM_ANGLE))
      break;
    for (pos = topAngle; pos < topAngle + 7 && pos < MAXIMUM_ANGLE; pos += 1) { // goes from 10* degrees to 170 degrees
      mainServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(20);                       // waits 500 ms for the servo to reach the position
    }
    for (pos = topAngle; pos > topAngle - 7 && pos > MINIMUM_ANGLE; pos -= 1) { // goes from 170 degrees to 10* degrees
      mainServo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(20);                       // waits 11 ms for the servo to reach the position
    }
//  delay(2050);
//  srand((unsigned) time(NULL));
//  delay((rand() % 1500));
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
