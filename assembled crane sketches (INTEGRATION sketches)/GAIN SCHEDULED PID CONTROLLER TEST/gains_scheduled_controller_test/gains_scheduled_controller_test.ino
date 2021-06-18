#include <PID_v1.h>
#include <FilterDerivative.h>
#include <FilterOnePole.h>
#include <Filters.h>
#include <FilterTwoPole.h>
#include <FloatDefine.h>
#include <RunningStatistics.h>
#include <Servo.h>
#include <slewingFLC.h>
#include <MPU6050.h>
#include <LiquidCrystal.h>


int potPin = A1;
int servoPin = 8;
int desAngle = 0;
const double thresh = 0.1;
MPU6050 mpu;
double beta = 0;
double posSP = 0;
double posErr = 0;
double swingSP = 0;
double swingErr = 0;;
double posFB = 0;
double slewControllerOutput = 0;
double swingControllerOutput = 0;
double filteredFB = 0;
PID slewingController(&filteredFB, &slewControllerOutput, &posSP, 0.4, 0.008, 0, DIRECT);                            //creating the slewing position PID controller 
PID tangentialSwingController(&beta, &swingControllerOutput, &swingSP, 1, 0, 0, DIRECT);                    //creating the swing dampening PID controller

Servo s1;
const int rs = 34, en = 32, d4 = 30, d5 = 28, d6 = 26, d7 = 24;
int k1Pin = A8;
int k2Pin = A9;
int k3Pin = A10;
int k1, k2;
float k3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long loop_timer;
float filterFrequency = 5;                  //use 5Hz for HS 85 and 0.63 for MG90s
FilterOnePole lowpassFilter( LOWPASS, filterFrequency );
FilterOnePole highpassFilter( HIGHPASS, 1 );
int posFBpin = 11;
int betafbPin = 12;       //PWM pin


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  pinMode(betafbPin, OUTPUT);
  mpu.setup_mpu_6050_registers();
  mpu.calibrateMPU6050();
  pinMode(potPin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(posFBpin, OUTPUT);
  s1.attach(servoPin);
  posSP = 45;
  swingSP = 0;
  slewingController.SetOutputLimits(-180, 180);
  slewingController.SetSampleTime(16);
  tangentialSwingController.SetOutputLimits(-90, 90);
  tangentialSwingController.SetSampleTime(16);
  slewingController.SetMode(AUTOMATIC);
  tangentialSwingController.SetMode(AUTOMATIC);
  loop_timer = micros();
}

void loop() {
  posSP = (double)map(analogRead(potPin), 0, 1023, 30, 180);
  filteredFB = (double)lowpassFilter.input(s1.read());
  mpu.measureAngle();
  beta = (double)highpassFilter.input(mpu.getBeta());
  slewingController.Compute();
  tangentialSwingController.Compute();
  desAngle = (int)(filteredFB + slewControllerOutput + swingControllerOutput);
  if ((double)(slewControllerOutput + swingControllerOutput) >= thresh || (double)(slewControllerOutput + swingControllerOutput) <= -1*thresh){
    s1.attach(servoPin);
    s1.write(desAngle);
  }else{
    s1.detach();
  }
  analogWrite(posFBpin, map(filteredFB, 0, 180, 0, 255));                //writing posFB to PWM pin
  analogWrite(betafbPin, map(beta, -90, 90, 0, 255));
  Serial.print(slewControllerOutput); Serial.print(" "); Serial.print(swingControllerOutput); Serial.print(" "); Serial.print(filteredFB); Serial.print(" "); Serial.println(posSP);
  while(micros() - loop_timer < 16000);                                 //Wait until the loop_timer reaches 16000us (62.5Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer

}
