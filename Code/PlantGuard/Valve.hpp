#ifndef VALVE_HPP
#define VALVE_HPP

#include <ESP32Servo.h>

class Valve {
public:
  /**
   * @param pin The pin which the servo motor is connected to.
   */
  void attach(int pin);

  /**
   * Opens the valve, allowing water to flow.
   */
  void open();

  /**
   * Closes the valve, stopping the water from flowing.
   */
  void close();

private:
  Servo servo;
};

#endif
