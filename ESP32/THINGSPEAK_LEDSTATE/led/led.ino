#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

int LED = 2;
int ReadState = 0;

WiFiClient client;

unsigned long channelID = 3400114;
const char* writeAPIKey = "Z1258U03QGLCOPHQ";

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi Connected!");
  ThingSpeak.begin(client);
}

void loop() {
  // LED ON
  digitalWrite(LED, HIGH);
  ReadState = 1;
  ThingSpeak.setField(1, ReadState);
  int status = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (status == 200) {
    Serial.println("LED ON data sent successfully");
  } else {
    Serial.print("Error sending data: ");
    Serial.println(status);
  }

  delay(15000);

  // LED OFF
  digitalWrite(LED, LOW);
  ReadState = 0;
  ThingSpeak.setField(1, ReadState);
  status = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (status == 200) {
    Serial.println("LED OFF data sent successfully");
  } else {
    Serial.print("Error sending data: ");
    Serial.println(status);
  }

  delay(15000);
}