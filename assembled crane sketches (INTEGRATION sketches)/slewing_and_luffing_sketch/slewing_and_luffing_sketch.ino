#include <Servo.h>
#include <MPU6050.h>

MPU6050 mpu;
long loop_timer;
int loadAngle;
int x = A1;
int y = A2;
int baseServoPin = 8;
int boomServo1Pin = 9;
int boomServo2Pin = 10;
Servo baseServo; int baseServoAngle;
Servo boomServo1; int boomServo1Angle;
Servo boomServo2; int boomServo2Angle;

int getBoomServo2Angle(int a){
  return (180-a);
}

void setup() {

  Serial.begin(115200);
  Wire.begin();
  //mpu.setup_mpu_6050_registers();
  //mpu.calibrateMPU6050();
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  baseServo.attach(baseServoPin);
  boomServo1.attach(boomServo1Pin);
  boomServo2.attach(boomServo2Pin);
  loop_timer = micros(); 
}

void loop() {

  baseServoAngle = map(analogRead(x), 0, 1023, 0, 180);
  if (baseServoAngle <30)
    baseServoAngle = 30;
  if (baseServoAngle >150)
    baseServoAngle = 150;
  boomServo1Angle = map(analogRead(y), 0, 1023, 30, 60);
  boomServo2Angle = getBoomServo2Angle(boomServo1Angle);
  baseServo.write(baseServoAngle);
  boomServo1.write(boomServo1Angle);
  boomServo2.write(boomServo2Angle);
  //loadAngle = mpu.measureAngle();
  Serial.print("Slewing angle: "); Serial.print(baseServoAngle); Serial.print(" Luffing Angle: "); Serial.println(boomServo1Angle); //Serial.print(" Load angle: "); Serial.println(loadAngle);
  while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer

}



