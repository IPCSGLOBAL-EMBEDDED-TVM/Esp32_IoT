#define LED 4  // GPIO2 (D4 in NodeMCU)

void setup() {
  pinMode(LED, OUTPUT); // Set LED pin as output
}

void loop() {
  digitalWrite(LED, LOW);  // Turn LED ON
  delay(1000);                     // Wait 1 second
  
  digitalWrite(LED, HIGH); // Turn LED OFF
  delay(1000);                     // Wait 1 second
}
