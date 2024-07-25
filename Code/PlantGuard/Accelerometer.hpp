#ifndef ACCELEROMETER_HPP
#define ACCELEROMETER_HPP

#include <SparkFun_ADXL345.h>

class Accelerometer {
public:
  /**
   * Turns the accelerometer on and starts taking measurements.
   * 
   * This spawns a task that continuously measures the acceleration and keeps the last `count` measurements. These measurements are used to extract statistics about the acceleration.
   * 
   * @param count How many measurements should be kept.
   * @param dt How much time (in milliseconds) should pass between each measurement.
   */
  void begin(int count, int dt = 100);

  /**
   * Reads the magnitude of the acceleration from the sensor.
   * 
   * @returns The magnitude of the accelerations in gs.
   */
  double read();

  /**
   * Returns the average of the last measurements.
   */
  double average();

  /**
   * Returns the variance of the last measurements.
   */
  double variance();

private:

  /**
   * The FreeRTOS task that measures the acceleration in intervals.
   */
  static void task(void *);

  ADXL345 adxl;
  double *measurements;
  int index;
  int count;
  int dt;
};

extern Accelerometer accel;

#endif
