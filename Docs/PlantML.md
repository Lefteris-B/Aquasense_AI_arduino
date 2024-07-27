## TinyML Plant Protection
This functionality enables the microcontroller to autonomously determine windshield actuation based on real-time monitoring 
of wind velocity fluctuations and emerging meteorological conditions.

### Requirements
**Board Addons**
- esp32 v2.0.17 <-- v3.0 throws errors

**Libraries**
- tflm_esp32 v1.0.0 <- Tensorflow for ESP32
- EloquentTinyML v3.0.1 <- Abstraction Layer

### **Available Functions**
- **uint8_t ml_predict(double\*)**
    - Executes the model and returns the result.
    - Requires a float array as an input parameter with 3 items.
    - Returns either 0 or 1
- **uint32_t ml_predict_time()**
    - Returns the latency of the last inference in microseconds.

### ML Model
**I/O**
- Inputs
    - Input 0 : Wind speed [0-10]
    - Input 1 : Weather [0 (Clear), 1 (Rain), 2 (Storm)]
    - Input 2 : Luminance [0-10]
- Outputs
    - Output 0 : DC Motor power decision [0/1]

**Architecture**

*Inference speed : < 250us!*

|**Layer**| Params |
|---------|--------|
|Dense 64 |  256   |
|Dense 32 |  2080  |
|Dense 16 |  528   |
|Dense 1  |  17    |

**Requirements**
- Flash: 14kB
- SRAM: 5kB (+ 14kB if loaded)

**Example use**
```
#include "ML.h"

ML ml; /* Automatically initiates */

float t0[3] = {1.0, 0.0, 0.0};

void setup() {
  Serial.begin(9600);
  ...
}

void loop() {
  uint8_t output = ml.ml_predict(t0);
  Serial.println(output);
  ...
  Serial.print("Inference time (us): ");
  Serial.println(ml.ml_predict_time());
  ...
}
```