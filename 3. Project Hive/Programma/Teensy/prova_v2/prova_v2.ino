#include "DualVNH5019MotorShield.h"
#include <SD.h>
#include <SPI.h>

DualVNH5019MotorShield driver1;
DualVNH5019MotorShield driver2;

File myFile;

int buzzer = 26; //buzzer
int sound = 1000; //suono 

void buzzzerok(){
  /*
      tone(buzzer, sound);
      delay(200);
      noTone(buzzer);
      tone(buzzer, sound);
      delay(200);
      noTone(buzzer); 
      delay(700);
      */
}

void buzzerfault(){
      tone(buzzer, sound);
      delay(300);
      noTone(buzzer);
      delay(700);
}

void setup()
{
   
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect.
  }
  buzzzerok();
  Serial.println("Serial: GO");
  
  if (!SD.begin(BUILTIN_SDCARD)) {
      Serial.println("SD: NO GO");
      buzzerfault();
  }
  else{
    Serial.println("SD: GO");
    buzzzerok();
  }
  
  if (SD.exists("variabili.txt")) {

    myFile = SD.open("variabili.txt", FILE_READ);
    myFile.readln
    Serial.println("FILE: GO");
    buzzzerok();
    
  }else{

    myFile = SD.open("variabili.txt", FILE_WRITE);
    myFile.println(buzzer);
    myFile.println(sound);
    Serial.println("FILE: GO");
    buzzzerok();
    
  }

 driver1 = DualVNH5019MotorShield(3, 4, 2, 20, 20, 9, 10, 8, 20, 20 );
 driver2 = DualVNH5019MotorShield(22, 21, 23, 20, 20, 14, 13, 15, 20, 20 );
 Serial.println("test: GO");

}

void loop()
{
  driver1.setSpeeds(400, 400);
  driver2.setSpeeds(400, 400);
}
