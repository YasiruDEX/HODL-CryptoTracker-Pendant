#include "ServoManager.h"

void ServoManager::attach(int pin) {
  Zaxis.attach(pin);
}

void ServoManager::write(int angle) {
  Zaxis.write(angle);
}
