#include <Servo.h>


//Testing all servo motors on arduino MEGA 


int servoPin = 8;                          //the pin the servo motor data line will be connected to
int inputPin = A1;                       //the input pin the pot is connected to
int fbPin = A0;
int angle = 0;                          //the intput angle
Servo myServo;                        //servo object

void setup() {
  Serial.begin(115200);             //use serial monitor for debugging
  myServo.attach(servoPin);    
  pinMode(inputPin, INPUT);

}

void loop() {

  angle = map(analogRead(inputPin),0,1023,10,180);
  Serial.println(angle);
  myServo.write(angle);
  
}
