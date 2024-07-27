#include "Cover.hpp"
#include "Valve.hpp"
#include "ML.h"

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

  valve.attach(12);

  cover.attachMotor(16, 17);
  cover.attachSwitch(32, 33);
}

void loop() {
  // Go back and forth acoording to the model
  if (ml.ml_predict(sample) == 1) {
    cont_rotation();
  }
}
