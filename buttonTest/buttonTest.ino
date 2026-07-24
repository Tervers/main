#define TIME_SELECT_PIN 19
#define ANGLE_SELECT_PIN 13

void setup() {
  pinMode(TIME_SELECT_PIN, INPUT_PULLUP);
  pinMode(ANGLE_SELECT_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  delay(2000);
  Serial.println("Starting button test...");
}

void loop() {
  int angleReading = digitalRead(ANGLE_SELECT_PIN);
  int timeReading = digitalRead(TIME_SELECT_PIN);
  
  // Also read the raw ADC values for comparison
  int timeRaw = analogRead(TIME_SELECT_PIN);
  int angleRaw = analogRead(ANGLE_SELECT_PIN);
  
  Serial.print("Angle: ");
  Serial.print(angleReading);
  Serial.print(" (raw: ");
  Serial.print(angleRaw);
  Serial.print(") | Time: ");
  Serial.print(timeReading);
  Serial.print(" (raw: ");
  Serial.print(timeRaw);
  Serial.println(")");
  
  delay(200);
}
