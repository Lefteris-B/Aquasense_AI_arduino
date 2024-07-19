### TinyML Plant Protection
This functionality enables the microcontroller to autonomously determine windshield actuation based on real-time monitoring 
of wind velocity fluctuations and emerging meteorological conditions.

**Required Libs**
- tflm_esp32 v1.0.0 <- Tensorflow for ESP32
- EloquentTinyML v3.0.1 <- Abstraction Layer

**Functions**
- void ml_init(): Initializes the model specified in "model.h" file.
- float ml_predict(float*): Executes the model and returns the first result.
Requires a float array as an input parameter with "X" number of items.
- uint ml_predict_latency(): Returns the latency of the last inference
in microseconds.

*Information about the ML model is not yet available*