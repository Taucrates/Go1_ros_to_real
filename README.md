# Introduction
This package is a modification of the official packages of unitree. Is completely functional, and is able to control the movement (x, y, yaw) of the robot Go1, sending Twist messages to the topic /cmd_vel. The package include a [keyboard controller](https://github.com/methylDragon/teleop_twist_keyboard_cpp) to operate the Go1.

## Packages:

Basic message function: `unitree_legged_msgs`

Software development kit by [unitree](https://github.com/unitreerobotics/unitree_legged_sdk) (modified): `unitree_legged_sdk`

The interface between ROS and real robot: `unitree_legged_real`

## Environment
Is recommended to run this package in Ubuntu 18.04 and ROS melodic environment.

# Dependencies
* [Boost](http://www.boost.org) (version 1.5.4 or higher)
* [CMake](http://www.cmake.org) (version 2.8.3 or higher)
* [LCM](https://github.com/lcm-proj/lcm/releases) (version 1.4.0 or higher)
* [g++](https://gcc.gnu.org/) (version 8.3.0 or higher)

LCM installation:
```bash
cd lcm-x.x.x
mkdir build
cd build
cmake ../
make
sudo make install
```

# Installation
Just have to clone the repository in your workspace:
```
cd ~/catkin_ws/src
git clone https://github.com/Taucrates/Go1_ros_to_real.git
cd ..
catkin_make
```

# Run the package
The first step is the execution of the node that enables communication between your machine and the Go1:

```
roslaunch unitree_legged_real real.launch
```

In that place you should be able to control the robot sending Twist messages to the topic /cmd_vel.
In the case you want to control the robot using the keyboard (use a numeric keyboard) just have to run:

```
rosrun teleop_twist_keyboard_cpp teleop_twist_keyboard
```





