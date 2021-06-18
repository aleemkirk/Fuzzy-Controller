#include <Servo.h>
#include <slewingFLC.h>
#include <MPU6050.h>

//defining the load angle error input
  TrapFLCSet left(-90, -60, 0);
  TriFLCSet center(-5, 0, 5);
  TrapFLCSet right(90, 60, 0);
  LoadAngleErr loadangleer(left, center, right);

  //defining the position angle error input
  TrapFLCSet posLeft(-180, -150, 0);
  TriFLCSet none(-20, 0, 20);
  TrapFLCSet posRight(180, 150, 0);
  PosAngleErr posangleerr(posLeft, none, posRight);

  //defining the change in position output
  SingleFLCSet moveRight(-10);
  SingleFLCSet noChange(0);
  SingleFLCSet moveLeft(10);
  ChangeInPos  changeinpos(moveRight, noChange, moveLeft);

  //defining the slewing FLC
  slewingFLC FLC1(&loadangleer, &posangleerr, &changeinpos);

int posSP = 0;
int potPin = A1;
int posErr = 0;
int fbPin = A0;
int posFB = 0;
float posFB1, posFB2 = 0;
int posErrGain = 2;
int servoPin = 8;
int desAngle = 0;
//MPU6050 mpu;
//int loadAngle;

Servo s1;
long loop_timer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Wire.begin();
  //mpu.setup_mpu_6050_registers();
  //mpu.calibrateMPU6050();
  pinMode(potPin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(fbPin, INPUT);
  s1.attach(servoPin);
  loop_timer = micros();

}

void loop() {

  posSP = map(analogRead(potPin), 0, 1023, 30, 180);
  posFB2 = posFB1;
  posFB1 = map(analogRead(fbPin), 168, 470, 30, 180);
  posFB = (int)(0.945*posFB1 + 0.0549*posFB2);                          //filtering the position FB
  posErr = posSP - posFB;
  //loadAngle = -0.5*mpu.measureAngle();
  desAngle = posFB + (int)FLC1.findslewingFLCoutput(0, posErrGain*posErr);
  if ((int)FLC1.findslewingFLCoutput(0, posErrGain*posErr)>=8 || (int)FLC1.findslewingFLCoutput(0, posErrGain*posErr) <= -8){
    s1.attach(servoPin);
    s1.write(desAngle);
  }else{
    s1.detach();
  }
  Serial.print("Pos SP: "); Serial.print(posSP);Serial.print(" Pos FB: ");Serial.print(posFB);Serial.print(" Des Angle: "); Serial.print(desAngle);Serial.print(" FLC Output: "); Serial.println(FLC1.findslewingFLCoutput(0, posErrGain*posErr)); //Serial.print(" Load Angle: "); Serial.println(loadAngle);
  while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer

}
