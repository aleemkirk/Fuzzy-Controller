#include <MPU6050.h>
#include <FLCIn.h>


  MPU6050 mpu;
  long loop_timer;
//TriFLCSet triset(-1, 0, 1);
//TrapFLCSet trapset(2, 1, 0);
//SingleFLCSet singleset(1);
  TrapFLCSet left(-90, -60, 0);
  TriFLCSet center(-5, 0, 5);
  TrapFLCSet right(90, 60, 0);
  LoadAngleErr loadangleer(left, center, right);

  //fuzzy sets to test the position error angle input using values from the MPU6050
    TrapFLCSet posLeft(-180, -150, 0);
    TriFLCSet none(-5, 0, 5);
    TrapFLCSet posRight(180, 150, 0);
    PosAngleErr posangleerr(posLeft, none, posRight);
  
  int a;

  
void setup() {
  Wire.begin();
  Serial.begin(115200);
//  Serial.print("Index Value at "); Serial.print(a); Serial.println(" for:");
//  Serial.print("Trianglular: "); Serial.println(triset.getIndex(a));
//  Serial.print("Trapizoidal: "); Serial.println(trapset.getIndex(a));
//  Serial.print("Singleton: "); Serial.println(singleset.getIndex(a));
  mpu.setup_mpu_6050_registers();
  mpu.calibrateMPU6050();
  loop_timer = micros();

}

void loop() {
  a = mpu.measureAngle();
//Testing the load angle error input
//  loadangleer.findIndex(a);
//  Serial.print("  L: ");Serial.print(loadangleer.indexL);
//  Serial.print("  C: ");Serial.print(loadangleer.indexC);
//  Serial.print("  R: ");Serial.print(loadangleer.indexR);
//  Serial.print("  Angle: ");Serial.println(a);

//Testing the position error angle input
  posangleerr.findIndex(a);
  Serial.print("  L: ");Serial.print(posangleerr.indexL);
  Serial.print("  N: ");Serial.print(posangleerr.indexN);
  Serial.print("  R: ");Serial.print(posangleerr.indexR);
  Serial.print("  Position: ");Serial.println(a);
  while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer
}
