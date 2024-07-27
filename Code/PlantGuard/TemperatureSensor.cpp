#include "TemperatureSensor.hpp"
#include <Arduino.h>

void TemperatureSensor::attach(int pin, double resistance) {
  this->pin = pin;
  this->resistance = resistance;
}

double TemperatureSensor::read() {
  const double A = 0.0014696690;
  const double B = 0.00017546533;
  const double D = 4.1200050e-7;

  double v = analogRead(pin) / 4095.0 * 3.3;
  double r = v / (3.3 - v) * resistance;
  double l = log(r);
  double T = 1 / (A + B*l + D*pow(l, 3));
  return T - 273.15;
}
