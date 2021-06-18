#include <FilterDerivative.h>
#include <FilterOnePole.h>
#include <Filters.h>
#include <FilterTwoPole.h>
#include <FloatDefine.h>
#include <RunningStatistics.h>

#include <MPU6050.h>

MPU6050 mpu;
int betaAngle, phiAngle = 0;
int betafbPin = 12;       //PWM pin
int phifbPin = 13;
long loop_timer;
FilterOnePole highpassFilter( HIGHPASS, 1 );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  pinMode(betafbPin, OUTPUT);
  pinMode(phifbPin, OUTPUT);
  mpu.setup_mpu_6050_registers();
  mpu.calibrateMPU6050();
  loop_timer = micros();
}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.measureAngle();
  betaAngle = highpassFilter.input(mpu.getBeta());
  phiAngle = mpu.getPhi();
  analogWrite(betafbPin, map(betaAngle, -90, 90, 0, 255));
  analogWrite(phifbPin, map(phiAngle, -90, 90, 0, 255));
  Serial.print("Load Anlge: "); Serial.print(betaAngle);Serial.print(" Output Voltage: "); Serial.println(map(betaAngle, -90, 90, 0, 5));
  while(micros() - loop_timer < 16000);                                 //Wait until the loop_timer reaches 16000us (62.5Hz) before starting the next loop
  loop_timer = micros(); 
}
