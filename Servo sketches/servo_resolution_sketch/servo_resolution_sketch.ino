#include <Servo.h>

int servoPin = 2;
int potPin = A1;
int fbPin = A0;
int pb = 3;
int angle = 10;
Servo s1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pb, INPUT);
  s1.attach(servoPin);
  s1.write(angle);

}

void loop() {

//  if(digitalRead(pb)){
//    angle = angle + 1;
//  }
//  s1.write(angle);
//  Serial.println(angle);
//  delay(500);
  angle = map(analogRead(potPin), 0, 1023, 30, 180);
  s1.write(angle);
  Serial.print(angle);Serial.println(analogRead(fbPin));

}
