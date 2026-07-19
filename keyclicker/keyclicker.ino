#include <Servo.h>
#include <time.h>
#include <stdlib.h>

#define SERVO_PIN 16
#define PIN_ADC0  26
#define ANGLE_L1  13    //led1 representing minAngle
#define ANGLE_L2  14
#define ANGLE_L3  15`    //GPIO subject to change

Servo mainServo;  // create servo object to control a servo

int pos = 0;         // variable to store the servo position
int minAngle = 10;   // minimum angle servo can lower to
int offset = 0;      // added time to randomize keyclicks

bool counter[3] = {0, 0, 0};

void setup() {
  mainServo.attach(SERVO_PIN, 500, 2500);  // attaches the servo on pin 9 to the servo object
}

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
