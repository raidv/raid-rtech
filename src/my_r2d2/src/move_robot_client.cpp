#include "ros/ros.h"
#include "my_r2d2/MoveRobot.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_robot_client");
  if (argc != 2)
  {
    ROS_INFO("usage: move_robot DIRECTION");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<my_r2d2::MoveRobot>("move_robot");
  my_r2d2::MoveRobot srv;
  srv.request.direction = atoll(argv[1]);
  if (not client.call(srv))
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}
