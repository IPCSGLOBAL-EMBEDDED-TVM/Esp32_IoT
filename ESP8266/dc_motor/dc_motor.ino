#define IN1 2  //D1
#define IN2 5      //D2
//#define ENA 14    //D5  //pwm
void setup() {
  // put your setup code here, to run once:
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
   // pinMode(ENA,OUTPUT);

}

void loop() {
  // fwd
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      //analogWrite(ENA,700);  //0-1023
      delay(1000);

      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      delay(1000);

      //REVERSE

      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      //analogWrite(ENA, 700);
      delay(1000);

      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      delay(1000);
}
