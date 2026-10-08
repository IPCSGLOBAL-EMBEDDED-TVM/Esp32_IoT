#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

const char* mqtt_server = "b9883a04065542bf81c138d04de0bbdf.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

const char* mqtt_user = "hivemq.webclient.1772003810651";
const char* mqtt_pass = "5w4ZUCB7.yN*o!ahM>0z";

#define LED_PIN D4


WiFiClientSecure espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {

  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println("Received: " + message);

  if (message == "ON") {
    digitalWrite(LED_PIN, LOW);   // Active LOW
    
  }
  else if (message == "OFF") {
    digitalWrite(LED_PIN, HIGH);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266_Adam", mqtt_user, mqtt_pass)) {
      client.subscribe("adam/device1/led");
      Serial.println("Subscribed");
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  espClient.setInsecure();  // Learning purpose

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}
