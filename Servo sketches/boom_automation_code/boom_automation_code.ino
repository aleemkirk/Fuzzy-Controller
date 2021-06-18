#include <Servo.h>

int servoPin1 = 10;                         
int servoPin2 = 11;
int inputPin = A0;                       //the input pin the pot is connected to
int servo1Angle = 0;                     
Servo myServo1;                        
Servo myServo2;

int getServo2Angle(int a){
  return (180 - a);
}

void setup() {

  Serial.begin(115200);             //use serial monitor for debugging
  myServo1.attach(servoPin1);    
  myServo2.attach(servoPin2);
  pinMode(inputPin, INPUT);
  servo1Angle = 45;
  myServo1.write(servo1Angle);
  myServo2.write(getServo2Angle(servo1Angle));  

}

void loop() {

  servo1Angle = map(analogRead(inputPin),0,1023,5,90);
  Serial.println(servo1Angle);
  
  myServo1.write(servo1Angle);
  myServo2.write(getServo2Angle(servo1Angle));
}
