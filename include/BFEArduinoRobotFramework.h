/**
 * @file BFEArduinoRobotFramework.h
 * @brief Framework for controlling a robot using Arduino.
 *
 * This header file provides the necessary declarations for the BFEArduinoRobotFramework. It integrates
 * motor control, ultrasonic distance sensing, and servo motor control into a single framework designed
 * for robotic projects. The framework is built upon several controller classes that abstract the
 * functionality of the respective hardware components.
 *
 * The framework assumes a specific hardware configuration and provides a high-level interface for
 * interacting with the different components of the robot. This includes moving forwards and backwards,
 * turning, measuring distance to obstacles, and adjusting servo positions.
 */

#ifndef BFEArduinoRobotFramework_h
#define BFEArduinoRobotFramework_h

#include "MotorController.h"
#include "UltrasonicSensorController.h"
#include "ServoController.h"

extern ServoController servoController;
extern UltrasonicSensorController sensorController;
extern MotorController motorController;

/**
 * Initializes all components of the robot, including serial communication and the individual controllers
 * for motors, ultrasonic sensors, and servos. This function should be called once in the Arduino sketch's
 * setup function to ensure all hardware components are correctly initialized before use.
 */
extern void arduinoSetup();

#endif // BFEArduinoRobotFramework_h
