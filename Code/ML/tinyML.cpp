#include "tinyML.h"

void ml_init(void) {
  Serial.println("__TINYML_INIT__");

  while (!tf.begin(model).isOk()) {
    Serial.println(tf.exception.toString());
  }
}