#include <Arduino.h>

#include "LightSensor.hpp"

void LightSensor::attach(int pin, double resistance) {
  this->pin = pin;
  this->resistance = resistance;
}

double LightSensor::getResistance() {
  double voltage = analogRead(pin) / 4095.0 * 3.3;
  double r = voltage / (3.3 - voltage) * resistance;
  return r;
}

double LightSensor::read() {
  double r = getResistance();
  return pow(r/7570.0, -1.25);
}
