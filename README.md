# BFE-Arduino-Robot-Framework
[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/FlorianNoeverGOB/BFE-Arduino-Robot-Framework/blob/master/README.md)
[![de](https://img.shields.io/badge/lang-de-green.svg)](https://github.com/FlorianNoeverGOB/BFE-Arduino-Robot-Framework/blob/master/README.de.md)

Framework for the BFE Arduino Robots

## Documentation

### Public Functions
`arduinoSetup()` - Initializes the other classes and sets the associated pins.

### Classes
There are 3 classes that are publicly available:
- `motorController` - For doing actions with the Arduino's motors
- `servoController` - For turning the Arduino's Servo
- `sensorController` - For measuring the distance in which the Sensor is facing

### MotorController
Controls the movement of the robot using its motor drivers.

motorController has the following Functions:
- `void setup()` - Initializes the motor controller by setting up pin modes and attaching interrupts for the speed sensors. **Gets called automatically by the Framework**

<br/>

- `void setDirection(Direction direction)` - Sets the direction in which the robot drives.
  - *`direction`* - Desired direction. **(Possible values: FORWARD, BACKWARD, NONE)**

<br/>

- `void setSpeed(int speed)` - Sets the speed of the robot.
  - *`speed`* - Desired speed value.

<br/>

- `void stop()` - Commands the robot to stop all motor activity immediately.

<br/>

- `void leftTurn(int degrees, int speed = 150)` - Turns the robot left by a specified number of degrees at a certain speed.
  - *`degrees`* - The degrees by which to turn left.
  - *`speed`* - The speed at which to turn left. **Can be left out, default is 150**

<br/>

- `void rightTurn(int degrees, int speed = 150)` - Turns the robot right by a specified number of degrees at a certain speed.
  - *`degrees`* - The degrees by which to turn right.
  - *`speed`* - The speed at which to turn right. **Can be left out, default is 150**

<br/>

- `void drive()` - Updates the speed and direction of the motors. **Has to be called regularly to drive**

### ServoController
Manages a servo motor's operations, including angle adjustments.

servoController has the following Functions:
- `void setup()` - Attaches the servo to its designated pin and sets an initial angle of 90 degrees. **Gets called automatically by the Framework**

<br/>

- `void setAngle(int angle = 90)` - Sets the servo to a specified angle.
  - *`angle`* - The angle to which to set the Servo to. (0° = Left, 90° = Front, 180° = Right). **Can be left out, default is 90°**

### SensorController
Manages distance measurement using an ultrasonic sensor.

sensorController has the following Functions:
- `void setup()` - Attaches the sensor to its designated pins. **Gets called automatically by the Framework**

<br/>

- `unsigned long getDistance()` - Measures the distance to an object in front of the ultrasonic sensor. Returns the measured distance as an unsigned long. **unsigned long = large positive only number**

## Full API Documentation
The full API-Documentation can be found here: [API Documentation](https://CwistSilver.github.io/BFE-Arduino-Robot-Framework/index.html)
