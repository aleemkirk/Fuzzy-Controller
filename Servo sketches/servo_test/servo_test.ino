#include <Servo.h>

//testing servo motor on esp module

int pot = A1;   //pot connected to this pin
int baud =115200; //the baud rate 
int desiredAngle = 1;  //the angle of the servo motor
int setpointAngle = 1;
int servoPin = D0;  //the pin the servo will be connected to
int pushBtn = D1;
Servo myServo;

void setup() {
  // put your setup code here, to run once:
  pinMode(pot, INPUT); //setting the pot pin as an input
  pinMode(servoPin, OUTPUT);  //setting the servo pin to an output
  pinMode(pushBtn, INPUT);
  myServo.attach(servoPin);
  Serial.begin(baud);

}

void loop() {
  desiredAngle = map(analogRead(pot), 0, 1024, 1, 180);  //mapping the input value to some angle between 0 and 180 degrees
  if((bool)digitalRead(pushBtn)){
    setpointAngle = desiredAngle;
    myServo.write(setpointAngle);
  }else{
    myServo.write(setpointAngle);
  }
  Serial.print("Desired Angle: "); Serial.print(desiredAngle);
  Serial.print("  Setpoint Angle: "); Serial.println(setpointAngle);
}
