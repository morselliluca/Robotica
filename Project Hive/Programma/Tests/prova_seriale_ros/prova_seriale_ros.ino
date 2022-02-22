#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;

float x;
float z;

void velCallback( const geometry_msgs::Twist & vel){
  x = vel.linear.x;
  z = vel.angular.z;

}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", velCallback);

void setup()
{
  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  Serial.print(x);
  Serial.print(z);
  nh.spinOnce();
  delay(10);
  
}
