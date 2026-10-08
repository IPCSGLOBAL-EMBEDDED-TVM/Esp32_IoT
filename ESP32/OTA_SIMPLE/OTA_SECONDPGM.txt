#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

#define LED 2

void setup() { 

  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  ArduinoOTA.begin();
}

void loop() {

  ArduinoOTA.handle();

  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);

}