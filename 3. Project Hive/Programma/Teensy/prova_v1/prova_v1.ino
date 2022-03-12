#include "DualVNH5019MotorShield.h"
#include <SD.h>
#include <SPI.h>

DualVNH5019MotorShield driver1;
DualVNH5019MotorShield driver2;

File myFile;

void setup()
{
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.println("Serial: GO");

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD: NO GO");
  }
  else{
    Serial.println("SD: GO");
  }
  
  if (SD.exists("variabili.txt")) {

    myFile = SD.open("variabili.txt", FILE_READ);
    //READ ALL VARIABLES
    Serial.println("FILE: GO");
    
  }else{

    myFile = SD.open("variabili.txt", FILE_WRITE);
    //WRITE ALL VARIABLES
    Serial.println("FILE: GO");
    
  }

  driver1 = DualVNH5019MotorShield(3, 4, 2, 20, 20, 9, 10, 8, 20, 20 );
  driver2 = DualVNH5019MotorShield(22, 21, 23, 20, 20, 14, 13, 15, 20, 20 );

  if (driver1.getM1Fault()) //Check M1
  {
    Serial.println("M1: NO GO");
  }
  else{
    Serial.println("M1: GO");
  }

  if (driver1.getM2Fault()) //Check M2
  {
    Serial.println("M2: NO GO");
  }
  else{
    Serial.println("M2: GO");
  }

  if (driver2.getM1Fault()) //Check M3
  {
    Serial.println("M3: NO GO");
  }
  else{
    Serial.println("M3: GO");
  }

  if (driver2.getM2Fault()) //Check M4
  {
    Serial.println("M4: NO GO");
  }
  else{
    Serial.println("M4: GO");
  }

}

void loop()
{

}
