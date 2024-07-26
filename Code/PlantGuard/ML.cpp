#include "ML.h"

ML::ML() {
  fail = false;

  if (ml_init() == false) {
    Serial.println("ML: Initialization failure");
  }
}

bool ML::ml_init(void) {
  Serial.println("__TINYML_INIT__");

  /* Structural information */
  tf.setNumInputs(3);
  tf.setNumOutputs(1);
  tf.resolver.AddFullyConnected();

  /* Initialize model loader and check for errors. */
  if (!tf.begin(model).isOk()) {
    fail = true;
  }

  return !(fail);
}

uint8_t ML::ml_predict(uint8_t *input) {
  if (fail == true) {
    return 0; // Don't move if something is off
  }

  /* Normalize values with minmax algorithm */
  float norm[3] = {0};
  minmax_norm(input, norm);

  /* Predict and check for errors */
  if (!tf.predict(norm).isOk()) {
    return 0; // Don't move if something is off
  }

  /* Apply sigmoid function */
  float output = sigmoid_function(tf.output(0));

  /* Return either 0 or 1 */
  return round(output);
}

uint32_t ML::ml_predict_time(void) {
    return tf.benchmark.microseconds();
}

float ML::sigmoid_function(float input) {
  return (1 / (1 + exp(-input)));
}

void ML::minmax_norm(uint8_t *input, float *output) {
  output[0] = (input[0] - 0)/(10 - 0);  // Wind
  output[1] = (input[1] - 0)/(2 - 0);   // Weather
  output[2] = (input[2] - 0)/(10 - 0);  // Luminance
}
