#include <LiquidCrystal.h>
#include <Servo.h>




//push buttons will be usued to control the angle of the servo motor and the angle will be displayed on an LCD screen

int servoData = D3;      //servo data will come from this pin
int addBtn = D2;         //increase servo angle
const int rs = D0, en = D1, d4 = D4, d5 = D5, d6 = D6, d7 = D7;
Servo servo;
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);

int servoAngle;

void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(servoData, OUTPUT);
  pinMode(addBtn, INPUT);
  servoAngle = 0;
  LCD.begin(16, 2);
  servo.attach(servoData);
  servo.write(2);
  LCD.setCursor(0,0);
  LCD.print("Servo Angle: ");
  LCD.print(servoAngle);
 
}

void loop() {
  bool state = digitalRead(addBtn);
  if(servoAngle < 90 && state){
        servoAngle++;
        LCD.setCursor(0,0);
        LCD.print("Servo Angle: ");
        LCD.print(servoAngle);
  }
}
