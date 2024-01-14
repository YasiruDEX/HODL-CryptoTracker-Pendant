#ifndef SERVO_MANAGER_H
#define SERVO_MANAGER_H

#include <Servo.h>

class ServoManager {
public:
  void attach(int pin);
  void write(int angle);
private:
  Servo Zaxis;
};

#endif
