1. How to run the program

## First terminal window:
git clone https://github.com/raidv/raid-rtech.git
cd raid-rtech
catkin_make
source devel/setup.bash
roslaunch my_r2d2 r2d2_server_control.launch 

## Second terminal window
cd raid-rtech
source devel/setup.bash
rosrun my_r2d2 move_robot_client 1

rosrun my_r2d2 move_robot_client 2

rosrun my_r2d2 move_robot_client 3

2. Solution to problem

I started from where lab 4 ended. I had my_r2d2 with a launch file that succesfully opened everything up such that I could use turtle teleop to control the robot. I then needed to replace the teleop node (that took care of publishing the geometry_msgs/Twist messages to corresponding cmd_vel topic) with a server that would do the same. I started by creating the service file (raid-rtech/src/my_r2d2/srv/MoveRobot.srv). The service file has one int64 request value and one boolean response value (I used the addTwoInts example and left it to be int64 even though it is completely unneccesary in this task to use such large type).

Then I created the move_robot_client and move_robot_server files. Again I used the AddTwoInts as basis. In the client I write user input to the request field of the service. On the server side I take the same value and write it to a direction variable. If direction is 1, robot moves forward, if 2, robot turns turns about 90 degrees CCW and if it's 3 the robot turns 90 degrees the other way. The server always writes true to the response vale of the service (it is just a proof-of-concept so not all features are implemented, but there is a vacancy to possibly give feedback to the client program). It is also worth noting that in the response routine only the direction variable is updated. The publishing on the cmd_vel topic is done seperatly afterwards, thus not jamming the service calls.

The publisher spins at a rate of 10 and for each movement the geometry_msgs/Twist message is published on cmd_vel topic for 40 times (resulting in 4 second movements). The velocity values were chosen through the process of trial and error that would result in visible movement and about 90 degree rotation.

The client node can take any suitable int64 as input, but the server node only responds to values 1, 2 and 3 that move the robot only in the three directions stated in the task. More movements can be implemented in the future.

3. Helpful links used

http://wiki.ros.org/ROS/Tutorials/CreatingMsgAndSrv#Creating_a_srv
http://wiki.ros.org/ROS/Tutorials/WritingServiceClient%28c%2B%2B%29
http://wiki.ros.org/ROS/Tutorials/ExaminingServiceClient
http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber%28c%2B%2B%29

