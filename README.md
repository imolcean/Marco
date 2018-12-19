# Marco
Remotely controlled rover based on RaspberryPi


## Features

### CLI

You can control the rover by connecting to it via SSH and typing the commands directly.

### WebSocket

Most people would prefer to use a GUI. For that purpose, there is a WebSocket
interface that works with the same commands as the CLI. You can write your own client or just use
[MarcoWeb](https://github.com/imolcean/MarcoWeb) to control your rover.


## Dependencies

### Libconfig

http://www.hyperrealm.com/libconfig/

##### Installation
`apt-get install libconfig++-dev libconfig8-dev`



### Boost

- http://www.boost.org/doc/libs/1_60_0/doc/html/string_algo.html
- http://www.boost.org/doc/libs/1_62_0/doc/html/boost_asio.html

##### Installation
`apt-get install libboost-all-dev`


### BCM2835

http://www.airspayce.com/mikem/bcm2835/

##### Installation
- `wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.52.tar.gz`
- `tar zxvf bcm2835-1.52.tar.gz`
- `cd bcm2835-1.52`
- `./configure`
- `make`
- `sudo make check`
- `sudo make install`


### pi-blaster

https://github.com/sarfata/pi-blaster

##### Installation
- `sudo apt-get install autoconf`
- `git clone https://github.com/sarfata/pi-blaster.git`
- `cd pi-blaster`
- `./autogen.sh`
- `./configure`
- `make`
- `sudo make install`


## Commands

There are three commands
- `move`
- `stop`
- `action`

### Command `move`

Has the following form `move x y [t]`, where

- `x` X part of the move vector
- `y` Y part of the move vector
- `t` Time of execution. When it exceeds, the rover will stop. If this parameter is not specified or is set to zero,
the rover will continue executing the `move` until another command arrives.

*Example:*
`marco move 1 0 3000` The rover is going to move forward (360°) with the maximum speed for
three seconds or until another command arrives.

*Example:*
`marco move 0.5 -0.5 0` The rover is going to move forward and to the right (045°) with the half of its
maximum speed until another command arrives.

*Example:*
`marco move 0 0.1` The rover is going to turn to the left staying on its place (270°) with one tenth from its maximum
speed until another command arrives.

### Command `stop`

This command takes no parameters and is there to stop the rover immediately. It's equal to `move 0 0`. In both cases,
the rover will stop even if there was a `move` command issued previously with the execution time unequal zero.

*Example:*
`marco stop`

### Command `action`
*This command is reserved for different kind of actions that might be added in the future.*


## Control vector

Control vector is a 2D vector on the XY plane that denotes the direction of the rover's movement.
In this case, the X axis has its zero point at the center of the rover's body and is directed forward. The Y axis begins
at the same point and is directed to the left.

By a positive X component in the control vector, the rover will move forward, and by a negative backwards.
The Y component is treated in the same manner. By a positive Y, the rover will turn to the left, by a negative to the
right.

> Note: When X is set to zero and Y not, the rover will turn around one of its tracks, and not the center
> of its body.
