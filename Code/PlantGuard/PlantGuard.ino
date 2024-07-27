#include <Wire.h>

#include "Cover.hpp"
#include "LightSensor.hpp"
#include "MoistureSensor.hpp"
#include "TemperatureSensor.hpp"
#include "Accelerometer.hpp"
#include "Valve.hpp"
#include "ML.h"

Accelerometer accel;
MoistureSensor moisture;
TemperatureSensor temp;
LightSensor light;

Valve valve;

/* ML related */
ML ml;
double sample[3] = {0.0, 0.0, 0.0};

/* Continuously rotate the protection 
 * This should be moved in Cover.hpp 
 */
void cont_rotation() {
  static bool rotate_forw = true;
  if (rotate_forw) {
    rotate_forw = !(cover.stepPositive());
  }
  else {
    rotate_forw = !(cover.stepNegative());
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(13, 15);

  accel.begin(10);

  valve.attach(12);

  cover.attachMotor(16, 17);
  cover.attachSwitch(32, 33);

  light.attach(36, 10000); // 36 = VP
  temp.attach(39, 10000); // 39 = VN
  moisture.attach(34);
}

void loop() {
  // Go back and forth acoording to the model
  if (ml.ml_predict(sample) == 1) {
    cont_rotation();
  }

  Serial.printf("Temperature: %.1lf\n", temp.read());
  Serial.printf("Light: %lf\n", light.read());
  Serial.printf("Movement: %lf\n", accel.variance());
  Serial.printf("Moisture: %.3lf\n", moisture.read());
  delay(500);
}
