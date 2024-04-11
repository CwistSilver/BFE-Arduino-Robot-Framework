#ifndef UltrasonicSensorController_h
#define UltrasonicSensorController_h

#include "Arduino.h"

/**
 * @file UltrasonicSensorController.h
 * @class UltrasonicSensorController
 * @brief Manages distance measurement using an ultrasonic sensor.
 *
 * This class facilitates the use of an ultrasonic sensor for distance measurement on the Arduino.
 * It provides an interface to initialize the sensor and to calculate the distance to an object by emitting
 * ultrasonic waves and measuring the time it takes for the echo to return.
 *
 * @note The setup() method should be called during the Arduino sketch's setup phase to correctly initialize
 * the sensor pins.
 *
 * @param echo The digital pin number connected to the echo pin of the ultrasonic sensor.
 * @param trig The digital pin number connected to the trigger pin of the ultrasonic sensor.
 */
class UltrasonicSensorController
{
public:
  /**
   * Constructor for creating an UltrasonicSensorController.
   * Initializes the controller with specified pins for trigger and echo.
   * @param echo Digital pin connected to the sensor's echo pin.
   * @param trig Digital pin connected to the sensor's trigger pin.
   */
  UltrasonicSensorController(int echo, int trig);

  /**
   * Sets up the digital pins connected to the ultrasonic sensor as input (echo) and output (trig) respectively.
   * This method should be called once in the setup() function of the Arduino sketch.
   */
  void setup();

  /**
   * Measures the distance to an object in front of the ultrasonic sensor.
   * This function triggers an ultrasonic pulse and measures the time taken for the echo to return,
   * calculating the distance based on the speed of sound.
   *
   * @return The measured distance in centimeters.
   */
  unsigned long getDistance();

private:
  int _echo, _trig; ///< Pin numbers for echo and trig pins of the ultrasonic sensor
};

#endif
