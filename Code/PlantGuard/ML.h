/* -----------------------
 *  Tiny Machine Learning
 * ----------------------- */
#ifndef ML_H
#define ML_H

#include <stdint.h>

/* Model */
#include "model.h"

/* Load the required libraries for TinyML */
#include <tflm_esp32.h>
#include <eloquent_tinyml.h>

/* Allow up to 5kB SRAM */
#define ARENA_SIZE 5000

/**
 * This class executes the ML model used for deciding DC motor movement
 */
class ML {
public:
  ML();

  /**
    * Executes the ML inference routine
    *
    * @param input The input array pointer of type uint8_t that contains the values used for the classifier.
    * @returns Either 1 (Move) or 0 (Don't move) depending on the result of the inference.
    */
  uint8_t ml_predict(uint8_t *input);

  /**
    * @returns The last inference time in microseconds.
    */
  uint32_t ml_predict_time(void);

protected:
  /**
    * Initiates the classification model. This must be run before any other function declared here.
    * @returns True for success, False for failure.
    */
  bool ml_init(void);

  /**
    * This function applies the sigmoid logistic activation on the input.
    * @param input The output float number that has to be activated.
    * @returns The output of the function.
    */
  float sigmoid_function(float &input);

  /**
    * This function applies the MinMax normalization on the input.
    *
    * Changes are applied directly on the input array.
    *
    * @param input The pointer of the float array that has to be normalized.
    */ 
  void minmax_norm(float *input);

private:
  /* Model loader instance */
  Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;

  bool fail;
};

#endif
