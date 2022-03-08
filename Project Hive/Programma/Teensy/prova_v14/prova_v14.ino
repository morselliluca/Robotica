#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Arduino_GFX_Library.h>
#include <DriverDkv.h>
#include <Adafruit_MLX90614.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

//Costanti

#define reflection1A A10 //riflesso analogico 1
#define reflection2A A11 //riflesso analogico 2

#define reflection1D 11 //riflesso digitale 1
#define reflection2D 12 //riflesso digitale 2

#define morto1_led 28 //morto1
#define morto2_led 16 //morto2
#define morto3_led 17 //morto3

#define serial_led 5 //serial led
#define start_led 6 //start led

#define startsw 37 //start switch

#define buzzer 26 //buzzer

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

//indirizzi I2C
uint8_t IR[3] = {0x5C , 0x5A , 0x5B};

//Dischiarazioni oggetti
DriverDkv Driver1 = DriverDkv(3, 4, 2, 9, 10, 8);
DriverDkv Driver2 = DriverDkv(22, 21, 23, 14, 13, 15);
Adafruit_MLX90614 mlx;
ros::NodeHandle  nh;

//dichiarazione file
File myFile; 

int sound = 2000; //suono 
int reflection = 0; //rifelsso medio

String input;
String speedL;
String speedR;
String cubi;

float x;
float z;

bool caldo = false;

void velCallback( const geometry_msgs::Twist & vel){
  x = vel.linear.x;
  z = vel.angular.z;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", velCallback);


void setup() {
    Serial1.begin(9600);
    mlx.begin();

    //PinModes
    pinMode(buzzer, OUTPUT);
    pinMode(startsw, INPUT);

    analogWriteFrequency(2, 375000);
    analogWriteFrequency(8, 375000);
    analogWriteFrequency(23, 375000);
    analogWriteFrequency(15, 375000);

    analogWriteResolution(8);

    //Serial Check
    Serial1.begin(9600);
    while (!Serial1) {
        ; // wait for serial port to connect.
    }
    if(Serial1.avaible()){
      digitalWrite(serial_led, HIGH);
    }
    nh.initNode();
    nh.subscribe(sub);
    

}

/////Main/////

void loop() {
  for(int i = 0; i < 3; i++){
    mlx.AddrSet(IR[i]);
      if((mlx.readObjectTempC() - mlx.readAmbientTempC()) > 5 && !caldo){
      Serial1.print("caldo in");Serial.println(IR[i]);
      caldo = true;
      dead();
    }
  }
  nh.spinOnce();
  Serial1.print(x);
  Serial1.print(z);
}

void dead() {
    digitalWrite(morto1_led, HIGH);
    digitalWrite(morto2_led, HIGH);
    digitalWrite(morto3_led, HIGH);
    delay(200);
    digitalWrite(morto1_led, LOW);
    digitalWrite(morto2_led, LOW);
    digitalWrite(morto3_led, LOW);
}

void bttf() {
  digitalWrite(morto1_led, HIGH);
  delay(50);
  digitalWrite(morto2_led, HIGH);
  delay(50);
  digitalWrite(morto3_led, HIGH);
  delay(50);
  digitalWrite(morto1_led, LOW);
  delay(50);
  digitalWrite(morto2_led, LOW);
  delay(50);
  digitalWrite(morto3_led, LOW);
  delay(50);
}
