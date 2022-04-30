#include <ros.h>
#include <ros/time.h>
#include <tiny_msgs/tinyVector.h>
#include <tiny_msgs/tinyIMU.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>


MPU6050 accelgyro;

int16_t ax, ay, az, gx, gy, gz;

uint32_t seq;

tiny_msgs::tinyIMU imu_msg;
ros::NodeHandle  nh;
ros::Publisher imu_pub("tinyImu", &imu_msg);


void setup()
{
  Wire.begin();

  nh.initNode();
  nh.advertise(imu_pub);
  
  accelgyro.initialize();
  seq = 0;
}

void loop()
{
  nh.spinOnce();
}

void gyro(){
    seq++;
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  imu_msg.header.stamp = nh.now();
  imu_msg.header.frame_id = 0;
  imu_msg.header.seq = seq;

  imu_msg.accel.x = ax;
  imu_msg.accel.y = ay;
  imu_msg.accel.z = az;
  imu_msg.gyro.x = gx;
  imu_msg.gyro.y = gy;
  imu_msg.gyro.z = gz;

  imu_pub.publish( &imu_msg );
}
