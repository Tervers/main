#include <threads.h>
#include <stdlib.h>

#define ANGLE_SELECT_PIN 13

void setup() {
  pinMode(ANGLE_SELECT_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  delay(2000);
  Serial.println("Raspberry Pi Pico initialization completed!");
}

void loop() {
  Serial.println("")

}
