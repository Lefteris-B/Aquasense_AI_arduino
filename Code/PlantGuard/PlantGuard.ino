#include <Wire.h>

#include "Cover.hpp"
#include "LightSensor.hpp"
#include "MoistureSensor.hpp"
#include "TemperatureSensor.hpp"
#include "Accelerometer.hpp"
#include "Valve.hpp"
#include "ML.h"

/* Sensors */
Accelerometer accel;
MoistureSensor moisture;
TemperatureSensor temp;
LightSensor light;

/* Mechanical parts */
Valve valve;

/* Machine Learning */
ML ml;

/* Continuously rotate the protection shield.
 * Should be moved over in Cover.hpp!
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

/* Light range scan function */
void light_range_scan_task(void *) {
  while (true) {
    double max_captured_light = 0.0;

    /* Perform a two-way cycle */
    while (!(cover.stepPositive())) {
      double curr_light = light.read();
      max_captured_light = max(curr_light, max_captured_light);
    }
    while (!(cover.stepNegative())) {
      double curr_light = light.read();
      max_captured_light = max(curr_light, max_captured_light);
    }

    ml.ml_set_max_light(max_captured_light);
    delay(1U * 1000U * 60U * 30U); // Wait for 30 min.
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

  ml.ml_set_max_accel(1.0); // Default value
  ml.ml_set_max_light(1.0); // Default value

  xTaskCreate(light_range_scan_task, "LRS", 2048, NULL, 1, NULL);
}

void loop() {
  /* Go back and forth according to the model (assume weather is clear) */
  double sample[3] = {accel.variance(), 0.0 /* weather.code() */, light.read()};
  if (ml.ml_predict(sample) == 1) {
    cont_rotation();
  }

  Serial.printf("Temperature: %.1lf\n", temp.read());
  Serial.printf("Light: %lf\n", light.read());
  Serial.printf("Movement: %lf\n", accel.variance());
  Serial.printf("Moisture: %.3lf\n", moisture.read());
  delay(500);
}
