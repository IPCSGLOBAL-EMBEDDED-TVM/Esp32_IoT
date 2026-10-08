#include <ESP8266WiFi.h>
#include <espnow.h>

// Structure must be exactly the same as the sender
typedef struct struct_message {
  char name[20];
} struct_message;

struct_message myData;

// Callback function
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));

  Serial.print("Received Name: ");
  Serial.println(myData.name);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set device role
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

  // Register receive callback
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing needed here
}