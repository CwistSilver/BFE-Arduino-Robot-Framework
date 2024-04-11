#include "Arduino.h"
#include "ServoController.h"
#include "BFEArduinoRobotFramework.h"
#include <Servo.h>

ServoController *ServoControllerInstance;

ServoController::ServoController(int pin)
{
  _pin = pin;
  ServoControllerInstance = this;
}

void ServoController::setup()
{
  _servo.attach(_pin);
  _servo.write(90);
}

void ServoController::setAngle(int angle)
{
  _servo.write(constrain(angle, 0, 180));
  delay(1000);
}
