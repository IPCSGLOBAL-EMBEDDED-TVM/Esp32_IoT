#include <WiFi.h>
#include <ThingSpeak.h>

// WiFi Credentials
const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

// ThingSpeak
unsigned long channelID = 3313075;
const char* writeAPIKey = "PAMEBXDW6JLB67RL";

WiFiClient client;

// Ultrasonic Pins
#define TRIG 5
#define ECHO 18

long duration;
float distance;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {

  // Trigger Ultrasonic
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Read Echo
  duration = pulseIn(ECHO, HIGH);

  // Calculate Distance (cm)
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Send to ThingSpeak
  ThingSpeak.setField(1, distance);

  int status = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (status == 200) {
    Serial.println("Data sent successfully ✅");
  } else {
    Serial.print("Error Code: ");
    Serial.println(status);
  }

  delay(15000); // Required delay
}
