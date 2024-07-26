#include "Cover.hpp"
#include "Valve.hpp"

Valve valve;

void setup() {
  Serial.begin(115200);

  valve.attach(12);
  
  cover.attachMotor(16, 17);
  cover.attachSwitch(32, 33);
}

void loop() {
  // Go forth
  while (!cover.stepPositive());
  // And back
  while (!cover.stepNegative());
}
