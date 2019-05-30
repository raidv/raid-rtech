#include "ros/ros.h"
#include "my_r2d2/MoveRobot.h"
#include <geometry_msgs/Twist.h>

#include <sstream>

int direction = 0;
int count = 0;

bool move(my_r2d2::MoveRobot::Request  &req,
         my_r2d2::MoveRobot::Response &res)
{
  res.success = true;
  direction = req.direction;

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_robot_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("move_robot", move);
  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ROS_INFO("Ready to move robot.");
  //ros::spin();
  ros::Rate rate(10);
  

  while(ros::ok()){
     geometry_msgs::Twist msg;
     switch (direction){
       case 1:
         msg.linear.x = 2;
         count ++;
         if (count > 40){
           direction = 0;
           count = 0;
         }
         break;
       case 2:
         msg.angular.z = 4;
         count ++;
         if (count > 40){
           direction = 0;
           count = 0;
         }
         break;
       case 3:
         msg.angular.z = -4;
         count ++;
         if (count > 40){
           direction = 0;
           count = 0;
         }
         break;
       default:
         break;
     }
     cmd_vel_pub.publish(msg);

     rate.sleep();
     ros::spinOnce(); 
  } 

  return 0;
}
