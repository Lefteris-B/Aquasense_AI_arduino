#include "Cover.hpp"
#include "LightSensor.hpp"

void setup() {
  Serial.begin(115200);
  
  cover.attachMotor(16, 17);
  cover.attachSwitch(32, 33);

  lightSensor.attach(36, 10000); // 36 = VP
}

void loop() {
  Serial.printf("%lf\n", lightSensor.read());
  delay(100);
}
