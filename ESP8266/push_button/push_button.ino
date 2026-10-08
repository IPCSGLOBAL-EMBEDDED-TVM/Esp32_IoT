#define BUTTON_PIN D2      // GPIO4
#define LED_PIN LED_BUILTIN

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // internal pull-up
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  // Button pressed = LOW (because of pull-up)
  if (buttonState == LOW) {
    digitalWrite(LED_PIN, LOW);   // LED ON (active LOW)
    Serial.println("Button Pressed");
  } else {
    digitalWrite(LED_PIN, HIGH);  // LED OFF
    Serial.println("Button Released");
  }

  delay(200);  // small delay to avoid noise
}