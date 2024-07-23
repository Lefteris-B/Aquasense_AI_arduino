/* -----------------------
 *  Tiny Machine Learning 
 * ----------------------- */

#ifndef TINYML_H
#define TINYML_H

/* Load the required libraries for TinyML */
#include <tflm_esp32.h>
#include <eloquent_tinyml.h>

/* Model */
#include "model.h"

/* Instantiate model loader */
#define ARENA_SIZE 5000
Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;

void ml_init(void) {
  Serial.println("__TINYML_INIT__");

  /* Initialize model loader and check for errors. */
  while (!tf.begin(model).isOk()) {
    Serial.println(tf.exception.toString());
  }
}

float ml_predict(float *input) {
  /* Predict and check for errors */
  if (!tf.predict(input).isOk()) {
    Serial.println(tf.exception.toString());
  }

  return tf.output(0);
}

unsigned int ml_predict_time(void) {
    return tf.benchmark.microseconds();
}

#endif