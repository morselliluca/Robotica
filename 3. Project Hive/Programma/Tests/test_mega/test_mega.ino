#include <ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/String.h>
#include <math.h>
#include <DriverDkv.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

ros::NodeHandle nh;
std_msgs::String str_msg;

geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;
ros::Publisher blk("nero", & str_msg);
ros::Publisher hot("calore", & str_msg);
ros::Publisher str("partito", & str_msg);

DriverDkv driver1 = DriverDkv(3, 4, 2, 9, 10, 8);
DriverDkv driver2 = DriverDkv(22, 21, 23, 14, 13, 15);

volatile signed int counterL = 0; // This variable will increase or decrease depending on the rotation of encoder
volatile signed int counterR = 0; // This variable will increase or decrease depending on the rotation of encoder
volatile int dcountL = 0; // diff in encoder reading for left wheel
volatile int dcountR = 0; // diff in encoder reading for left wheel

double x = 0.0; // Initial X position
double y = 0.0; // Initial Y position
double theta = 0.00; // Initial Theta angle

char base_link[] = "/base_link";
char odom[] = "/odom";
char black[] = "";
char heat[] = "";
char starting[] = "";

String nero = "0"; //cambia questa variabile per provare il nero
String calore = "0"; //cambia questa variabile per provare il calore
String partito = "0"; //cambia questa variabile per provare il parito

float dL; // Dl = 2*PI*R*(lefttick/totaltick)
float dR; // Dr = 2*PI*R*(righttick/totaltick)
float dC;

float R = 0.09; // Wheel Radius 
float tick = 1240; // Encoder total tick
float len = 0.18; // Distance between two wheels

int buzzer = 26; //buzzer
int sound = 2000; //suono 

long previousMillis;
long currentMillis;

int loopTime = 1; //cicli standardizzati da 1ms

int cicliodom = 10; //ogni 10 cicli (10ms) fa la roba di odom
int cicliencoder = 1; //ogni 1 cicli (1ms) fa la roba di odom

int counter = 0;

float demandx;
float demandz;

void velCallback(  const geometry_msgs::Twist& vel)
{
     demandx = vel.linear.x;
     demandz = vel.angular.z;

     demandx = constrain(demandx,-1,1);    
     demandz = constrain(demandz,-1,1);
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel" , velCallback);     //create a subscriber for ROS cmd_vel topic


void setup() {
    
    
    nh.initNode(); // Initializing node handler
    broadcaster.init(nh); // odom data broadcaster init
    nh.subscribe(sub);
    nh.advertise(hot);
    nh.advertise(str);
    nh.advertise(blk);
}

void loop() {
    currentMillis = millis();

    if (currentMillis - previousMillis >= loopTime) { // start timed loop for everything else
        previousMillis = currentMillis;
        if (counter % cicliodom == 0) {
            SendStuff(); //manda la roba a ros
            nh.spinOnce();
            counter = 0;
        }
        
        counter++;
        
  }

}

void SendStuff() {
    // creo il pacchetto odom + tf
    t.header.frame_id = odom; // odom data publishes on Odom topic
    t.child_frame_id = base_link; // base link
    t.transform.translation.x = x;
    t.transform.translation.y = y;
    t.transform.rotation = tf::createQuaternionFromYaw(theta); // converting from euler angle to quaternion form
    t.header.stamp = nh.now();

    nero.toCharArray(black, (nero.length() + 1));
    calore.toCharArray(heat, (calore.length() + 1));
    partito.toCharArray(starting, (partito.length() + 1));

    //mando i messaggi a ros
    broadcaster.sendTransform(t); // broadcasting updated result    
    str_msg.data = black;
    blk.publish( & str_msg);
    str_msg.data = heat;
    hot.publish( & str_msg);
    str_msg.data = starting;
    str.publish( & str_msg);

}
