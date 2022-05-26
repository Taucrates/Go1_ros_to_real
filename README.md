# Introduction
This package is a modification of the official packages of unitree. Is completely functional, and is able to control the robot sending Twist messages to the topic /cmd_vel.

## Packages:

Basic message function: `unitree_legged_msgs`

Software development kit by unitree: `unitree_legged_sdk`

The interface between ROS and real robot: `unitree_legged_real`

## Environment
Is recommended to run this package in Ubuntu 18.04 and ROS melodic environment.

# Dependencies
* lcm 1.4.0

# Installation
Just have to clone the repository in your workspace:

`cd ~/catkin_ws/src

git clone https://github.com/Taucrates/Go1_ros_to_real.git

cd ..

catkin_make`

# Run the package
You can control your real Go1 robot from ROS by this package.

Before you run expamle program, please run command

```
roslaunch unitree_legged_real real.launch ctrl_level:=highlevel
```
or
```
roslaunch unitree_legged_real real.launch ctrl_level:=lowlevel
```

It depends which control mode you want to use.

Then, if you want to run high-level control mode, you can run example_walk node like this
```
rosrun unitree_legged_real example_walk
```

If you want to run low-level control mode, you can run example_position program node like this
```
rosrun unitree_legged_real example_postion
```

You can also run the node state_sub to subscribe the feedback information from Go1 robot
```
rosrun unitree_legged_real state_sub
```

And before you do the low-level control, please press L2+A to sit the robot down and then press L1+L2+start to make the robot into
mode in which you can do joint-level control, finally make sure you hang the robot up before you run low-level control.





