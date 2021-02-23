/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;

Servo servo, esc;
char armed;
//to run: in each terminal: (1) roscore (2) rosrun rosserial_python serial_node.py /dev/ttyACM0 
// (3)rostopic pub servo std_msgs/UInt16 10 & rostopic pub esc std_msgs/UInt16 1
 
//turning settings are now done manually
//120 is full left
// 50 is straight
//and 10 is right
void servo_cb( const std_msgs::UInt16& cmd_msg){
  servo.write((int) cmd_msg.data); //set servo angle, should be from 0-180  
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}
//speed settings will be minimal to avoid damage
//they are: 1: stop, and 2: go
void esc_cb(const std_msgs::UInt16& cmd_msg){
  if(!armed){
    esc.attach(3);
    //delay(300);
    esc.writeMicroseconds(2100);
    delay(1000);
    esc.writeMicroseconds(700);
    delay(1000);
    esc.writeMicroseconds(1400);
    delay(1000);
    esc.writeMicroseconds(1400);
    armed=1;
  }
  if(cmd_msg.data == 1)
    esc.writeMicroseconds(1400);
  if(cmd_msg.data == 2)
    esc.writeMicroseconds(1300);
}

ros::Subscriber<std_msgs::UInt16> sub0("servo", servo_cb);
ros::Subscriber<std_msgs::UInt16> sub1("esc",esc_cb);

void setup(){
  pinMode(13, OUTPUT);
  armed = 0;
  nh.initNode();
  nh.subscribe(sub0);
  nh.subscribe(sub1);
  servo.attach(9); //attach it to pin 9
}

void loop(){
  nh.spinOnce();
  delay(1);
}
