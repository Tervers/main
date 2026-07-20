/* INCLUDES */
#include <Servo.h>
#include <time.h>
#include <stdlib.h>

/* DEFINES */
#define SERVO_PIN 22
#define PIN_ADC0  26

/* OBJECTS */
Servo mainServo;  // create servo object to control a servo

/* SERVO VARIABLES */
int pos = 0;         // variable to store the servo position
int minAngle = 10;   // minimum angle servo can lower to
int offset = 0;      // added time to randomize keyclicks

/* 4-DIGIT 7-SEGMENT DISPLAY VARIABLES */
int dataPin = 18;   
int latchPin = 20;
int clockPin = 21;          
int comPin[] = {17, 16, 15, 14};// Common pin (anode) of 4 digit 7-segment display

byte num[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8,    // characters 0-F
              0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e};

/* VARIABILITY VARIABLES */
int v;            // variability level
bool counter[v];  

/* INITIALIZATION */
void setup() {
  mainServo.attach(SERVO_PIN, 500, 2500);  // attaches the servo on pin 9 to the servo object
}

/* MAIN */
void loop() {
    //led and angle controls


  for (pos = minAngle; pos < 170; pos += 160) { // goes from 10* degrees to 170 degrees
    mainServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1750);                       // waits 500 ms for the servo to reach the position
  }
  for (pos = 170; pos > minAngle; pos -= 160) { // goes from 170 degrees to 10* degrees
    mainServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(250);                       // waits 11 ms for the servo to reach the position
  }
  srand((unsigned) time(NULL));
  delay((rand() % 1000));
}
