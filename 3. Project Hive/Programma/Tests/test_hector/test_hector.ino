#include <ros.h>
#include <ros/time.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <math.h>
#include <DriverDkv.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_MLX90614.h>
#include <Wire.h>

ros::NodeHandle nh;
std_msgs::String str_msg;

ros::Publisher blk("nero", & str_msg);
ros::Publisher hot("calore", & str_msg);
ros::Publisher str("partito", & str_msg);

#define reflection1A A10 //riflesso analogico 1
#define reflection2A A11 //riflesso analogico 2

#define reflection1D 11 //riflesso digitale 1
#define reflection2D 12 //riflesso digitale 2

#define startsw 37 //start switch

#define IR1 0x5C //indirizzo ir davanti
#define IR2 0x5A //indirizzo ir sinistra
#define IR3 0x5B //indirizzo ir destra

Adafruit_MLX90614 mlx;

DriverDkv driver1 = DriverDkv(3, 4, 2, 9, 10, 8);
DriverDkv driver2 = DriverDkv(22, 21, 23, 14, 13, 15);

char black[] = "";
char heat[] = "";
char starting[] = "";

String nero = "0";
String calore = "0";
String partito = "0";

int buzzer = 26; //buzzer
int sound = 2000; //suono 

bool ctrl = true;

long previousMillis;
long currentMillis;

int loopTime = 1; //cicli standardizzati da 1ms

int cicliros = 10; //ogni 10 cicli (10ms) fa la roba di ros

int counter = 0;

int pwmres = 8;

float kx = pow(2, pwmres) * 0.7;
float kz = pow(2, pwmres) * 0.5;
float kc = 1.2;

float basecutoff = 0.45;

float demandx;
float demandz;

float Left = 0;
float Right = 0;

int cutoff = 170;

void velCallback(const geometry_msgs::Twist & vel) {
    demandx = vel.linear.x;
    demandz = vel.angular.z;

    demandx = constrain(demandx, -1, 1);
    demandz = constrain(demandz, -1, 1);
    if (demandx > 0) {
        demandx = map(demandx, 0, 1, (kx * 0.35), kx);
    } else {
        demandx = map(demandx, -1, 0, -kx, -(kx * 0.35));
    }

    if (demandx > 0) {
        demandz = map(demandz, 0, 1, (kz * basecutoff), kz);
    } else {
        demandz = map(demandz, -1, 0, -kz, -(kz * basecutoff));
    }
}

ros::Subscriber < geometry_msgs::Twist > sub("cmd_vel", velCallback); //create a subscriber for ROS cmd_vel topic

void setup() {

    pinMode(buzzer, OUTPUT);

    nh.initNode(); // Initializing node handler
    nh.subscribe(sub);
    nh.advertise(hot);
    nh.advertise(str);
    nh.advertise(blk);

    mlx.begin(); 

    buzzzerok(buzzer, sound);

}

void loop() {
    currentMillis = millis();

    if (currentMillis - previousMillis >= loopTime) { // start timed loop for everything else
        previousMillis = currentMillis;
        if (counter % cicliros == 0) {
            checkCalore(); //da fare
            checkNero(); //da fare
            checkPartito(); // controlla se lo switch da il parito
            sendStuff(); //manda la roba a ros
            nh.spinOnce();
            partito = "0";
            calore = "0";
            nero = "0";
            counter = 0;
        }

        Left = demandx - demandz;
        Right = demandx + demandz;

        Left = constrain(Left, -cutoff, cutoff);
        Right = constrain(Right, -cutoff, cutoff);

        driver1.setSpeeds(Right, (Left * -1));
        driver2.setSpeeds(Right, (Left * -1));

        counter++;

    }

}

void sendStuff() {   
  
    nero.toCharArray(black, (nero.length() + 1));
    calore.toCharArray(heat, (calore.length() + 1));
    partito.toCharArray(starting, (partito.length() + 1));

    //mando i messaggi a ros
    str_msg.data = black;
    blk.publish( & str_msg);
    str_msg.data = heat;
    hot.publish( & str_msg);
    str_msg.data = starting;
    str.publish( & str_msg);
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
  mlx.AddrSet(IR1); 
  char temp[3];
  if(mlx.readAmbientTempC() < mlx.readObjectTempC() * kc){
    temp[0] = "F";
  }
  mlx.AddrSet(IR2);
  if(mlx.readAmbientTempC() < mlx.readObjectTempC() * kc){
    temp[1] = "L";
  }
  mlx.AddrSet(IR3);
  if(mlx.readAmbientTempC() < mlx.readObjectTempC() * kc){
    temp[2] = "R";
  }
  calore = String(temp);

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
