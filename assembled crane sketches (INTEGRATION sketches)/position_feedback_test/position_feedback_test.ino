#include <Servo.h>

int posFBpin = A0;
int posFB = 0;
int x = A1;
int y = A2;
int baseServoPin = 8;
Servo baseServo; int baseServoAngle;

void setup() {
  Serial.begin(115200);
  pinMode(posFBpin, INPUT);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  baseServo.attach(baseServoPin);

}

void loop() {

  baseServoAngle = map(analogRead(x), 0, 1023, 0, 180);
  baseServo.write(baseServoAngle);
  posFB = map(analogRead(posFBpin), 104, 428, 0, 180);
  Serial.print("Posistion SP: "); Serial.print(baseServoAngle); Serial.print(" Posistion FeedBack: "); Serial.println(posFB);

}
