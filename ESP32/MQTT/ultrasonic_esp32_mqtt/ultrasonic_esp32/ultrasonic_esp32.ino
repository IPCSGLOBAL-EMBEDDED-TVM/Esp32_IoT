#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// -------- WIFI ----------
const char* ssid = "Redmi 13C 5G";
const char* password = "12345678";

// -------- MQTT ----------
const char* mqtt_server = "802c8668d4e941f88bf180b2426f8fb3.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

const char* mqtt_user = "hivemq.webclient.1788864487158";
const char* mqtt_pass = "*.H5w1$hQdD3Ip7VmJq<";

const int trigPin = 4;
const int echoPin = 5;

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
