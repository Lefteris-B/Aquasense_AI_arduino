#include "Valve.hpp"

void Valve::attach(int pin) {
  servo.attach(pin, 500, 2500);

  // Always make sure that the valve is closed on startup.
  close();
}

void Valve::open() {
  servo.write(0);
  // The servo rotates at about 2.5ms per degree, so 300ms should be enough for a 90-degree turn.
  delay(300);
}

void Valve::close() {
  servo.write(90);
  delay(300);
}
