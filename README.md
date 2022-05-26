# Introduction
This package is a modification of the official packages of unitree. Is completely functional, and is able to control the robot sending Twist messages to the topic /cmd_vel.

## Packages:

Basic message function: `unitree_legged_msgs`

Software development kit by unitree (modified): `unitree_legged_sdk`

The interface between ROS and real robot: `unitree_legged_real`

## Environment
Is recommended to run this package in Ubuntu 18.04 and ROS melodic environment.

# Dependencies
* lcm 1.4.0

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





