#include <LiquidCrystal.h>

// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(1, 2, 5, 6, 7, 8);

void setup() {
  lcd.begin(16, 2);   // 16 columns, 2 rows

  lcd.setCursor(0, 0);
  lcd.print("Hello ESP8266");

  lcd.setCursor(0, 1);
  lcd.print("LCD Working");
}

void loop() {
  // nothing here
}
