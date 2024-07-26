#include <Wire.h>

#include "Cover.hpp"
#include "LightSensor.hpp"
#include "MoistureSensor.hpp"
#include "TemperatureSensor.hpp"
#include "Accelerometer.hpp"

Accelerometer accel;
MoistureSensor moisture;
TemperatureSensor temp;
LightSensor light;

void setup() {
  Serial.begin(115200);
  Wire.begin(13, 15);

  accel.begin(10);
  
  cover.attachMotor(16, 17);
  cover.attachSwitch(32, 33);

  light.attach(36, 10000); // 36 = VP
  temp.attach(39, 10000); // 39 = VN
  moisture.attach(34);
}

void loop() {
  Serial.printf("%lf\n", temp.read());
  delay(100);
}
