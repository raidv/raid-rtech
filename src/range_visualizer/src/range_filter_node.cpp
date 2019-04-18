#include <vector>
#include <numeric>
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Range.h"

std::vector< float > arr(25);
sensor_msgs::Range prev_msg;

void Callback(const sensor_msgs::Range::ConstPtr& msg)
{
  prev_msg = *msg;
  arr.insert(arr.begin(), msg->range);
  arr.pop_back();
  ROS_INFO("Valor indice: [%f]", msg->range);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "range_filter_node");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("ultrasound/raw", 500, Callback);
//  ros::spin();

  ros::Publisher pub = n.advertise<sensor_msgs::Range>("ultrasound/filtered", 500);
  //ros::Publisher pub = n.advertise<std_msgs::String>("ultrasound/filtered", 500);
  ros::Rate loop_rate(10);
  //ros::spinOnce();

  int count = 0;
  while (ros::ok())
  {
    float average = accumulate( arr.begin(), arr.end(), 0.0)/arr.size(); 
    sensor_msgs::Range msg = prev_msg;
    msg.range = average;
    msg.header.frame_id = "filtered_range";

    //std_msgs::String msg;
    //std::stringstream ss;
    //ss << "hello world " << count;
    //msg.data = ss.str();
    //msg.data
    //ROS_INFO("%f", msg.data);
    //ROS_INFO("%s", msg.data.c_str());
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


  return 0;
}
