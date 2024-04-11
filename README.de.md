# BFE-Arduino-Robot-Framework
[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/FlorianNoeverGOB/BFE-Arduino-Robot-Framework/blob/master/README.md)
[![de](https://img.shields.io/badge/lang-de-green.svg)](https://github.com/FlorianNoeverGOB/BFE-Arduino-Robot-Framework/blob/master/README.de.md)

Framework für die BFE Arduino Roboter

## Dokumentation

### Öffentliche Funktionen
`arduinoSetup()` - Initialisiert die anderen Klassen und setzt die zugehörigen Pins.

### Klassen
Es gibt 3 Klassen, die öffentlich zugänglich sind:

- `motorController` - Für Aktionen mit den Motoren des Arduino
- `servoController` - Zum Drehen des Arduino-Servos
- `sensorController` - Zum Messen der Entfernung, in die der Sensor zeigt

### MotorController
Steuerung der Bewegung des Roboters mit seinen Motortreibern.

motorController hat die folgenden Funktionen:

`void setup()` - Initialisiert den Motorcontroller, indem Pin-Modi eingestellt und Unterbrechungen für die Geschwindigkeitssensoren angehängt werden. **Wird automatisch vom Framework aufgerufen**

<br/>

- `void setDirection(Direction direction)` - Legt die Richtung fest, in die der Roboter fährt.
  - *`speed`* - Gewünschte Richtung. **(Mögliche Werte: FORWARD, BACKWARD, NONE)**

<br/>

- `void driveBackward(int speed = 150)` - Legt die Geschwindigkeit des Roboters fest.
  - *`speed`* - Gewünschter Geschwindigkeitswert.

<br/>

- `void stop()` - Befiehlt dem Roboter, alle Motoraktivitäten sofort zu stoppen.

<br/>

- `void leftTurn(int degrees, int speed = 150)` - Dreht den Roboter um eine bestimmte Anzahl von Grad nach links bei einer bestimmten Geschwindigkeit.
  - *`degrees`* - Die Gradzahl, um die nach links gedreht werden soll.
  - *`speed`* - Die Geschwindigkeit, mit der nach links gedreht werden soll. **Kann weggelassen werden, Standard ist 150**

<br/>

- `void rightTurn(int degrees, int speed = 150)` - Dreht den Roboter um eine bestimmte Anzahl von Grad nach rechts bei einer bestimmten Geschwindigkeit.
  - *`degrees`* - Die Gradzahl, um die nach rechts gedreht werden soll.
  - *`speed`* - Die Geschwindigkeit, mit der nach rechts gedreht werden soll. **Kann weggelassen werden, Standard ist 150**

<br/>

`void drive()` - Aktualisiert die Geschwindigkeit und Richtung der Motoren. **Muss regelmäßig aufgerufen werden, um zu fahren**

### ServoController
Verwaltet die Operationen eines Servomotors, einschließlich Winkelverstellungen.

servoController hat die folgenden Funktionen:

- `void setup()` - Verbindet den Servo mit seinem festgelegten Pin und setzt einen anfänglichen Winkel von 90 Grad. **Wird automatisch vom Framework aufgerufen**

<br/>

- `void setAngle(int angle)` - Stellt den Servo auf einen bestimmten Winkel ein.
  - *`angle`* - Der Winkel, auf den der Servo eingestellt werden soll. (0° = Links, 90° = Vorne, 180° = Rechts). **Kann weggelassen werden, Standard ist 90°**

### SensorController
Verwaltet die Entfernungsmessung mit einem Ultraschallsensor.

sensorController hat die folgenden Funktionen:

- `void setup()` - Verbindet den Sensor mit seinen festgelegten Pins. **Wird automatisch vom Framework aufgerufen**

<br/>

- `unsigned long getDistance()` - Misst die Entfernung zu einem Objekt vor dem Ultraschallsensor. Gibt die gemessene Entfernung als unsigned long zurück. **unsigned long = große, nur positive Zahl**
- 
## Vollständige API-Dokumentation
Die vollständige API-Dokumentation ist hier zu finden: [API Documentation](https://CwistSilver.github.io/BFE-Arduino-Robot-Framework/index.html)
