#define PIR_PIN 27
#define LED_PIN 26

void setup() {
  pinMode(PIR_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  Serial.println("System Stabilizing...");
  delay(30000);   // 30 sec warm-up
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Intrusion Detected!");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Area Secure.");
  }

  delay(1000);
}