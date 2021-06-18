#include <MPU6050.h>
#include <LiquidCrystal.h>


MPU6050 mpu;
long loop_timer;
int anglePin=3;
int angle;

void setup() {
  // put your setup code here, to run once:
    Wire.begin();                                                        //Start I2C as master
    Serial.begin(115200);                                               //Use only for debugging
    pinMode(anglePin, OUTPUT);    
    mpu.setup_mpu_6050_registers();
    mpu.calibrateMPU6050();
    loop_timer = micros(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  angle = mpu.measureAngle();
  //analogWrite(anglePin, map(angle, -90, 90, 0, 255));
  //Serial.print( map(angle, -90, 90, 0, 255));
  //Serial.print("\t");
  Serial.println(angle);
  while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer
}
