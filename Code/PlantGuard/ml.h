/* -----------------------
 *  Tiny Machine Learning
 * ----------------------- */
#ifndef ML_H
#define ML_H

#include <Arduino.h>
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

private:
  /* Model loader instance */
  Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;

  bool fail;
};

#endif