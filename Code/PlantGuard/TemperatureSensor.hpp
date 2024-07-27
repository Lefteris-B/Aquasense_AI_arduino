#ifndef TEMPERATURESENSOR_HPP
#define TEMPERATURESENSOR_HPP

class TemperatureSensor {
public:
  /**
   * Configures which pin the thermistor is connected to, and what resistance is connected in series to it.
   * 
   * @param pin The pin which the thermistor is connected to.
   * @param resistance The value of the resistance connected in series to the thermistor.
   */
  void attach(int pin, double resistance);

  /**
   * Reads the temperature from the sensor.
   */
  double read();

private:
  int pin;
  double resistance;
};

#endif
