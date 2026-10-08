#define LED1 1  
#define LED2 3

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT); // Set LED pin as output
   pinMode(LED2, OUTPUT); // Set LED pin as output
}

void loop() {
  digitalWrite(LED1, HIGH);  // Turn LED ON
  digitalWrite(LED2, HIGH); // Turn LED OFF
 
  Serial.println("LED IS ON");                   // Wait 1 second
 delay(1000);  
  digitalWrite(LED1, LOW);  // Turn LED ON
 
  digitalWrite(LED2, LOW);  // Turn LED ON
  delay(1000);            
              
}
