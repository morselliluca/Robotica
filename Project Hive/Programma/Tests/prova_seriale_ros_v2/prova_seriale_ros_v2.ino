#include <ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

ros::NodeHandle  nh;

geometry_msgs::TransformStamped t;
tf::TransformBroadcaster broadcaster;

#define outputA1 29
#define outputB1 30
#define outputA2 31
#define outputB2 32
#define outputA3 34
#define outputB3 33
#define outputA4 36
#define outputB4 35

int counter1 = 0;
int aState1;
int aLastState1;

int counter2 = 0;
int aState2;
int aLastState2;

int counter3 = 0;
int aState3;
int aLastState3;

int counter4 = 0;
int aState4;
int aLastState4;

volatile signed int counterL = 0;       // This variable will increase or decrease depending on the rotation of encoder
volatile signed int counterR = 0;       // This variable will increase or decrease depending on the rotation of encoder
volatile int dcountL = 0;               // diff in encoder reading for left wheel
volatile int dcountR = 0;               // diff in encoder reading for left wheel

double x = 0.0;                         // Initial X position
double y = 0.0;                         // Initial Y position
double theta = 0.00;                    // Initial Theta angle

char base_link[] = "/base_link";
char odom[] = "/odom";
float pi=3.14;                          // Pi=3.14
float R=0.09;                          // Wheel Radius 
unsigned int tick=1242;                  // Encoder total tick
float len=0.18;                         // Distance between two wheels

void setup() {
  pinMode(outputA1, INPUT);
  pinMode(outputB1, INPUT);
  pinMode(outputA2, INPUT);
  pinMode(outputB2, INPUT);
  pinMode(outputA3, INPUT);
  pinMode(outputB3, INPUT);
  pinMode(outputA4, INPUT);
  pinMode(outputB4, INPUT);
  aLastState1 = digitalRead(outputA1);
  aLastState2 = digitalRead(outputA2);
  aLastState3 = digitalRead(outputA3);
  aLastState4 = digitalRead(outputA4);
  nh.initNode();                        // Initializing node handler
  broadcaster.init(nh);                 // odom data broadcaster init

}

void loop() {
  encoder();
  dcountL=counterL-dcountL;
  dcountR=counterR-dcountR;
   
  signed int templ=counterL; 
  signed int tempR=counterR;
  
  float dL=0.72*(dcountL/(float)tick);  // Dl = 2*PI*R*(lefttick/totaltick)
  float dR=0.72*(dcountR/(float)tick);  // Dr = 2*PI*R*(righttick/totaltick)
  float dC=(dL+dR)/2;

   x = x+(dC*(cos(theta)));             // calculates new X position based on wheel revolution
   y = y+(dC*(sin(theta)));             // calculates new Y position based on wheel revolution
   theta = theta +((dR-dL)/len);        // calculates new theta angle based on encoder values
  if(theta > 3.14)
    theta=-3.14;
    
  // tf odom->base_link
  t.header.frame_id = odom;             // odom data publishes on Odom topic
  t.child_frame_id = base_link;         
  
  t.transform.translation.x = x;
  t.transform.translation.y = y;
  // converting from euler angle to quaternion form
  t.transform.rotation = tf::createQuaternionFromYaw(theta);
  t.header.stamp = nh.now();
  
  broadcaster.sendTransform(t);         // broadcasting updated result 
  nh.spinOnce();
  
  dcountL=templ;
  dcountR=tempR;
  delay(1);
}

void encoder() {
  aState1 = digitalRead(outputA1); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState1 != aLastState1) {
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB1) != aState1) {
      counter1++;
    } else {
      counter1--;
    }

  }
  aLastState1 = aState1; // Updates the previous state of the outputA with the current state

  aState2 = digitalRead(outputA2); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState2 != aLastState2) {
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB2) != aState2) {
      counter2++;
    } else {
      counter2--;
    }

  }
  aLastState2 = aState2; // Updates the previous state of the outputA with the current state

  aState3 = digitalRead(outputA3); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState3 != aLastState3) {
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB3) != aState3) {
      counter3++;
    } else {
      counter3--;
    }

  }
  aLastState3 = aState3; // Updates the previous state of the outputA with the current state

  aState4 = digitalRead(outputA4); // Reads the "current" state of the outputA
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState4 != aLastState4) {
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB4) != aState4) {
      counter4++;
    } else {
      counter4--;
    }

  }
  aLastState4 = aState4; // Updates the previous state of the outputA with the current state

  counterL = (counter1 + counter2) / 2;
  counterR = (counter3 + counter4) / 2;
}
