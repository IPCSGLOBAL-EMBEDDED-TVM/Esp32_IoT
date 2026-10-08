#include <WiFi.h>

const char* ssid = "IPCS,3FLOOR";
const char* password = "Ipcs@2026";

WiFiServer server(80);

int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client Connected");

    String request = client.readString();   // ✅ Read full request
    Serial.println(request);

    // LED ON
    if (request.indexOf("GET /LEDON") != -1) {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED ON");
    }

    // LED OFF
    if (request.indexOf("GET /LEDOFF") != -1) {
      digitalWrite(ledPin, LOW);
      Serial.println("LED OFF");
    }

    // Send proper response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/plain");
    client.println("Connection: close");
    client.println();
    client.println("OK");

    delay(1);
    client.stop();
    Serial.println("Client Disconnected");
  }
}
