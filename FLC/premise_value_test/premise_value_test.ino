#include <Servo.h>
#include <MPU6050.h>
#include <slewingFLC.h>



  MPU6050 mpu;
  long loop_timer;

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
  
 int a;

  //defining the slewing FLC
  slewingFLC FLC1(&loadangleer, &posangleerr, &changeinpos);

  int servoPin = 52;
  Servo myServo;
  int positionError = 0;
  int currentAngle = 90;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  myServo.attach(servoPin);
  myServo.write(currentAngle);
  mpu.setup_mpu_6050_registers();
  mpu.calibrateMPU6050();
  loop_timer = micros();

}

void loop() {
  a = mpu.measureAngle();
  FLC1.findslewingFLCoutput(a, positionError);
  //Serial.print(FLC1.Pvalue1);Serial.print(" ");Serial.print(FLC1.Pvalue2);Serial.print(" ");Serial.print(FLC1.Pvalue3);Serial.print(" ");Serial.print(FLC1.Pvalue4);Serial.print(" ");Serial.print(FLC1.Pvalue5);Serial.print(" ");Serial.print(FLC1.Pvalue6);Serial.print(" ");Serial.print(FLC1.Pvalue7);Serial.print(" ");Serial.print(FLC1.Pvalue8);Serial.print(" ");Serial.print(FLC1.Pvalue9);Serial.println(" ");
  Serial.print("Position error: "); Serial.print(positionError);Serial.print("  Load Angle Error: "); Serial.print(a); Serial.print("  FLC Output: "); Serial.println(FLC1.findslewingFLCoutput(a, positionError));
  currentAngle = currentAngle + FLC1.crispOutput;
  myServo.write(currentAngle);
  while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer
}
