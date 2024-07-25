#ifndef MOISTURESENSOR_HPP
#define MOISTURESENSOR_HPP

class MoistureSensor {
public:
  /**
   * Configures which pin the moisture sensor is connected to.
   * 
   * @param pin The pin which the moisture sensor is connected to.
   */
  void attach(int pin);

  /**
   * Reads the moisture value of the sensor.
   * 
   * The returned value is in the range 0-1, where 0 is full dry and 1 is full wet.
   */
  double read();

private:
  int pin;
};

#endif
