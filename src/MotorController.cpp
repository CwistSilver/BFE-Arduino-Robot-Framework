#include "Arduino.h"
#include "Print.h"
#include "MotorController.h"

MotorController *motorControllerInstance;

bool debugShowTurn = false;
bool debugShowWheelWait = false;
bool debugShowMotorSpeed = false;
bool debugShowSpeedSensor = false;
bool debugShowSpeedError = false;

MotorController::MotorController(int motorLeftPin1, int motorLeftPin2, int motorRightPin1, int motorRightPin2, int speedSensorLeft, int speedSensorRight, int enA, int enB)
{
  _motorLeftPin1 = motorLeftPin1;
  _motorLeftPin2 = motorLeftPin2;
  _motorRightPin1 = motorRightPin1;
  _motorRightPin2 = motorRightPin2;
  _speedSensorLeftPin = speedSensorLeft;
  _speedSensorRightPin = speedSensorRight;
  _enA = enA;
  _enB = enB;
  _maxHoles = 20;
  _maxWheelTurnPerSecond = 5.0;
  motorControllerInstance = this;
}

void MotorController::setup()
{
  pinMode(_motorLeftPin1, OUTPUT);
  pinMode(_motorLeftPin2, OUTPUT);
  pinMode(_motorRightPin1, OUTPUT);
  pinMode(_motorRightPin2, OUTPUT);

  pinMode(_speedSensorLeftPin, INPUT_PULLUP);
  pinMode(_speedSensorRightPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(_speedSensorLeftPin), _speedCounterLeft_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(_speedSensorRightPin), _speedCounterRight_ISR, FALLING);

  _leftMotorSpeed = 0;
  _rightMotorSpeed = 0;
  _direction = NONE;
  _baseSpeed = 150;
  _speedError = 0;
}

void MotorController::setDirection(Direction direction)
{
  if (direction == NONE)
  {
    _stopLeftWheel();
    _stopRightWheel();
  }
  _direction = direction;
}

void MotorController::setSpeed(int speed)
{
  _baseSpeed = abs(speed);
}

void MotorController::_stop()
{
  setDirection(NONE);
}

void MotorController::leftTurn(int degrees, int speed)
{
  _turn(-degrees, speed);
}

void MotorController::rightTurn(int degrees, int speed)
{
  _turn(degrees, speed);
}

void MotorController::_turn(int degrees, int speed)
{
  if (speed == 0)
  {
    _stop();
    return;
  }

  if (degrees == 0)
    return;

  bool isLeftTurn = degrees < 0;

  degrees = abs(degrees);
  degrees = constrain(degrees, 0, 360);
  float rotationInPercent = degrees / 360.0;
  int fullRotation = _maxHoles * 2;
  int neededHoles = round(fullRotation * rotationInPercent);

  if (debugShowTurn)
  {
    Serial.println(isLeftTurn ? "Start Left Turn" : "Start Right Turn");
    Serial.print("Needed Holes: ");
    Serial.println(neededHoles);
  }

  _stop();

  int leftWheelSpeed = isLeftTurn ? -speed : speed;
  int rightWheelSpeed = isLeftTurn ? speed : -speed;
  _setSpeedLeftWheel(leftWheelSpeed);
  _setSpeedRightWheel(rightWheelSpeed);

  int curSpeedCounterLeft = _speedSensorLeftCount;
  int curSpeedCounterRight = _speedSensorRightCount;
  _waitForWheelsHolesCount(neededHoles, curSpeedCounterLeft, neededHoles, curSpeedCounterRight);

  if (debugShowTurn)
    Serial.println(isLeftTurn ? "End Left Turn" : "End Right Turn");
}

void MotorController::_waitForLeftWheelHolesCount(int numberHoles, int currentNumberHoles)
{
  bool leftReady = false;
  while (!leftReady)
  {
    int speedSensorChangedCountLeft = _speedSensorLeftCount - currentNumberHoles;
    if (debugShowWheelWait)
    {
      Serial.print("Left Wheel Count: ");
      Serial.println(speedSensorChangedCountLeft);
    }
    if (speedSensorChangedCountLeft >= numberHoles)
    {
      leftReady = true;
      if (debugShowWheelWait)
        Serial.println("Left Wheel Ready");
    }
  }
}

void MotorController::_waitForRightWheelHolesCount(int numberHoles, int currentNumberHoles)
{
  bool rightReady = false;
  while (!rightReady)
  {
    int speedSensorChangedCountRight = _speedSensorRightCount - currentNumberHoles;
    if (debugShowWheelWait)
    {
      Serial.print("Right Wheel Count: ");
      Serial.println(speedSensorChangedCountRight);
    }
    if (speedSensorChangedCountRight >= numberHoles)
    {
      rightReady = true;
      if (debugShowWheelWait)
        Serial.println("Right Wheel Ready");
    }
  }
}

void MotorController::_waitForWheelsHolesCount(int numberHolesLeft, int currentNumberHolesLeft, int numberHolesRight, int currentNumberHolesRight)
{
  bool leftReady = false;
  bool rightReady = false;
  while (!leftReady || !rightReady)
  {
    int speedSensorChangedCountLeft = _speedSensorLeftCount - currentNumberHolesLeft;
    int speedSensorChangedCountRight = _speedSensorRightCount - currentNumberHolesRight;
    if (debugShowWheelWait)
    {
      Serial.print("Left Wheel Count: ");
      Serial.print(speedSensorChangedCountLeft);
      Serial.print(" | Right Wheel Count: ");
      Serial.println(speedSensorChangedCountRight);
    }
    if (!leftReady && speedSensorChangedCountLeft >= numberHolesLeft)
    {
      _stopLeftWheel();
      leftReady = true;
      if (debugShowWheelWait)
        Serial.println("Left Wheel Ready");
    }

    if (!rightReady && speedSensorChangedCountRight >= numberHolesRight)
    {
      _stopRightWheel();
      rightReady = true;
      if (debugShowWheelWait)
        Serial.println("Right Wheel Ready");
    }
  }
}

void MotorController::_stopLeftWheel()
{
  digitalWrite(_motorLeftPin1, 0);
  digitalWrite(_motorLeftPin2, 0);
  analogWrite(_enA, 0);
}

void MotorController::_stopRightWheel()
{
  digitalWrite(_motorRightPin1, 0);
  digitalWrite(_motorRightPin2, 0);
  analogWrite(_enB, 0);
}

void MotorController::_turnLeftWheel(Direction direction)
{
  if (direction == FORWARD)
  {
    digitalWrite(_motorLeftPin1, 1);
    digitalWrite(_motorLeftPin2, 0);
  }
  else if (direction == BACKWARD)
  {
    digitalWrite(_motorLeftPin1, 0);
    digitalWrite(_motorLeftPin2, 1);
  }
  else
    _stopLeftWheel();
}

void MotorController::_turnRightWheel(Direction direction)
{
  if (direction == FORWARD)
  {
    digitalWrite(_motorRightPin1, 1);
    digitalWrite(_motorRightPin2, 0);
  }
  else if (direction == BACKWARD)
  {
    digitalWrite(_motorRightPin1, 0);
    digitalWrite(_motorRightPin2, 1);
  }
  else
    _stopRightWheel();
}

void MotorController::_setSpeedLeftWheel(int speed)
{
  Direction direction = static_cast<Direction>(constrain(speed, -1, 1));
  _turnLeftWheel(direction);
  analogWrite(_enA, constrain(abs(speed), 0, 255));
}

void MotorController::_setSpeedRightWheel(int speed)
{
  Direction direction = static_cast<Direction>(constrain(speed, -1, 1));
  _turnRightWheel(direction);
  analogWrite(_enB, constrain(abs(speed), 0, 255));
}

void MotorController::drive()
{
  int curSpeedCounterLeft = _speedSensorLeftCount;
  int curSpeedCounterRight = _speedSensorRightCount;

  _calcSpeedError();

  _leftMotorSpeed = constrain(_baseSpeed - _speedError, 100, 255) * _direction;
  _rightMotorSpeed = constrain(_baseSpeed + _speedError, 100, 255) * _direction;

  if (debugShowMotorSpeed)
  {
    Serial.print("left: ");
    Serial.print(_leftMotorSpeed);
    Serial.print(" counter: ");
    Serial.print(curSpeedCounterLeft);

    Serial.print(" | right: ");
    Serial.print(_rightMotorSpeed);
    Serial.print(" counter: ");
    Serial.print(curSpeedCounterRight);

    Serial.print(" | speedError: ");
    Serial.println(_speedError);
  }

  _setSpeedLeftWheel(_leftMotorSpeed);
  _setSpeedRightWheel(_rightMotorSpeed);
}

void MotorController::_calcSpeedError()
{
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - _previousTime) / 1000.0;
  if (deltaTime == 0)
    return;
  _previousTime = currentTime;

  int leftCountDelta = _speedSensorLeftCount - _speedSensorLeftCountPrevious;
  int rightCountDelta = _speedSensorRightCount - _speedSensorRightCountPrevious;

  float maxHoles = static_cast<float>(_maxHoles);
  float wheelSpeedLeft = leftCountDelta / maxHoles / deltaTime;
  float wheelSpeedRight = rightCountDelta / maxHoles / deltaTime;

  _speedSensorLeftCountPrevious = _speedSensorLeftCount;
  _speedSensorRightCountPrevious = _speedSensorRightCount;

  float wheelSpeedPercentLeft = wheelSpeedLeft / _maxWheelTurnPerSecond;
  float wheelSpeedPercentRight = wheelSpeedRight / _maxWheelTurnPerSecond;

  float rawSpeedErrorPercent = wheelSpeedPercentLeft - wheelSpeedPercentRight;
  float rawSpeedError = rawSpeedErrorPercent * 255 * 2;
  _speedError += rawSpeedError * deltaTime;

  if (debugShowSpeedError)
  {
    Serial.print(" | delta: ");
    Serial.print(deltaTime);

    Serial.print(" | left speed: ");
    Serial.print(wheelSpeedLeft);

    Serial.print(" | right speed: ");
    Serial.print(wheelSpeedRight);

    Serial.print(" | percent error: ");
    Serial.print(rawSpeedErrorPercent);
    Serial.print(" | raw error: ");
    Serial.print(rawSpeedError);
    Serial.print(" | speed error: ");
    Serial.println(_speedError);
  }
}

void MotorController::_speedCounterLeft_ISR()
{
  motorControllerInstance->_speedSensorLeftCount++;
  if (debugShowSpeedSensor)
  {
    Serial.print("_speedCounterLeft_ISR: ");
    Serial.println(motorControllerInstance->_speedSensorLeftCount);
  }
}

void MotorController::_speedCounterRight_ISR()
{
  motorControllerInstance->_speedSensorRightCount++;
  if (debugShowSpeedSensor)
  {
    Serial.print("_speedCounterRight_ISR: ");
    Serial.println(motorControllerInstance->_speedSensorRightCount);
  }
}
