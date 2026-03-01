#include <WiFi.h>
#include <ThingSpeak.h>

#define PIR_PIN 27
#define LED_PIN 26

#include "secrets.h"

WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT_PULLDOWN);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  ThingSpeak.writeField(CHANNEL_ID, 1, motion, WRITE_API_KEY);

  Serial.println("PIR Stabilizing...");
  delay(30000);  // 30 sec warm-up
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Intrusion Detected!");
    ThingSpeak.writeField(channelID, 1, 1, writeAPIKey);
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Area Secure");
    ThingSpeak.writeField(channelID, 1, 0, writeAPIKey);
  }

  delay(15000);  // ThingSpeak minimum update interval

int response = ThingSpeak.writeField(channelID, 1, motion, writeAPIKey);

if(response == 200){
  Serial.println("Data sent to ThingSpeak successfully!");
} else {
  Serial.print("Error sending data. Code: ");
  Serial.println(response);
}
}