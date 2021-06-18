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
int servoPin = 8;
int desAngle = 0;
const int thresh = 1;
//MPU6050 mpu;
//int loadAngle;

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
int filteredFB;
FilterOnePole lowpassFilter( LOWPASS, filterFrequency );
int posFBpin = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Wire.begin();
  //mpu.setup_mpu_6050_registers();
  //mpu.calibrateMPU6050();
  pinMode(potPin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(posFBpin, OUTPUT);
  s1.attach(servoPin);
  lcd.begin(16, 2);
  pinMode(k1Pin, INPUT);
  pinMode(k2Pin, INPUT);
  pinMode(k3Pin, INPUT);
  loop_timer = micros();

}

void loop() {
  lcd.clear();
  k1 = map(analogRead(k1Pin), 0, 1023, 0, 20);
  k2 = map(analogRead(k2Pin), 0, 1023, 0, 20);
  k3 = (float)map(analogRead(k3Pin), 0, 1023, 0, 11)/10;
  lcd.setCursor(2, 0);
  lcd.print("K1:");
  lcd.print(k1);
  lcd.setCursor(9, 0);
  lcd.print("K2:");
  lcd.print(k2);
  lcd.setCursor(4, 1);
  lcd.print("K3:");
  lcd.print(k3);
  posSP = map(analogRead(potPin), 0, 1023, 30, 180);
  filteredFB = lowpassFilter.input(s1.read());
  posErr = posSP - filteredFB; //posFB;
  //loadAngle = -0.5*mpu.measureAngle();
  desAngle = (int)(filteredFB + (float)k3*FLC1.findslewingFLCoutput(0, k1*posErr));
  if ((int)((float)k3*FLC1.findslewingFLCoutput(0, k1*posErr)) >= thresh || (int)((float)k3*FLC1.findslewingFLCoutput(0, k1*posErr)) <= -1*thresh){
    s1.attach(servoPin);
    s1.write(desAngle);
  }else{
    s1.detach();
  }
  analogWrite(posFBpin, map(filteredFB, 0, 180, 0, 255));                //writing posFB to PWM pin
  Serial.print("Pos SP: "); Serial.print(posSP);Serial.print(" Pos FB: ");Serial.print(filteredFB);Serial.print(" Des Angle: "); Serial.print(desAngle);Serial.print(" FLC Output: "); Serial.println((float)k3*FLC1.findslewingFLCoutput(0, k1*posErr)); //Serial.print(" Filtered FB: "); Serial.println(filteredFB);
  while(micros() - loop_timer < 16000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer

}
