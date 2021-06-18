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



float flcOutput = 0;
int posSP = 0;
int potPin = A1;
int posErr = 0;
int posFB = 0;
int servoPin = 8;
int desAngle = 0;
const int thresh = 1;
MPU6050 mpu;
int beta = 0;

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
FilterOnePole highpassFilter( HIGHPASS, 1 );
int posFBpin = 11;
int betafbPin = 12;       //PWM pin


void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  Wire.begin();
  pinMode(betafbPin, OUTPUT);
  mpu.setup_mpu_6050_registers();
  mpu.calibrateMPU6050();
  pinMode(potPin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(posFBpin, OUTPUT);
  s1.attach(servoPin);
  lcd.begin(16, 2);
  lcd.noCursor();
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
  lcd.print(k1);
  lcd.print("; ");
  lcd.print(k2);
  lcd.print("; ");
  lcd.setCursor(0, 1);
  lcd.print(k3);
  posSP = map(analogRead(potPin), 0, 1023, 30, 180);
  filteredFB = lowpassFilter.input(posSP);
  s1.write(filteredFB);
  mpu.measureAngle();
  beta = highpassFilter.input(mpu.getBeta());
  analogWrite(posFBpin, map(filteredFB, 0, 180, 0, 255));                //writing posFB to PWM pin
  analogWrite(betafbPin, map(beta, -90, 90, 0, 255));
//  Serial.print("Pos SP: "); Serial.print(posSP);Serial.print(" Pos FB: ");Serial.print(filteredFB);Serial.print(" Des Angle: "); Serial.print(desAngle);Serial.print(" FLC Output: "); Serial.print(flcOutput); 
//  Serial.print(" K1: "); Serial.print(k1); Serial.print(" K2: "); Serial.print(k2); Serial.print(" K3: "); Serial.print(k3); Serial.print(" Beta: "); Serial.println(beta);
//  Serial.print("Loop time: "); Serial.println(micros() - loop_timer);
  while(micros() - loop_timer < 16000);                                 //Wait until the loop_timer reaches 16000us (62.5Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer

}
