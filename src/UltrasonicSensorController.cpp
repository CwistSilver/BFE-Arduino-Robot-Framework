#include "UltrasonicSensorController.h"

UltrasonicSensorController *UltrasonicSensorControllerInstance;

UltrasonicSensorController::UltrasonicSensorController(int echo, int trig)
{
  _echo = echo;
  _trig = trig;
  UltrasonicSensorControllerInstance = this;
}

void UltrasonicSensorController::setup()
{
  pinMode(_echo, INPUT);
  pinMode(_trig, OUTPUT);
}

unsigned long UltrasonicSensorController::getDistance()
{
  digitalWrite(_trig, 1);
  delay(10);
  digitalWrite(_trig, 0);
  unsigned long duration = pulseIn(_echo, 1);
  unsigned long distance = duration * 0.034 / 2;
  return distance;
}
