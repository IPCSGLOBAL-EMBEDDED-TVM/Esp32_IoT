#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

const char* mqtt_server = "ec7bb4e92a2f4420af23e5614428f523";
const int mqtt_port = 8883;

const char* mqtt_user = "hivemq.webclient.1787299870575";
const char* mqtt_pass = "JMgw$%U4c@Z&E91p6gBvQghp6hPfYELn";

#define LED_PIN 2


WiFiClientSecure espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {

  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println("Received: " + message);

  if (message == "1") {
    digitalWrite(LED_PIN, LOW);   // ON
  }
  else if (message == "0") {
    digitalWrite(LED_PIN, HIGH);  // OFF
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


