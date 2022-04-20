#!/bin/bash
echo "Sourcing files"
source /opt/ros/noetic/setup.bash
source /home/ubuntu/lidar_ws/devel/setup.bash
echo "Converting Filesystem"
dos2unix /home/ubuntu/lidar_ws/src/goalFinder/scripts/goalFinder.py
echo "Starting ROS"
roslaunch /home/ubuntu/test.launch
