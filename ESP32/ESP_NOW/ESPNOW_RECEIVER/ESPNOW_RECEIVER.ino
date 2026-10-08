#include <ESP8266WiFi.h>
#include <espnow.h>


typedef struct struct_message {
  int value;
} struct_message;

struct_message myData;


void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));

  Serial.print("Received: ");
  Serial.println(myData.value);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set device role
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

  // Register callback
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing needed here
}
