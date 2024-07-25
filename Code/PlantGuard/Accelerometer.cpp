#include "Accelerometer.hpp"

Accelerometer accel;

void Accelerometer::task(void *param) {
  Accelerometer *accel = (Accelerometer *) param;

  while (true) {
    accel->index = (accel->index + 1) % accel->count;
    accel->measurements[accel->index] = accel->read();
    delay(accel->dt);
  }
}

void Accelerometer::begin(int count, int dt) {
  this->adxl = ADXL345();
  this->count = count;
  this->dt = dt;

  adxl.powerOn();
  adxl.setRangeSetting(2);

  double first = read();
  measurements = (double *) malloc(count * sizeof(double));
  for (int i = 0; i < count; i++) {
    measurements[i] = first;
  }
  index = -1;

  xTaskCreate(Accelerometer::task, "Accelerometer", 2048, this, 1, NULL);
}

double Accelerometer::read() {
  int x, y, z;
  adxl.readAccel(&x, &y, &z);
  
  double gx = x / 256.0;
  double gy = y / 256.0;
  double gz = z / 256.0;
  return sqrt(gx*gx + gy*gy + gz*gz);
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
