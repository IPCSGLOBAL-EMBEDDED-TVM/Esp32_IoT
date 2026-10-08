#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// -------- WIFI ----------
const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

// -------- MQTT ----------
const char* mqtt_server = "b429458c4a3447f5a3388bb0e7916ab3.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

const char* mqtt_user = "hivemq.webclient.1772016068408";
const char* mqtt_pass = "R6KChwLX?5tB;*g.s81j";

const int mq2Pin = D4;

// -------- MQTT OBJECTS ----------
WiFiClientSecure espClient;
PubSubClient client(espClient);

// ---------- CALLBACK (Optional if you want subscribe) ----------
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// ---------- RECONNECT ----------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");

    if (client.connect("ESP32_Client", mqtt_user, mqtt_pass)) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 2 sec");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(mq2Pin, INPUT);

  // WiFi Connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");

  espClient.setInsecure();  // For learning/testing only

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  // ---------- Read MQ-2 Sensor ----------
  int mq2Value = analogRead(mq2Pin); // raw analog value (0-4095)

  // Optional: Convert to percentage (0-100%)
  float mq2Percent = (mq2Value / 4095.0) * 100.0;

  // ----------- Create JSON -----------
  String payload = "{";
  payload += "\"MQ2_VALUE\":" + String(mq2Value) + ",";
  payload += "\"MQ2_PERCENT\":" + String(mq2Percent,1) + ",";
  payload += "}";

  // ----------- Publish -----------
  client.publish("esp32/mq2/data", payload.c_str());

  Serial.println("Published:");
  Serial.println(payload);

  delay(2000);  // Send every 2 seconds
}