#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("WiFi Scanner Started");
}

void loop() {
  Serial.println("\nScanning...");

  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("No networks found");
  } else {
    Serial.printf("%d networks found\n\n", n);

    for (int i = 0; i < n; i++) {
      Serial.printf("%d: %s", i + 1, WiFi.SSID(i).c_str());
      Serial.printf(" | RSSI: %d dBm", WiFi.RSSI(i));
      Serial.printf(" | Channel: %d", WiFi.channel(i));
      Serial.printf(" | Encryption: %s\n",
                    (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ?
                    "Open" : "Secured");
    }
  }

  Serial.println("\n-------------------");
  delay(10000); // Scan every 10 seconds
}
