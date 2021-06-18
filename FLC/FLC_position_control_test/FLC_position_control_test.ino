#include <Servo.h>
#include <slewingFLC.h>

  //defining the load angle error input
  TrapFLCSet left(-90, -60, 0);
  TriFLCSet center(-5, 0, 5);
  TrapFLCSet right(90, 60, 0);
  LoadAngleErr loadangleer(left, center, right);

  //defining the position angle error input
  TrapFLCSet posLeft(-180, -150, 0);
  TriFLCSet none(-5, 0, 5);
  TrapFLCSet posRight(180, 150, 0);
  PosAngleErr posangleerr(posLeft, none, posRight);

  //defining the change in position output
  SingleFLCSet moveRight(-10);
  SingleFLCSet noChange(0);
  SingleFLCSet moveLeft(10);
  ChangeInPos  changeinpos(moveRight, noChange, moveLeft);

  slewingFLC FLC1(&loadangleer, &posangleerr, &changeinpos);

int posFBpin = A0;
float posFB = 0;
int x = A1;
int y = A2;
int baseServoPin = 8;
float posError =0;
float posErrorGain = 1;
float outputGain = 1;
int loadAngleError = 0;
Servo baseServo; int baseServoAngle;

void setup() {
  Serial.begin(115200);
  pinMode(posFBpin, INPUT);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  baseServo.attach(baseServoPin);

}

void loop() {

  baseServoAngle = map(analogRead(x), 0, 1023, 0, 180);         //position angle set point
  posFB = map(analogRead(posFBpin), 114, 393, 10, 180);          //position angle feedback
  posError = posErrorGain*(baseServoAngle - posFB);
  baseServo.write(posFB + outputGain*(FLC1.findslewingFLCoutput(loadAngleError, posError)));
  Serial.print("Posistion SP: "); Serial.print(baseServoAngle); Serial.print(" Posistion FeedBack: "); Serial.print(posFB); Serial.print(" Position Error: "); Serial.println(baseServoAngle-posFB);

}
