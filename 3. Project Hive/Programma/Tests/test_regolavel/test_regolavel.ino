#include <DriverDkv.h>

#define outputA1 29
#define outputB1 30
#define outputA2 31
#define outputB2 32
#define outputA3 34
#define outputB3 33
#define outputA4 36
#define outputB4 35

int counter = 0;

<<<<<<< HEAD
float encoderlast, encoderrev, encodererr, targetvel, vel;
int kp = 1;
=======
float encoderrev, vel;
int pwm1 = 20;
>>>>>>> e123bf2f7858f893cb2f3ca11fe913f79eabe2d1

int ticks = 1240;
long previousMillis;
long currentMillis;

int loopTime = 1; //cicli standardizzati da 1ms

int cicliodom = 5000; //ogni 10 cicli (10ms) fa la roba di odom
int cicliencoder = 1; //ogni 1 cicli (1ms) fa la roba di odom

DriverDkv driver1 = DriverDkv(3, 4, 2, 9, 10, 8);
DriverDkv driver2 = DriverDkv(22, 21, 23, 14, 13, 15);

void setup() {
  Serial.begin(9600);

}

void loop() {
  encoder();

  //Serial.println(String(counter1) +  String(counter2) +String(counter3) +String(counter4));
      currentMillis = millis();

    if (currentMillis - previousMillis >= loopTime && pwm1 < 255) { // start timed loop for everything else
        previousMillis = currentMillis;
        if (counter % cicliodom == 0) {
<<<<<<< HEAD
            encoderrev = counter1 - encoderlast;
     
            encodererr = (((encoerrev *1000) / ticks) * 0.09 * 3.14 + 2) - x;
            vel = encodererr * kp + vel;
  
  
            driver1.setSpeeds(vel, (vel*-1));
  
            encoderlast = counter1;  
            counter = 0;
=======
            encoderrev = ((counter1+counter2+counter3+counter4)/4);
            vel = (encoderrev / 5) * 0.2826;

            driver1.setSpeeds(pwm1, (pwm1*-1));
            driver2.setSpeeds(pwm1, (pwm1*-1));
            counter1 = 0;
            counter2 = 0;
            counter3 = 0;
            counter4 = 0;
            pwm1 += 5;
>>>>>>> e123bf2f7858f893cb2f3ca11fe913f79eabe2d1
        }
        if (counter % cicliencoder == 0) {
            encoder(); //fa gli encoder
            Serial.print(vel);
            Serial.print("\t");
            Serial.println(pwm1);
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
