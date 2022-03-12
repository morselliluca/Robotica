//#include <ros.h>
//#include <geometry_msgs/Twist.h>

// wheel encoder interrupts

#define encoder0PinA 29      // encoder 1
#define encoder0PinB 30

#define encoder1PinA 31     // encoder 2
#define encoder1PinB 32

#define encoder2PinA 33      // encoder 3
#define encoder2PinB 34

#define encoder3PinA 35     // encoder 4
#define encoder3PinB 36

volatile long encoder0Pos = 0;    // encoder 1
volatile long encoder1Pos = 0;    // encoder 2
volatile long encoder2Pos = 0;    // encoder 3
volatile long encoder3Pos = 0;    // encoder 4

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
  pinMode(encoder0PinA, INPUT_PULLUP);    // encoder pins
  pinMode(encoder0PinB, INPUT_PULLUP);

  pinMode(encoder1PinA, INPUT_PULLUP); 
  pinMode(encoder1PinB, INPUT_PULLUP);

  pinMode(encoder2PinA, INPUT_PULLUP);    // encoder pins
  pinMode(encoder2PinB, INPUT_PULLUP);

  pinMode(encoder3PinA, INPUT_PULLUP); 
  pinMode(encoder3PinB, INPUT_PULLUP);

  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE); 

  attachInterrupt(2, doEncoderC, CHANGE);
  attachInterrupt(3, doEncoderD, CHANGE); 

  attachInterrupt(4, doEncoderE, CHANGE);
  attachInterrupt(5, doEncoderF, CHANGE); 

  attachInterrupt(6, doEncoderG, CHANGE);
  attachInterrupt(7, doEncoderH, CHANGE); 
  
  Serial.begin(9600);
  //nh.initNode();
  //nh.subscribe(sub);
}

void loop()
{
  Serial.print(encoder0Pos + ";");
  Serial.print(encoder1Pos + ";");
  Serial.print(encoder2Pos + ";");
  Serial.println(encoder3Pos + ";");
  //nh.spinOnce();
  delay(1);
  
}

// ************** encoder 1 *********************


void doEncoderA(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinB) == HIGH) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
 
}

void doEncoderB(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {  
      encoder0Pos = encoder0Pos + 1;         // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinA) == LOW) {   
      encoder0Pos = encoder0Pos + 1;          // CW
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
  

}

// ************** encoder 2 *********************

void doEncoderC(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder1PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder1PinB) == LOW) {  
      encoder1Pos = encoder1Pos - 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder1PinB) == HIGH) {   
      encoder1Pos = encoder1Pos - 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;          // CCW
    }
  }
 
}

void doEncoderD(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder1PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder1PinA) == HIGH) {  
      encoder1Pos = encoder1Pos - 1;         // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder1PinA) == LOW) {   
      encoder1Pos = encoder1Pos - 1;          // CW
    } 
    else {
      encoder1Pos = encoder1Pos + 1;          // CCW
    }
  }
  

}

// ************** encoder 3 *********************


void doEncoderE(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder2PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder2PinB) == LOW) {  
      encoder2Pos = encoder2Pos + 1;         // CW
    } 
    else {
      encoder2Pos = encoder2Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder2PinB) == HIGH) {   
      encoder2Pos = encoder2Pos + 1;          // CW
    } 
    else {
      encoder2Pos = encoder2Pos - 1;          // CCW
    }
  }
 
}

void doEncoderF(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder2PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder2PinA) == HIGH) {  
      encoder2Pos = encoder2Pos + 1;         // CW
    } 
    else {
      encoder2Pos = encoder2Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder2PinA) == LOW) {   
      encoder2Pos = encoder2Pos + 1;          // CW
    } 
    else {
      encoder2Pos = encoder2Pos - 1;          // CCW
    }
  }
  

}

// ************** encoder 4 *********************

void doEncoderG(){  

  // look for a low-to-high on channel A
  if (digitalRead(encoder3PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder3PinB) == LOW) {  
      encoder3Pos = encoder3Pos - 1;         // CW
    } 
    else {
      encoder3Pos = encoder3Pos + 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder3PinB) == HIGH) {   
      encoder3Pos = encoder3Pos - 1;          // CW
    } 
    else {
      encoder3Pos = encoder3Pos + 1;          // CCW
    }
  }
 
}

void doEncoderH(){  

  // look for a low-to-high on channel B
  if (digitalRead(encoder3PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder3PinA) == HIGH) {  
      encoder3Pos = encoder3Pos - 1;         // CW
    } 
    else {
      encoder3Pos = encoder3Pos + 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder3PinA) == LOW) {   
      encoder3Pos = encoder3Pos - 1;          // CW
    } 
    else {
      encoder3Pos = encoder3Pos + 1;          // CCW
    }
  }
  

}
