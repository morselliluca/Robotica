#pragma once

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || \
    defined(__AVR_ATmega328PB__) || defined (__AVR_ATmega32U4__)
  #define DriverDkv_TIMER1_AVAILABLE
#endif

#include <Arduino.h>

class DriverDkv
{
  public:
    // CONSTRUCTORS   
    DriverDkv(unsigned char INA1,
               unsigned char INB1,
               unsigned char PWM1,
               unsigned char INA2,
               unsigned char INB2,
               unsigned char PWM2);

    DriverDkv(unsigned char INA1,
               unsigned char INB1,
               unsigned char PWM1,
               unsigned char INA2,
               unsigned char INB2,
               unsigned char PWM2,
               unsigned char ENA1,
               unsigned char ENB1,
               unsigned char ENA2,
               unsigned char ENB2,
               unsigned char ROT,
               unsigned char DIAM,
               unsigned char LARG,
               unsigned char BASESPEED);


    // PUBLIC METHODS
    int Setup();
    int readencoder(int inputDT, int inputCLK, int counter);
    //normal
    void SetM1Speed(int speed); // Set speed for M1.
    void SetM2Speed(int speed); // Set speed for M2.
    void SetSpeeds(int m1Speed, int m2Speed); // Set speed for both M1 and M2.
    //smothed
    void SmoothSetM1Speed(int speed); // Set speed for M1.
    void SmoothSetM2Speed(int speed); // Set speed for M2.
    void SmoothSetSpeeds(int m1Speed, int m2Speed); // Set speed for both M1 and M2.
    //experimental
    void Move(int speed, int mm); 
    void Turn(int angolo);


    

private:
        unsigned char _INA1;
        unsigned char _INB1;
        unsigned char _PWM1;
        unsigned char _INA2;
        unsigned char _INB2;
        unsigned char _PWM2;
        unsigned char _ENA1;
        unsigned char _ENB1;
        unsigned char _ENA2;
        unsigned char _ENB2;

};
