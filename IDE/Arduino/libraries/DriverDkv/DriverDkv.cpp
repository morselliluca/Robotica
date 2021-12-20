#include "DriverDkv.h"

int k = 1;
int counter1 = 0;
int counter2 = 0;

float _DIAM = 0;
float _LARG = 0;
float _ROT = 0;

bool M1 = false;
bool experimental = true;

// Constructors 
DriverDkv::DriverDkv(unsigned char INA1,
                     unsigned char INB1,
                     unsigned char PWM1,
                     unsigned char INA2,
                     unsigned char INB2,
                     unsigned char PWM2){
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

  experimental = false;
}

DriverDkv::DriverDkv(unsigned char INA1,
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
                     unsigned char LARG){
  _INA1 = INA1;
  _INB1 = INB1;
  _PWM1 = PWM1;
  _INA2 = INA2;
  _INB2 = INB2;
  _PWM2 = PWM2;

  _ENA1 = ENA1;
  _ENB1 = ENB1;
  _ENA2 = ENA2;
  _ENB2 = ENB2;

  _ROT = ROT;
  _DIAM = DIAM;
  _LARG = LARG;

  pinMode(_INA1,OUTPUT);
  pinMode(_INB1,OUTPUT);
  pinMode(_PWM1,OUTPUT);
  pinMode(_INA2,OUTPUT);
  pinMode(_INB2,OUTPUT);
  pinMode(_PWM2,OUTPUT);

  pinMode(_ENA1, INPUT);
  pinMode(_ENB1, INPUT);
  pinMode(_ENA2, INPUT);
  pinMode(_ENB2, INPUT);
}

//Experimental
int DriverDkv::Setup()
{
if(experimental){
    setSpeeds(255, 255);

    for (int i = 0; i < 200; i++) {
        counter1 = readencoder(_ENA1, _ENB1, counter1); //read encoder 1
        counter2 = readencoder(_ENA2, _ENB2, counter2); //read encoder 2
        delay(1);
    }

    if (counter1 > counter2) {
        M1 = true;
        k = counter1 / counter2;
    }
    else if (counter1 > counter2) {
        M1 = false;
        k = counter2 / counter1;
    }
    else {
        k = 1;
    }
    counter1 = 0;
    counter2 = 0;

    return k;
}
}

void DriverDkv::Move(int m1Speed, int m2Speed, int mm)
{
if(experimental){
        double rotation = (mm / (_DIAM * 3.14)) * _ROT;
    double media = 0;

    setSpeeds(m1Speed, m2Speed);

    while (media < rotation) {
        counter1 = readencoder(_ENA1, _ENB1, counter1); //read encoder 1
        counter2 = readencoder(_ENA2, _ENB2, counter2); //read encoder 2
        media = media + ((counter1 + counter2) / 2);
    }

    setSpeeds(0, 0);

    counter1 = 0;
    counter2 = 0;
}
}

void DriverDkv::Turn(int m1Speed, int m2Speed, int angolo)
{
if(experimental){
    double rotation = _LARG / ((angolo / 360) * _DIAM) * _ROT;
    double media = 0;

    setSpeeds(m1Speed, m2Speed);

    while (media < rotation) {
        counter1 = readencoder(_ENA1, _ENB1, counter1); //read encoder 1
        counter2 = readencoder(_ENA2, _ENB2, counter2); //read encoder 2
        media = media + ((counter1 + counter2) / 2);
    }

    setSpeeds(0, 0);

    counter1 = 0;
    counter2 = 0;
}
}

void DriverDkv::MoveAuto(int mm)
{
    int a = sin(10);
}

void DriverDkv::TurnAuto(int gradi)
{
}

int DriverDkv::readencoder(int inputDT, int inputCLK, int counter) {
if(experimental){
    int currentStateCLK = 0;
    int previousStateCLK = 0;

    currentStateCLK = digitalRead(inputCLK);

    if (currentStateCLK != previousStateCLK) {
        if (digitalRead(inputDT) != currentStateCLK) {
            counter--;
        }
        else {
            counter++;
        }
    }
    previousStateCLK = currentStateCLK;
    return counter;
}
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
    if (M1) {
        m1Speed = m1Speed / k;
    }
    else {
        m1Speed = m1Speed / k;
    }

    setM1Speed(m1Speed);
    setM2Speed(m2Speed);
}