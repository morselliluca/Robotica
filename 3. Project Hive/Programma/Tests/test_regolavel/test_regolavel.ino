#include <DriverDkv.h>

#define outputA1 29
#define outputB1 30
#define outputA2 31
#define outputB2 32
#define outputA3 34
#define outputB3 33
#define outputA4 36
#define outputB4 35

int x;
int z;

float encoderlast, encoderrev, encodererr, targetvel, vel;
int rotms = 44;
int rotrads = 4;
int kp = 1;

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

long previousMillis;
long currentMillis;

int loopTime = 1; //cicli standardizzati da 1ms

int cicliodom = 10; //ogni 10 cicli (10ms) fa la roba di odom
int cicliencoder = 1; //ogni 1 cicli (1ms) fa la roba di odom

DriverDkv driver1 = DriverDkv(3, 4, 2, 9, 10, 8);

void setup() {
  Serial.begin(9600);

}

void loop() {
  encoder();

  //Serial.println(String(counter1) +  String(counter2) +String(counter3) +String(counter4));
      currentMillis = millis();

    if (currentMillis - previousMillis >= loopTime) { // start timed loop for everything else
        previousMillis = currentMillis;
        if (counter % cicliodom == 0) {
            encoderrev = counter1 - encoderlast;
            targetvel = x * rotms + z * rotrads;
            encodererr = targetvel - encoderrev;
            vel = encodererr * kp + vel;
  
  
            driver1.setSpeeds(vel, (vel*-1));
  
            encoderlast = counter1;  
            counter = 0;
        }
        if (counter % cicliencoder == 0) {
            encoder(); //fa gli encoder
        }


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

}
