#include <stdlib.h>

#define ANGLE_SELECT_PIN 13

int lastButtonState = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(ANGLE_SELECT_PIN, INPUT);
  Serial.begin(9600);
  delay(2000);
  Serial.println("Raspberry Pi Pico initialization completed!");
}

void loop() {
  int reading = digitalRead(ANGLE_SELECT_PIN);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      Serial.print("Button state changed to: ");
      Serial.println(buttonState);
    }
  }
  
  lastButtonState = reading;
  delay(10);
}



/*
#include <stdlib.h>

#define ANGLE_SELECT_PIN 12

void setup() {
  pinMode(ANGLE_SELECT_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  delay(2000);
  Serial.println("Raspberry Pi Pico initialization completed!");
}

void loop() {
  for (int i = 1;;i++) {
    Serial.println(i);
    Serial.println("digitalRead: ");
    Serial.println(digitalRead(ANGLE_SELECT_PIN));
    delay(500);
  }
}
*/