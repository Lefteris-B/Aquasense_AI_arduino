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

uint8_t ML::ml_predict(double *input) {
  if (fail == true) {
    return 0; // Don't move if something is off
  }
  
  /* Scale the input values */
  float scaled[3] = {0};
  input_scaler(input, scaled); 

  /* Normalize values with minmax algorithm */
  float norm[3] = {0};
  minmax_norm(scaled, norm);

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

void ML::input_scaler(double *input, float *output) {
  output[0] = round(10 * ((input[0] - 0) / (sizeof(double) - 0)));
  output[1] = 0U; // Weather
  output[2] = round(10 * 0); // Unknown limits
}

float ML::sigmoid_function(float input) {
  return (1 / (1 + exp(-input)));
}

void ML::minmax_norm(float *input, float *output) {
  output[0] = (input[0] - 0)/(10 - 0);  // Wind
  output[1] = (input[1] - 0)/(2 - 0);   // Weather
  output[2] = (input[2] - 0)/(10 - 0);  // Luminance
}
