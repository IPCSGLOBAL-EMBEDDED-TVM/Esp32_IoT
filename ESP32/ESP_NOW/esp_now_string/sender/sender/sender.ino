#include <WiFi.h>
#include <esp_now.h>

// Receiver MAC Address
uint8_t receiverMac[] = {0x84, 0xF3, 0xEB, 0x0A, 0xA0, 0x9A};

// Structure to send data
typedef struct struct_message {
  char name[20];
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Copy your name into the structure
  strcpy(myData.name, "Ruben");

  // Send data
  esp_now_send(receiverMac, (uint8_t *)&myData, sizeof(myData));

  Serial.print("Sent: ");
  Serial.println(myData.name);

  delay(2000);
}