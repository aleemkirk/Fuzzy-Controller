
#include <Servo.h>

Servo servo;
int servoPin = 3;
int pb = 2;
bool state = false;
void setup() {
  pinMode(pb, INPUT);
  servo.attach(servoPin);
  servo.write(1);
  

}

void loop() {
  state = digitalRead(pb);
  if (state){
    servo.write(180);
  }else{
    servo.write(10);
  }

}
