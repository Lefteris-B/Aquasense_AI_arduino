#ifndef LIGHTSENSOR_HPP
#define LIGHTSENSOR_HPP

class LightSensor {
public:
  /**
   * Configures which pin the photoresistor is connected, and what resistance is connected in series to it.
   * 
   * This class assumes that the photoresistor is connected to ground and the resistor to 3.3V.
   * 
   * @param pin The pin which the photoresistor is connected.
   * @param resistance The resistance of the resistor connected in series with the photorestistor.
   */
  void attach(int pin, double resistance);

  double read();

//protected:
  /**
   * Calculates the resistance of the photoresistor in ohms.
   */
  double getResistance();

private:
  int pin;
  double resistance;
};

extern LightSensor lightSensor;

#endif
