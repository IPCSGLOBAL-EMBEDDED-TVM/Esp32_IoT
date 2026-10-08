#include <WiFi.h>
#include <esp_now.h>

// Receiver MAC Address (change this)
uint8_t receiverMac[] = {0x68, 0xC6, 0x3A, 0xDF, 0x89, 0x0E};//68:C6:3A:DF:89:0E

// Structure to send data
typedef struct struct_message {
  int value;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA); // Must be in station mode

  // Init ESP-NOW
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
  myData.value = random(0, 100);

  esp_now_send(receiverMac, (uint8_t *)&myData, sizeof(myData));

  Serial.print("Sent: ");
  Serial.println(myData.value);

  delay(2000);
}
