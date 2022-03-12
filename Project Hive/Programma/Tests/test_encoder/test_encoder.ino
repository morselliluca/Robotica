//#include <ros.h>
//#include <geometry_msgs/Twist.h>

// wheel encoder interrupts
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

//ros::NodeHandle  nh;

float x;
float z;
/*
void velCallback( const geometry_msgs::Twist & vel){
  x = vel.linear.x;
  z = vel.angular.z;

}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", velCallback);
*/
void setup()
{
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
  
  Serial.begin(9600);
  //nh.initNode();
  //nh.subscribe(sub);
}

void loop()
{

  Serial.print(counter1);
  Serial.print(";");
  Serial.print(counter2);
  Serial.print(";");
  Serial.print(counter3);
  Serial.print(";");
  Serial.println(counter4);
  encoder();
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
