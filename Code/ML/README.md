## TinyML Plant Protection
This functionality enables the microcontroller to autonomously determine windshield actuation based on real-time monitoring 
of wind velocity fluctuations and emerging meteorological conditions.

### Requirements
**Board Addons**
- esp32 v2.0.17 <-- v3.0 throws errors

**Libraries**
- tflm_esp32 v1.0.0 <- Tensorflow for ESP32
- EloquentTinyML v3.0.1 <- Abstraction Layer

### **Functions**
- **void ml_init()**
    - Initializes the model specified in "model.h" file.

- **uint8_t ml_predict(uint8_t\*)**
    - Executes the model and returns the result.
    - Requires a uint8_t array as an input parameter with 3 items.
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
|**Layer**| Params |
|---------|--------|
|Dense 64 |  256   |
|Dense 32 |  2080  |
|Dense 16 |  528   |
|Dense 1  |  17    |
*Inference speed : < 250us!*

**Requirements**
- Flash: 14kB
- SRAM: 5kB (+ 14kB if loaded)

**Example use**
```
#include <stdint.h>
#include "ML/tinyML.h"

uint8_t t0[3] = {10U, 0U, 0U};  /* Outputs 1*/

void setup() {
  Serial.begin(9600);
  ml_init();
}

void loop() {
  uint8_t output = ml_predict(t0);
  Serial.println(output);

  Serial.print("Inference time (us): ");
  Serial.println(ml_predict_time());
}
```