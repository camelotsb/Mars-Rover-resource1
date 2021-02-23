# Software

### Contents
1. [Software Modules](#software-modules)
2. [Simplified Diagram Flowchart](#simplified)
3. [Dev/Build Tool Information](#dev-build)
4. [Installing the software stack on the Jetson TX2](#installation)

<a name="software-modules"/>

## 1. Software Modules

ROS uses a subscriber/publisher method of functioning where nodes process data, and publishes it to topics, which other nodes subscribe to. Because of this, ROS applications can be modeled as seen in the flowchart below. The issue with this model is that the nodes and topics within the programme don’t correspond neatly with actual files, so we’ll explain them here. 
All of the source code that runs on the Jetson TX2 is in Hardware/catkin_ws/src

The nodes encapsulated as /d400 and /t265 in the flow chart, in addition to /t265_to_d400, are implemented by intel librealsense. This package is in Hardware/catkin_ws/src/realsense-ros/camera. The material corresponding to the occupancy map is in /Hardware/catkin_ws/src/realsense-ros/occupancy. /apriltag_ros_continuous node and /tag_detections are the product of the april_tag ros library and can be found in Hardware/catkin_ws/src/apriltag_ros. /navi_node is from Hardware/catkin_ws/src/realsense-ros/navi

For more information about their functionality, reference the [Final Report](https://github.com/BostonUniversitySeniorDesign/20-28-MarsRover/blob/master/Reports%20and%20Presentations/EC464%20Final%20Report.docx).

<a name="simplified"/>

## 2. Simplified Diagram Flowchart
![ROS Simplified Node Diagram](https://github.com/BostonUniversitySeniorDesign/20-28-MarsRover/blob/master/README_images/ros%20node%20graph%20simplified.jpg)

For a more in depth diagram of the ROS rqt, [click here](https://github.com/BostonUniversitySeniorDesign/20-28-MarsRover/blob/master/README_images/rosgraph.png)


<a name="dev-build"/>

## 3. Dev/Build tool information
* Intel Realsense SDK 2.0
* Python 2.7
* ROS Melodic
* JetPack SDK 4.3
* OpenCV 4.0

<a name="installation"/>

## 4. Installing the software stack on the Jetson TX2
Key files from our Jetson TX2 were not pushed to the repo before the evacuation order was issued. This issue is addressed in our directions. These directions are for installing on a new Jetson TX2, not the one used for the project. Don't flash the old one. Our hope is that the relevant materials will be pushed hear at a later date.

### NVIDIA Jetson TX2

* First, obtain the entire contents of the `~/catkin_ws directory` as well as `~/.bashrc` file by logging into our Jetson using the credentials team28:Marsrover28.  

* Install Ubuntu 18.04 OS on a computer.

- Install the [NVIDIA SDK Manager](https://developer.nvidia.com/nvidia-sdk-manager) on your host computer.

* Follow the SDK Manager Instructions to Flash your new Jetson TX2. Be sure to include the CUDA packages.

* Install [librealsense](https://github.com/jetsonhacks/installRealSenseSDK).

* Install [ROS Melodic](https://github.com/jetsonhacks/installROS).

* (Optional) Install the [RealSense ROS wrapper](https://github.com/jetsonhacks/installRealSenseROS). It is perferable to use the one in this repo as it has been modified to work better.

* Run the `setupCatkinWorkspace.sh` script found in installROS repo.

* Move the `~/catkin_ws/src` directory you obtainted from the old Jetson into your new catkin_ws directory.

* Reference the old `~/.bashrc` file to set the proper environment variables in the `~/.bashrc` file on your new machine.

* Navigate to `catkin_ws/src/occupancy/cameras.launch` and modify the serial numbers to that of your t265 and d415 cameras

* In the catkin_ws directory, run `catkin_make` 

### Arduino

* On the Jetson, install the [Arduino IDE](https://www.arduino.cc/en/main/software) for Linux ARM 64.

* Install rosserial_arduino with the command `sudo apt-get install ros-melodic-rosserial-arduino` and 
`sudo apt-get install ros-melodic-rosserial`

* Add your user to the dialout group so you can push code onto the Arduino by running `sudo usermod -a -G dialout <username>`

* Now, follow the instructions starting [here](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup#Install_ros_lib_into_the_Arduino_Environment) for using this package in the Arduino IDE.

* Lastly, use open the `ROS_Ardy.ino` file in the Arduino IDE and run it on your Arduino
