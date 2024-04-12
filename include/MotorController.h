#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"

/**
 * @file MotorController.h
 * @class MotorController
 * @brief Controls the movement of the robot using its motor drivers.
 *
 * This class provides an interface for controlling the robot equipped with left and right motors, including
 * functions for moving forward, backward, stopping, and turning. It utilizes encoder feedback to
 * maintain speed and direction accuracy.
 *
 * @note This class is designed to be used with Arduino-based controllers.
 *
 * @param motorLeftPin1 Digital pin number connected to the left motor's first input.
 * @param motorLeftPin2 Digital pin number connected to the left motor's second input.
 * @param motorRightPin1 Digital pin number connected to the right motor's first input.
 * @param motorRightPin2 Digital pin number connected to the right motor's second input.
 * @param speedSensorLeftPin Digital pin number for the left speed sensor.
 * @param speedSensorRightPin Digital pin number for the right speed sensor.
 * @param enA PWM pin number for controlling the speed of the left motor.
 * @param enB PWM pin number for controlling the speed of the right motor.
 */
class MotorController
{
public:
  /**
   * Constructor for creating a MotorController.
   * Initializes the motor control on the specified pins.
   * @param motorLeftPin1 Digital pin number connected to the left motor's first input.
   * @param motorLeftPin2 Digital pin number connected to the left motor's second input.
   * @param motorRightPin1 Digital pin number connected to the right motor's first input.
   * @param motorRightPin2 Digital pin number connected to the right motor's second input.
   * @param speedSensorLeftPin Digital pin number for the left speed sensor.
   * @param speedSensorRightPin Digital pin number for the right speed sensor.
   * @param enA PWM pin number for controlling the speed of the left motor.
   * @param enB PWM pin number for controlling the speed of the right motor.
   */
  MotorController(int motorLeftPin1, int motorLeftPin2, int motorRightPin1, int motorRightPin2, int speedSensorLeftPin, int speedSensorRightPin, int enA, int enB);

  /**
   * Direction of the robot's movement.
   * FORWARD indicates forward movement, BACKWARD indicates backward movement, and STOP indicates no movement.
   */
  enum Direction
  {
    FORWARD = 1,   /**< Indicates forward movement. */
    BACKWARD = -1, /**< Indicates backward movement. */
    NONE = 0       /**< Indicates no movement. */
  };

  /**
   * Initializes the motor controller by setting up pin modes and attaching interrupts for the speed sensors.
   */
  void setup();

  /**
   * Sets the direction in which the robot drives.
   * @param direction Desired direction.
   */
  void setDirection(Direction direction);

  /**
   * Sets the speed of the robot.
   * @param speed Desired speed value. Negative values reverse direction.
   */
  void setSpeed(int speed);

  /**
   * Turns the robot left by a specified number of degrees at a certain speed.
   * @param degrees Angle in degrees to turn.
   * @param speed Speed at which to turn (default = 150).
   */
  void leftTurn(int degrees, int speed = 150);
  /**
   * Turns the robot right by a specified number of degrees at a certain speed.
   * @param degrees Angle in degrees to turn.
   * @param speed Speed at which to turn (default = 150).
   */
  void rightTurn(int degrees, int speed = 150);

  /**
   * Updates the speed and direction of the motors based on encoder feedback and desired settings.
   * Should be called regularly to maintain accurate control.
   */
  void drive();

private:
  int _maxHoles;                                                        ///< Number of holes in the wheel encoder disk.
  float _maxWheelTurnPerSecond;                                         ///< Maximum speed of the wheel in turns per second.
  int _baseSpeed;                                                       ///< Base speed of the robot.
  Direction _direction;                                                 ///< Current direction of the robot.
  float _speedError;                                                    ///< Speed error of the robot while driving.
  int _motorLeftPin1, _motorLeftPin2, _motorRightPin1, _motorRightPin2; ///< Motor control pins.
  int _speedSensorLeftPin, _speedSensorRightPin;                        ///< Speed sensor pins.
  int _enA, _enB;                                                       ///< PWM pins for motor speed control.
  volatile int _speedSensorLeftCount, _speedSensorRightCount;           ///< Speed sensor hole counts.
  int _speedSensorLeftCountPrevious, _speedSensorRightCountPrevious;    ///< Previous speed sensor hole counts.
  int _leftMotorSpeed, _rightMotorSpeed;                                ///< Current motor speeds.
  unsigned long _previousTime;
  ///< Previous time for speed calculations.
  /**
   * Commands the robot to drive in the given direction (forward or backward) determined by the speed.
   * @param speed Desired speed value (default = 150). Negative values reverse direction.
   */
  void _drive(int speed = 150);
  /**
   * Commands the robot to stop all motor activity immediately.
   */
  void _stop();
  /**
   * Generic turn function. Positive degrees for right turns, negative for left.
   * @param degrees Angle in degrees to turn. Negative for left, positive for right.
   * @param speed Speed at which to turn (default = 150).
   */
  void _turn(int degrees, int speed = 150);
  /**
   * Stops the left wheel.
   */
  void _stopLeftWheel();
  /**
   * Stops the right wheel.
   */
  void _stopRightWheel();
  /**
   * Turns the left wheel in the specified direction.
   */
  void _turnLeftWheel(Direction direction);
  /**
   * Turns the right wheel in the specified direction.
   */
  void _turnRightWheel(Direction direction);
  /**
   * Waits for the left wheel to turn by a certain number of holes.
   */
  void _waitForLeftWheelHolesCount(int numberHoles, int currentNumberHoles);
  /**
   * Waits for the right wheel to turn by a certain number of holes.
   */
  void _waitForRightWheelHolesCount(int numberHoles, int currentNumberHoles);
  /**
   * Waits for both wheels to turn by a certain number of holes.
   */
  void _waitForWheelsHolesCount(int numberHolesLeft, int currentNumberHolesLeft, int numberHolesRight, int currentNumberHolesRight);
  /**
   * Sets the speed of the left wheel.
   */
  void _setSpeedLeftWheel(int speed);
  /**
   * Sets the speed of the right wheel.
   */
  void _setSpeedRightWheel(int speed);
  /**
   * Calculates the speed error of the robot.
   */
  void _calcSpeedError();

  /**
   * Interrupt service routine for the left speed sensor.
   */
  static void _speedCounterLeft_ISR();
  /**
   * Interrupt service routine for the right speed sensor.
   */
  static void _speedCounterRight_ISR();
};

#endif
