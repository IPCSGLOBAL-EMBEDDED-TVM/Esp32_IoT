#include <Servo.h>

Servo myServo;

#define SERVO_PIN 4   // GPIO2

void setup() {
  myServo.attach(SERVO_PIN);
}

void loop() {
  // 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    delay(15);
  }

  // 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(15);
  }
}
