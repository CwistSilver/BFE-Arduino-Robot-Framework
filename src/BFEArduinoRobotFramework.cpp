/**
 * @file BFEArduinoRobotFramework.cpp
 * @brief Implementation of the BFEArduinoRobotFramework.
 *
 * This file contains the implementation of the BFEArduinoRobotFramework's setup function. The function
 * initializes serial communication and sets up all connected hardware components, preparing the robot for
 * operation. It includes initializing motor controllers, ultrasonic sensor controllers, and servo controllers
 * with predefined pin configurations. After setup, the robot is ready for commands to move, sense, and act
 * upon its environment.
 */

#include "BFEArduinoRobotFramework.h"

// Motor Left
const int motorLeftPin1 = 11; // Pin number for the left motor's first input
const int motorLeftPin2 = 12; // Pin number for the left motor's second input
const int enA = 6; // PWM pin number for controlling the speed of the left motor

// Motor Right
const int motorRightPin1 = 8; // Pin number for the right motor's first input
const int motorRightPin2 = 10; // Pin number for the right motor's second input
const int enB = 5; // PWM pin number for controlling the speed of the right motor

// Speed Sensor
const int speedSensorLeft = 2; // Pin number for the left speed sensor
const int speedSensorRight = 3; // Pin number for the right speed sensor

// Ultrasonic Sensor
const int trig = 4; // Pin number connected to the trigger pin of the ultrasonic sensor
const int echo = 9; // Pin number connected to the echo pin of the ultrasonic sensor

// Servo Motor
const int servoPin = 7; // Pin number where the servo is connected

// Classes
ServoController servoController(servoPin);
UltrasonicSensorController sensorController(echo, trig);
MotorController motorController(motorLeftPin1, motorLeftPin2, motorRightPin1, motorRightPin2, speedSensorLeft, speedSensorRight, enA, enB);

void arduinoSetup()
{
    Serial.begin(9600);
    servoController.setup();
    sensorController.setup();
    motorController.setup();
    delay(2000);
}