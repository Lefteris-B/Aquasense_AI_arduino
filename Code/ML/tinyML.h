/* -----------------------
 *  Tiny Machine Learning 
 * ----------------------- */

#ifndef TINYML_H
#define TINYML_H

#include <stdint.h>

/* Model */
#include "model.h"

/* Load the required libraries for TinyML */
#include <tflm_esp32.h>
#include <eloquent_tinyml.h>

/* Instantiate model loader */
#define ARENA_SIZE 5000
Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;

/* Functions */
static inline float sigmoid_function(float input) {
  return (1 / (1 + exp(-input)));
}

void ml_init(void) {
  Serial.println("__TINYML_INIT__");

  tf.setNumInputs(3);
  tf.setNumOutputs(1);
  tf.resolver.AddFullyConnected();

  /* Initialize model loader and check for errors. */
  while (!tf.begin(model).isOk()) {
    Serial.println(tf.exception.toString());
  }
}

uint8_t ml_predict(uint8_t *input) {
  /* Normalize values with minmax algorithm */
  float norm[3] = {0};
  norm[0] = (input[0] - 0)/(10 - 0);  // Wind
  norm[1] = (input[1] - 0)/(2 - 0);   // Weather
  norm[2] = (input[2] - 0)/(10 - 0);  // Luminance

  /* Predict and check for errors */
  if (!tf.predict(input).isOk()) {
    Serial.println(tf.exception.toString());
  }

  /* Apply sigmoid function */
  output = sigmoid_function(tf.output(0));

  /* Return either 0 or 1 */
  return round(output);
}

uint32_t ml_predict_time(void) {
    return tf.benchmark.microseconds();
}

#endif