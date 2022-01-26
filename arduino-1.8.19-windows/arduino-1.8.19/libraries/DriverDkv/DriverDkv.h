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

    // PUBLIC METHODS
    void setM1Speed(int speed); // Set speed for M1.
    void setM2Speed(int speed); // Set speed for M2.
    void setSpeeds(int m1Speed, int m2Speed); // Set speed for both M1 and M2.

  private:
    unsigned char _INA1;
    unsigned char _INB1;
    unsigned char _PWM1;
    unsigned char _INA2;
    unsigned char _INB2;
    unsigned char _PWM2;

};
