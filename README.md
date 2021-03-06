BrickPi Lua Code (binding of BrickPi C)
=======================================

This repository is a Lua binding library of BrickPi C code. It allows
to program BrickPi using Lua programming language, and it is pretty cool.

Installation
------------

This sofware needs Lua 5.2, which could be installed into raspbian wheezy
by executing:

- sudo apt-get install liblua5.2-dev
- sudo apt-get install lua5.2

Installation is done by:

- make
- make install

Reference
---------

In Lua, the library is loaded as a package:

```Lua
brickpi = require "brickpi"
```

The brickpi package has the following functions:

- `boolean,error_message = brickpi.setup()`: initializes the BrickPi
  C environment. Returns true if everything is ok, otherwise it
  returns false and an error message string.

- `brickpi.motorEnable(number, number, ...)`: initializes the given
  port numbers as motor ports.

- `brickpi.sensorType(port_number, type_number)`: initializes the
  given port number as sensor of the given type.

- `boolean,error_message = brickpi.setupSensors()`: after motors
  and sensors initialization, this function setup the configuration.
  It returns true if everything is ok, otherwise it returns false
  and an error message string.

- `brickpi.sleep(seconds)`: sleeps the given number of seconds. The
  number is a double, so it is possible to sleep a fraction of a
  second.

- `boolean,error_message = brickpi.update()`: this function updates
  the BrickPi C environment, providing motor update and sensor
  read.

- `brickpi.motorSpeed(port_number, port_number, ..., speed_number)`:
  sets the speed of the given list of motor ports to the given speed.
  The speed is a number between [-255,255].

- `speed_number = brickpi.motorSpeed(port_number)`: returns the speed
  set for the given motor port number.

- `brickpi.motorSteering(port1, port2, steer, power)`: sets the speed
  of two motors (port1 and port2) depending on the steer value (in
  range [-1,1]) and in the power value (in range [-1,1]). When steer=-1
  or steer=1 the robot will spin over its center, setting the speed
  of one motor to 255*power, and the other to -255*power. When steer=0,
  speed of both motors is set to 255*power. A negative power value
  will change the direction of the movement of motors.

- `value, value, ... = brickpi.sensorValue(port_number, port_number, ...)`:
  reads the value of the sensors at the given port numbers.

- `boolean,error_message = brickpi.setTimeout(number)`: initializes
  the BrickPi motors timeout, given in seconds. The  number is a double,
  so it is possible to give any fraction of a second. Returns true if
  everything is ok, otherwise it returns false plus an error message string.

The following port and sensor numbers are available:

- `brickpi.PORT_A`
- `brickpi.PORT_B`
- `brickpi.PORT_C`
- `brickpi.PORT_D`
- `brickpi.PORT_1`
- `brickpi.PORT_2`
- `brickpi.PORT_3`
- `brickpi.PORT_4`
- `brickpi.TYPE_MOTOR_PWM`
- `brickpi.TYPE_MOTOR_SPEED`
- `brickpi.TYPE_MOTOR_POSITION`
- `brickpi.TYPE_SENSOR_RAW`
- `brickpi.TYPE_SENSOR_LIGHT_OFF`
- `brickpi.TYPE_SENSOR_LIGHT_ON``
- `brickpi.TYPE_SENSOR_TOUCH`
- `brickpi.TYPE_SENSOR_ULTRASONIC_CONT`
- `brickpi.TYPE_SENSOR_ULTRASONIC_SS`
- `brickpi.TYPE_SENSOR_RCX_LIGHT`
- `brickpi.TYPE_SENSOR_COLOR_FULL`
- `brickpi.TYPE_SENSOR_COLOR_RED`
- `brickpi.TYPE_SENSOR_COLOR_GREEN`
- `brickpi.TYPE_SENSOR_COLOR_BLUE`
- `brickpi.TYPE_SENSOR_COLOR_NONE`
- `brickpi.TYPE_SENSOR_I2C`
- `brickpi.TYPE_SENSOR_I2C_9V`

BrickPi C
---------

More information on using C on the BrickPi can be found here:
http://www.dexterindustries.com/BrickPi/program-it/c/

BrickPi is a Raspberry Pi Board that connects LEGO MINDSTORMS
motors and sensors to the Raspberry Pi.

Examples are given under "SensorExamples" for using the different
sensors.

More information on hardware, firmware, and software can be found
here: http://www.dexterindustries.com/BrickPi
