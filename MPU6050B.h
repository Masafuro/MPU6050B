#ifndef MPU6050B_h
#define MPU6050B_h

#include "Arduino.h"

class MPU_B
{
public:
  MPU_B();
  void set();
  void loop();
  float y();
  float p();
  float r();

private:
  int _pin;
};

#endif
