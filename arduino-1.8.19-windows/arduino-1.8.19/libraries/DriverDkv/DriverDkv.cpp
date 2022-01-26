#include "DriverDkv.h"

// Constructors 
DriverDkv::DriverDkv(unsigned char INA1,
                     unsigned char INB1,
                     unsigned char PWM1,
                     unsigned char INA2,
                     unsigned char INB2,
                     unsigned char PWM2)
{
  _INA1 = INA1;
  _INB1 = INB1;
  _PWM1 = PWM1;
  _INA2 = INA2;
  _INB2 = INB2;
  _PWM2 = PWM2;

  pinMode(_INA1,OUTPUT);
  pinMode(_INB1,OUTPUT);
  pinMode(_PWM1,OUTPUT);
  pinMode(_INA2,OUTPUT);
  pinMode(_INB2,OUTPUT);
  pinMode(_PWM2,OUTPUT);
}
// Set speed for motor 1, speed is a number betwenn -255 and 255
void DriverDkv::setM1Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }

  if (speed == 0)
  {
    digitalWrite(_INA1,LOW);   // Make the motor coast no
    digitalWrite(_INB1,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA1,LOW);
    digitalWrite(_INB1,HIGH);
  }
  else
  {
    digitalWrite(_INA1,HIGH);
    digitalWrite(_INB1,LOW);
  }

  analogWrite(_PWM1,speed);

}

// Set speed for motor 2, speed is a number betwenn -255 and 255
void DriverDkv::setM2Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // make speed a positive quantity
    reverse = 1;  // preserve the direction
  }

  if (speed == 0)
  {
    digitalWrite(_INA2,LOW);   // Make the motor coast no
    digitalWrite(_INB2,LOW);   // matter which direction it is spinning.
  }
  else if (reverse)
  {
    digitalWrite(_INA2,LOW);
    digitalWrite(_INB2,HIGH);
  }
  else
  {
    digitalWrite(_INA2,HIGH);
    digitalWrite(_INB2,LOW);
  }
  analogWrite(_PWM2,speed);
}

// Set speed for motor 1 and 2
void DriverDkv::setSpeeds(int m1Speed, int m2Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
}