
#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Range.h>
#include <math.h>

// Ultrasonic sensor pins
int echoPin = A4;
int trigPin = A5;

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher range_pub("ultrasound/raw", &range_msg);

//char hello[13] = "hello world!";
int count = 0;

void setup()
{

  //Serial.begin(9600);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
  
  nh.initNode();
  nh.advertise(range_pub);
}

long getSonarReadingMillimeters()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration_us = pulseIn(echoPin, HIGH);
  long distance_mm = (duration_us / 58.0) * 10;
  return distance_mm;
}

sensor_msgs::Range build_msg()
{
  std_msgs::Header header;
  header.seq = count;
  header.frame_id = "raw_range";
  sensor_msgs::Range msg;
  
  msg.header = header;
  msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  msg.field_of_view = M_PI/(180/15); // 15 degrees in rad

  //float min_range = 0.02; // from datasheet
  //float max_range = 4;

  msg.min_range = float(0.02);
  msg.max_range = float(4.0);

  float us = getSonarReadingMillimeters()/1000.0; //Get distance from wall with ultrasonic sensor
  msg.range = us; // maybe needs a cast to float
  return msg;
}

void loop()
{
  //long us = getSonarReadingMillimeters(); //Get distance from wall with ultrasonic sensor
  //Serial.println(us);
  
  range_msg = build_msg();
  range_pub.publish( &range_msg );
  nh.spinOnce();
  delay(20);
  count++;
}
