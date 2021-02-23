/**
**  Simple ROS Node
**/
#include <ros/ros.h>
#include <iostream>
#include <std_msgs/UInt16.h>
#include <apriltag_ros/AprilTagDetection.h>
#include <apriltag_ros/AprilTagDetectionArray.h>
//  Simple ROS Node

//#include <ros/ros.h>
#include <ctime>
#define Kp 35.0
#define Ki 13.0
#define Kd 0.01
float x;
float y;
float z;
std_msgs::UInt16 turn;
std_msgs::UInt16 go;



class Localiser
{
public:
  Localiser(ros::NodeHandle& nh)
  {
      	ar_sub_ = nh.subscribe<apriltag_ros::AprilTagDetectionArray>("tag_detections", 1,
     	&Localiser::camera_callback, this);
  }

  void camera_callback(const apriltag_ros::AprilTagDetectionArray::ConstPtr& msg)
  {
	//apriltag_ros::AprilTagDetection detecto = msg->detections.front();
	last_msg_ = msg;
	/*
	x = msg->detections[0].pose.pose.pose.position.x;
	y = msg->detections[0].pose.pose.pose.position.y;
	z = msg->detections[0].pose.pose.pose.position.z;
	*/
	//ROS_INFO_STREAM("%2.1f,%2.1f,%2.1f",x,y,z);
	//ROS_INFO_STREAM(last_msg_->detections[0].pose.pose.pose);
	if(last_msg_ != NULL && last_msg_->detections.size()>0){
		x = last_msg_->detections[0].pose.pose.pose.position.x;
	        y = last_msg_->detections[0].pose.pose.pose.position.y;
        	z = last_msg_->detections[0].pose.pose.pose.position.z;
	}
  }
ros::Subscriber ar_sub_;
apriltag_ros::AprilTagDetectionArrayConstPtr last_msg_;
};

void turnLeft(){
	if(turn.data<115){
		turn.data+=5;
	}
}

void turnRight(){
	if(turn.data>15)
		turn.data-=5;
}

int main(int argc, char* argv[])
{
  // This must be called before anything else ROS-related
 	ros::init(argc, argv, "navi_node");
	
	ros::NodeHandle nh;
	
	ROS_INFO("Node is running");
	
	Localiser localiser(nh);
	//ros::spin();
	//ros::Subscriber cam_data = nh.subscribe<apriltag_ros::AprilTagDetectionArray>("/tag_detections",1,camera_callback);
	turn.data = 50;
	ros::Publisher turning = nh.advertise<std_msgs::UInt16>("servo",100);
	ros::Publisher going = nh.advertise<std_msgs::UInt16>("esc",100);
	ros::Rate loop_rate(10);
	//float twiddle = 0;
	int cooldown=0;
	float dt = 0;
	float previous_error = 0.0;
	float integral = 0.0;
	float output, error;
	float setpoint = 0.0;
	float derivative = 0.0;
	while(ros::ok()){
		//if(( (int)time(NULL)) %2==0){
			error = setpoint - x;
	       		integral = integral + error * dt;
			derivative = (error - previous_error) / dt;
			output = Kp * error + Ki * integral + Kd * derivative;
			previous_error = error;
		

			
			if(output>0){
				turnLeft();
				ROS_INFO("Turning left");
			}			
			else if(output<0){
				turnRight();
				ROS_INFO("Turning right");
			}
		//}
			turning.publish(turn);
		//}
		
		if(z<.3)
			go.data = 1;
		else
			go.data =2;
			//ROS_INFO("Going");		
		going.publish(go);
		ros::spinOnce();
		loop_rate.sleep();
		cooldown++;
	}	
	
	 return 0;
}
