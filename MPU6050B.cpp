#include "Arduino.h"
#include "MPU6050B.h"

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

MPU6050 mpu;

#define OUTPUT_READABLE_YAWPITCHROLL

bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

Quaternion q;
float ypr[3];
VectorFloat gravity;
volatile bool mpuInterrupt = false;
void dmpDataReady() {
    mpuInterrupt = true;
}



MPU_B::MPU_B()
{
}

void MPU_B::set()
{
  Serial.begin(115200);
  mpu.initialize();
  devStatus = mpu.dmpInitialize();

  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788);

  mpu.setDMPEnabled(true);
  attachInterrupt(0, dmpDataReady, RISING);
  mpuIntStatus = mpu.getIntStatus();
  dmpReady = true;
  packetSize = mpu.dmpGetFIFOPacketSize();
}

void MPU_B::loop()
{
  while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
}

float MPU_B::y(){
  return ypr[0]*180/M_PI;
}

float MPU_B::p(){
  return ypr[1]*180/M_PI;
}

float MPU_B::r(){
  return ypr[2]*180/M_PI;
}
