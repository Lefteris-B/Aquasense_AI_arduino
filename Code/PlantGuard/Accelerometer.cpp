#include "Accelerometer.hpp"
#include <Arduino.h>

void Accelerometer::task(void *param) {
  Accelerometer *accel = (Accelerometer *) param;

  while (true) {
    accel->index = (accel->index + 1) % accel->count;
    accel->measurements[accel->index] = accel->read();
    delay(100);
  }
}

void Accelerometer::begin(int count) {
  this->adxl = ADXL345_WE();
  this->count = count;

  adxl.init();
  adxl.setDataRate(ADXL345_DATA_RATE_12_5);
  adxl.setRange(ADXL345_RANGE_2G);
  
  double first = read();
  measurements = (double *) malloc(count * sizeof(double));
  for (int i = 0; i < count; i++) {
    measurements[i] = first;
  }
  index = -1;

  xTaskCreate(Accelerometer::task, "Acceleration", 2048, this, 1, NULL);
}

double Accelerometer::read() {
  xyzFloat g = adxl.getGValues();
  return sqrt(g.x*g.x + g.y*g.y + g.z*g.z);
}

double Accelerometer::average() {
  double sum = 0;
  for (int i = 0; i < count; i++) {
    sum += measurements[i];
  }
  return sum / count;
}

double Accelerometer::variance() {
  double avg = average();
  double sum = 0;
  for (int i = 0; i < count; i++) {
    double g = measurements[i];
    sum += (g - avg) * (g - avg);
  }
  return sum / count;  
}
