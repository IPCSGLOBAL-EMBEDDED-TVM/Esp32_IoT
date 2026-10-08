#include <WiFi.h>

const char* ssid = "ESP32_WIFI";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  Serial.println("WiFi Access Point Started");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Nothing to do
}