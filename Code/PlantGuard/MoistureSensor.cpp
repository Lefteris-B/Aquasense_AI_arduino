#include "MoistureSensor.hpp"
#include <Arduino.h>

void MoistureSensor::attach(int pin) {
  this->pin = pin;
}

double MoistureSensor::read() {
  double v = analogRead(pin) / 4095.0;
  return 1 - v;
}
