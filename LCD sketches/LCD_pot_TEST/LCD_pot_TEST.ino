#include <LiquidCrystal.h>

const int rs = 34, en = 32, d4 = 30, d5 = 28, d6 = 26, d7 = 24;
int k1Pin = A8;
int k2Pin = A9;
int k3Pin = A10;
int k1, k2;
float k3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(k1Pin, INPUT);
  pinMode(k2Pin, INPUT);
  pinMode(k3Pin, INPUT);
}

void loop() {
  lcd.clear();
  k1 = map(analogRead(k1Pin), 0, 1023, 0, 20);
  k2 = map(analogRead(k2Pin), 0, 1023, 0, 20);
  k3 = (float)map(analogRead(k3Pin), 0, 1023, 0, 11)/10;
  lcd.setCursor(2, 0);
  lcd.print("K1:");
  lcd.print(k1);
  lcd.setCursor(9, 0);
  lcd.print("K2:");
  lcd.print(k2);
  lcd.setCursor(4, 1);
  lcd.print("K3:");
  lcd.print(k3);

}
