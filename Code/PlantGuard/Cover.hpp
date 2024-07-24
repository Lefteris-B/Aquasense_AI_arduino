#ifndef COVER_HPP
#define COVER_HPP

/**
 * This class controls the motor that rotates the cover.
 */
class Cover {
public:
  Cover();

  /**
   * @param motor_pos_pin The GPIO pin connected to the motor, which when given power rotates the cover in the positive direction (counterclockwise).
   * @param motor_neg_pin The GPIO pin connected to the motor, which when given power rotates the cover in the negative direction (clockwise).
   * @param on_time The duration that the motor is turned on in each step.
   * @param off_time The duration that the motor is turned off in each step.
   */
  void attachMotor(int motor_pos_pin, int motor_neg_pin, int on_time = 50, int off_time = 70);

  /**
   * @param sw_pos_pin The GPIO pin at which the positive side of the edge switch is connected.
   * @param sw_neg_pin The GPIO pin at which the negative side of the edge switch is connected.
   */
  void attachSwitch(int sw_pos_pin, int sw_neg_pin);

  /**
   * Returns whether the cover touches the edge or not.
   */
  bool isOnEdge();

  /**
   * Moves the motor some steps counterclockwise.
   * 
   * @param steps The amount of steps to move the cover.
   * @returns A boolean indicating whether the cover hit the edge.
   */
  bool stepPositive(int steps = 1);

  /**
   * Moves the motor some steps clockwise.
   * 
   * @param steps The amount of steps to move the cover.
   * @returns A boolean indicating whether the cover hit the edge.
   */
  bool stepNegative(int steps = 1);

protected:
  /**
   * Sets the motor to rotate positively.
   */
  void rotatePositive();

  /**
   * Sets the motor to rotate negatively.
   */
  void rotateNegative();

  /**
   * Sets the motor to rotate towards a given direction.
   * 
   * @param dir True for positive rotation, false for negative.
   */
  void rotate(bool dir);

   /**
    * Stops the rotation of the motor.
    */
  void stop();

private:

  int pos_pin, neg_pin;
  int sw_pos_pin, sw_neg_pin;

  int on_time, off_time;

  /** Which edge the cover has hit. 1 is the positive edge, -1 is the negative edge, and 0 is none. */
  int hit_edge = 0;

  /** The time at which the cover last hit the edge */
  int last_edge_time = 0;
  
  /** Called when the edge switch is enabled. */
  static void ISR();
};

extern Cover cover;

#endif
