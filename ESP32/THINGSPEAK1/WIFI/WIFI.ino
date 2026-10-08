#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

WiFiClient client;

unsigned long channelID =  3313057;   // Your Channel ID
const char* writeAPIKey = "E2FUEIWSAOTEZXQM";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  ThingSpeak.begin(client);
}

void loop() {
  float temperature = 35;

  ThingSpeak.setField(1, temperature);
  ThingSpeak.writeFields(channelID, writeAPIKey);

  delay(15000); // ThingSpeak needs 15 sec gap
}