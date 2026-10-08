 #include "BluetoothSerial.h"

BluetoothSerial SerialBT;

int ledPin = 2;
char incoming;

void setup() 
{
  Serial.begin(115200);
  SerialBT.begin("ESP32_LED");   // Bluetooth device name

  pinMode(ledPin, OUTPUT);
}

void loop() 
{
  if (SerialBT.available())
  {
    incoming = SerialBT.read();

    if (incoming == '1')
    {
      digitalWrite(ledPin, HIGH);
      SerialBT.println("LED ON");
    }

    if (incoming == '0')
    {
      digitalWrite(ledPin, LOW);
      SerialBT.println("LED OFF");
    }
  }
}
