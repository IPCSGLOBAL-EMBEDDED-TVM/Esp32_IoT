int segment[7]={D0,D1,D2,D5,D6,D7,D8},digits[10] = {0X90,0X80,0XF8,0X82,0X92,0X99,0XB0,0xA4,0xF9,0xC0},ledlight[3]={1,3,D4};      
void setup() {
  led();
  segmentdigits();
}

void loop(){
  digitalWrite(1,HIGH);
  sevendisplay();
  digitalWrite(1,LOW);
  digitalWrite(3,HIGH);
  yellowdisplay();
  digitalWrite(3,LOW);
  digitalWrite(D4,HIGH);
  sevendisplay();
  digitalWrite(D4,LOW);
}

void led(){
  for(int d=0;d<3;d++){
    pinMode(ledlight[d],OUTPUT);
  }
}

void segmentdigits(){
  for(int k=0;k<7;k++){
    pinMode(segment[k],OUTPUT);
  }
}

void sevendisplay(){
  for(int i=0;i<10;i++){
  for(int j=0;j<7;j++){
    digitalWrite(segment[j],(digits[i]>>j)&1);
  }
  delay(1000);
 }
}

void yellowdisplay(){
  for(int i=4;i<10;i++){
  for(int j=0;j<7;j++){
    digitalWrite(segment[j],(digits[i]>>j)&1);
  }
  delay(1000);
 }
}

