#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Range.h"

#include <math.h>
#include <cstdlib>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "data_visualizer");
  ros::NodeHandle n;

  ros::Publisher random_range_pub = n.advertise<sensor_msgs::Range>("random_range", 1000);

  ros::Rate loop_rate(10);

  //srand(1);

  int count = 0;
  while (ros::ok())
  {
    std_msgs::Header header;
    header.seq = count;
    header.stamp = ros::Time::now();
    header.frame_id = "random_range";
    sensor_msgs::Range msg;

    msg.header = header;
    msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
    msg.field_of_view = M_PI/4;

    float min_range = 0.02;
    float max_range = 4;

    msg.min_range = min_range;
    msg.max_range = max_range;

    float r = min_range + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(max_range-min_range));
    msg.range = r;


    //ROS_INFO("%s", msg.data.c_str());

    random_range_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
