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

void ml_init(void);

#endif