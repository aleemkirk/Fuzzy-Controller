#include <PID_v1.h>
#include <FilterDerivative.h>
#include <FilterOnePole.h>
#include <Filters.h>
#include <FilterTwoPole.h>
#include <FloatDefine.h>
#include <RunningStatistics.h>
#include <Servo.h>
#include <MPU6050.h>


int potPin = A1;
int servoPin = 8;
const int thresh = 1;
double posSP = 20;
double slewControllerOutput = 0;
double filteredFB = 0;
PID slewingController(&filteredFB, &slewControllerOutput, &posSP, 0.4, 0.008, 0, DIRECT);                            //creating the slewing position PID 
int desAngle = 0;

Servo s1;
float filterFrequency = 5;                  //use 5Hz for HS 85 and 0.63 for MG90s
FilterOnePole lowpassFilter( LOWPASS, filterFrequency );
FilterOnePole highpassFilter( HIGHPASS, 1 );
int posFBpin = 11;
int betafbPin = 12;       //PWM pin


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  pinMode(potPin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(posFBpin, OUTPUT);
  s1.attach(servoPin);
  posSP = (double)map(analogRead(potPin), 0, 1023, 30, 180);
  s1.write(posSP);
  slewingController.SetOutputLimits(-180, 180);
  slewingController.SetSampleTime(16);
  slewingController.SetMode(AUTOMATIC);
}

void loop() {
  posSP = (double)map(analogRead(potPin), 0, 1023, 30, 180);
  filteredFB = (double)lowpassFilter.input(s1.read());
  slewingController.Compute();
  desAngle = (int)(filteredFB + slewControllerOutput);
  if ((int)(slewControllerOutput) >= thresh || (int)(slewControllerOutput) <= -1*thresh){
    s1.attach(servoPin);
    s1.write(desAngle);
  }else{
    s1.detach();
  }
  analogWrite(posFBpin, map(filteredFB, 0, 180, 0, 255));                //writing posFB to PWM pin
  Serial.print(slewControllerOutput); Serial.print(" "); Serial.print(posSP); Serial.print(" "); Serial.print(filteredFB); Serial.print(" "); Serial.println(desAngle);

}
