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

#define outputA1 29
#define outputB1 30
#define outputA2 31
#define outputB2 32
#define outputA3 34
#define outputB3 33
#define outputA4 36
#define outputB4 35

#define reflection1A A10 //riflesso analogico 1
#define reflection2A A11 //riflesso analogico 2

#define reflection1D 11 //riflesso digitale 1
#define reflection2D 12 //riflesso digitale 2

#define startsw 37 //start switch

#define IR1 0x5C //indirizzo ir davanti
#define IR2 0x5A //indirizzo ir sinistra
#define IR3 0x5B //indirizzo ir destra

File myFile; //dichiarazione file

DriverDkv driver1 = DriverDkv(3, 4, 2, 9, 10, 8);
DriverDkv driver2 = DriverDkv(22, 21, 23, 14, 13, 15);

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

volatile signed int counterL = 0; // This variable will increase or decrease depending on the rotation of encoder
volatile signed int counterR = 0; // This variable will increase or decrease depending on the rotation of encoder
volatile int dcountL = 0; // diff in encoder reading for left wheel
volatile int dcountR = 0; // diff in encoder reading for left wheel

double x = 0.0; // Initial X position
double y = 0.0; // Initial Y position
double theta = 0.00; // Initial Theta angle

signed int templ;
signed int tempR;

char base_link[] = "/base_link";
char odom[] = "/odom";
char black[] = "";
char heat[] = "";
char starting[] = "";

String nero = "0";
String calore = "0";
String partito = "0";

float dL; // Dl = 2*PI*R*(lefttick/totaltick)
float dR; // Dr = 2*PI*R*(righttick/totaltick)
float dC;

float R = 0.09; // Wheel Radius 
float tick = 1240; // Encoder total tick
float len = 0.18; // Distance between two wheels

int buzzer = 26; //buzzer
int sound = 2000; //suono 

bool ctrl = true;

long previousMillis;
long currentMillis;

int loopTime = 1; //cicli standardizzati da 1ms

int cicliodom = 10; //ogni 10 cicli (10ms) fa la roba di odom
int cicliencoder = 1; //ogni 1 cicli (1ms) fa la roba di odom

int counter = 0;

int kx = 1000;
int kz = 700;

float demandx;
float demandz;

float Left = 0;
float Right = 0;

void velCallback(  const geometry_msgs::Twist& vel)
{
     demandx = vel.linear.x;
     demandz = vel.angular.z;

     demandx = constrain(demandx,-1,1);    
     demandz = constrain(demandz,-1,1);

     demandx = demandx * kx;
     demandz = demandz * kz;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel" , velCallback);     //create a subscriber for ROS cmd_vel topic


void setup() {
    pinMode(buzzer, OUTPUT);

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
    
    nh.initNode(); // Initializing node handler
    broadcaster.init(nh); // odom data broadcaster init
    nh.subscribe(sub);
    nh.advertise(hot);
    nh.advertise(str);
    nh.advertise(blk);

    buzzzerok(buzzer, sound);
}

void loop() {
    currentMillis = millis();

    if (currentMillis - previousMillis >= loopTime) { // start timed loop for everything else
        previousMillis = currentMillis;
        if (counter % cicliodom == 0) {
            checkCalore(); //da fare
            checkNero(); //da fare
            calcolaOdom(); //calcola odom
            checkPartito(); // controlla se lo switch da il parito
            sendOdom(); //manda la roba a ros
            nh.spinOnce();
            //myFile.write(String(t) + " ; " + String(nero) + " ; " + String(calore) + " ; " + String(partito));
            counter = 0;
        }
        if (counter % cicliencoder == 0) {
            encoder(); //fa gli encoder
        }
     
        Left = demandx - (demandz);
        Right = demandx + (demandz);

        Left = constrain(Left,-200,200);
        Right = constrain(Right,-200,200);
        driver1.setSpeeds(Right, (Left*-1));
        driver2.setSpeeds(Right, (Left*-1));

        counter++;
        
  }

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
            counter2--;
        } else {
            counter2++;
        }

    }
    aLastState2 = aState2; // Updates the previous state of the outputA with the current state

    aState3 = digitalRead(outputA3); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState3 != aLastState3) {
        // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
        if (digitalRead(outputB3) != aState3) {
            counter3--;
        } else {
            counter3++;
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

void calcolaOdom() {
    dcountL = counterL - dcountL;
    dcountR = counterR - dcountR;

    templ = counterL;
    tempR = counterR;

    dL = 2 * PI * R * (dcountL / tick); // Dl = 2*PI*R*(lefttick/totaltick)
    dR = 2 * PI * R * (dcountR / tick); // Dr = 2*PI*R*(righttick/totaltick)
    dC = (dL + dR) / 2;

    x = x + (dC * (cos(theta))); // calculates new X position based on wheel revolution
    y = y + (dC * (sin(theta))); // calculates new Y position based on wheel revolution
    theta = theta + ((dR - dL) / len); // calculates new theta angle based on encoder values
    if (theta > PI)
        theta = -PI;
}

void sendOdom() {
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

    dcountL = templ;
    dcountR = tempR;
}

void checkPartito() {
    if (digitalRead(startsw)) {
        partito = "0";
    } else {
        partito = "1";
    }
}

void checkNero() {
  
}

void checkCalore() {

}

void buzzzerok(int buzzer, int sound) {

    tone(buzzer, sound);
    delay(100);
    noTone(buzzer);
    tone(buzzer, sound);
    delay(100);
    noTone(buzzer);
    delay(700);

}
