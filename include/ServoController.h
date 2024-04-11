#ifndef ServoController_h
#define ServoController_h

#include "Arduino.h"
#include <Servo.h>

/**
 * @file ServoController.h
 * @class ServoController
 * @brief Manages a servo motor's operations, including setup and angle adjustments.
 *
 * This class encapsulates the functionality needed to control a servo motor attached to the Arduino.
 * It provides methods to initialize the servo and set its angle within the conventional range of 0 to 180 degrees.
 * The class is designed to be used in conjunction with the Arduino Servo library.
 *
 * @note The setup() method must be called in your sketch's setup() function to properly initialize the servo hardware.
 *
 * @param pin The digital pin number on the Arduino board that the servo is connected to.
 */
class ServoController
{
public:
  /**
   * Constructor for creating a ServoController.
   * Initializes the servo control on a specified pin.
   * @param pin Digital pin to which the servo is connected.
   */
  ServoController(int pin);

  /**
   * Attaches the servo to its designated pin and sets an initial angle of 90 degrees.
   * This method should be called once in the setup() function of your Arduino sketch.
   */
  void setup();

  /**
   * Sets the servo to a specified angle.
   * The input angle is constrained between 0 and 180 degrees to ensure safe operation.
   * After setting the angle, the function includes a delay to allow the servo to reach the specified position.
   *
   * @param angle Desired angle to set the servo. The angle is constrained between 0 and 180 degrees (default is 90°).
   */
  void setAngle(int angle = 90);

private:
  int _pin;     ///< Pin number where the servo is connected.
  Servo _servo; ///< Servo object used to control the motor.
};

#endif
