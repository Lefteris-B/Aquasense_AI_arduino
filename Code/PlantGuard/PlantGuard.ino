#include <Wire.h>

#include "Cover.hpp"
#include "LightSensor.hpp"
#include "Accelerometer.hpp"

void setup() {
  Serial.begin(115200);
  Wire.begin(13, 15);

  accel.begin(10, 100);
  
  cover.attachMotor(16, 17);
  cover.attachSwitch(32, 33);

  lightSensor.attach(36, 10000); // 36 = VP
}

void loop() {
  Serial.printf("%lf\n", accel.variance());
  delay(100);
}
