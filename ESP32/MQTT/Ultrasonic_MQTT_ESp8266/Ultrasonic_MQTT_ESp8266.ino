#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// -------- WIFI ----------
const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

// -------- MQTT ----------
const char* mqtt_server = "b429458c4a3447f5a3388bb0e7916ab3.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

const char* mqtt_user = "hivemq.webclient.1772017675106";
const char* mqtt_pass = "4.R$w@;92giuB5IQAJlh";

const int trigPin = D4;
const int echoPin = D5;

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

// ---------- Read distance ----------
long readDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);  // measure pulse length
  long distance = duration * 0.034 / 2;    // convert to cm
  return distance;
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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

   long distance = readDistanceCM();   // read sensor

  

  // ----------- Create JSON -----------
  String payload = "{";
  payload += "\"DISTANCE\":" + String(distance) ;
 
  payload += "}";

  // ----------- Publish -----------
  client.publish("esp32/ultrasonic/data", payload.c_str());

  Serial.println("Published:");
  Serial.println(payload);

  delay(2000);  // Send every 2 seconds
}
