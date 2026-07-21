// INCLUDES
#include <Servo.h>
#include <time.h>
#include <stdlib.h>

// DEFINES
#define SERVO_PIN     22
#define PIN_ADC0      26
#define PIN_ANALOG_IN 26

#define MINIMUM_ANGLE  75
#define MAXIMUM_ANGLE 165

// OBJECTS
Servo mainServo;  // create servo object to control a servo

// SERVO VARIABLES
int pos = 0;         // variable to store the servo position
int topAngle = 50;   // angle servo will lower to
int offset = 0;      // added time to randomize keyclicks

// 4-DIGIT 7-SEGMENT DISPLAY VARIABLES
int dataPin = 18;   
int latchPin = 20;
int clockPin = 21;          
int comPin[] = {17, 16, 15, 14};// Common pin (anode) of 4 digit 7-segment display

byte num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,    // characters 0-F
              0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

// VARIABILITY VARIABLES
int v;            // variability level
bool counter[3];    // VLAs not accepted?

// INITIALIZATION
void setup() {
  mainServo.attach(SERVO_PIN, 500, 2500);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(comPin[i], OUTPUT);
  }
}

// MAIN
void loop() {

  // 4-DIGIT 7-SEGMENT DISPLAY
  for (int i = 0; i < 4; i++) {
      // Select a single 7-segment display
      electDigitalDisplay (i);
      // Send data to 74HC595
      writeData(num[i]);
      delay(5);
      // Clear the display content
      writeData(0xff);
    }





  topAngle = map((analogRead(PIN_ANALOG_IN)), 0, 1023, MINIMUM_ANGLE, MAXIMUM_ANGLE);

/* SERVO */
  for (pos = topAngle; pos < topAngle + 7 && pos < MAXIMUM_ANGLE; pos += 1) { // goes from 10* degrees to 170 degrees
    mainServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 500 ms for the servo to reach the position
  }
  for (pos = topAngle; pos > topAngle - 7 && pos > MINIMUM_ANGLE; pos -= 1) { // goes from 170 degrees to 10* degrees
    mainServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 11 ms for the servo to reach the position
  }
  delay(2050);
  srand((unsigned) time(NULL));
  delay((rand() % 1500));
}

  void electDigitalDisplay(byte com) {
    // Close all single 7-segment display
    for (int i = 0; i < 4; i++) {
      digitalWrite(comPin[i], LOW);
    }
    // Open the selected single 7-segment display
    digitalWrite(comPin[com], HIGH);
  }

  void writeData(int value) {
    // Make latchPin output low level
    digitalWrite(latchPin, LOW);
    // Send serial data to 74HC595
    shiftOut(dataPin, clockPin, LSBFIRST, value);  // Make latchPin output high level
  // Make latchPin output high level, then 74HC595 will update data to parallel output
    digitalWrite(latchPin, HIGH);
  }
