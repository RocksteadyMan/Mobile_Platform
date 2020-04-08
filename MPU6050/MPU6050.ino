#include <Wire.h>

const int MPU_addr=0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
double AcYsum, GyXsum;
float Ang_;
int max_speed=100;
int setspeed=20;
float CompensatorZ, CompensatorAcX;


void setup() {
  // put your setup code here, to run once:
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);

AcYsum=0;
GyXsum=0;

CompensatorZ=0; CompensatorAcX=0;
for(int i=0; i<500;i++)
{
  delay(10);
  Data_mpu6050();
  CompensatorZ +=GyZ;
  CompensatorAcX+=AcX;
}
CompensatorZ=CompensatorZ/500.0;
CompensatorAcX = CompensatorAcX/500.0;

}

void Data_mpu6050()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8 | Wire.read();
  AcY=Wire.read()<<8 | Wire.read();
  AcZ=Wire.read()<<8 | Wire.read();
  Tmp=Wire.read()<<8 | Wire.read();
  GyX=Wire.read()<<8 | Wire.read();
  GyY=Wire.read()<<8 | Wire.read();
  GyZ=Wire.read()<<8 | Wire.read();
}

void time_gyro(float mill_sec)
{
  long ms = mill_sec;
  unsigned long timer = micros();
  unsigned long endtime = micros() + long(ms*1000.0);
  while (endtime>timer){
     timer=micros();
     Data_mpu6050();
     Ang_ = Ang_ + (((float)(GyZ) - CompensatorZ)*(float)(micros()-timer))/131000000.0;
     delayMicroseconds(1);
    
  }
}

void Angle(float ang)
{
  int _speed = max_speed;
  bool flag = false;
  float Ang_2 = Ang_; long timer;
  setspeed(_speed, _speed);

  if (ang==0) return;
  if(ang<0)
  {
    do{
      right(); time_gyro(1); _stop(); time_gyro(1);
      
    }
    while (Ang_>(ang+Ang_2));
  }
  else
  {
    do{
      left(); time_gyro(1); _stop(); time_gyro(1);
    }
    while (Ang_ <(ang+Ang_2));
  }
  _stop();
  Ang_2 = Ang_ - (ang + Ang_2);
  if(abs(Ang_2)>1.0)
  Angle(-Ang_2);
 // setspeed(max_speed, max_speed);
}

void loop() {
  // put your main code here, to run repeatedly:

}
