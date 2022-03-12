#include <DualVNH5019MotorShield.h>
#include <SD.h>
#include <SPI.h>

/////Costanti/////

DualVNH5019MotorShield driver1 = DualVNH5019MotorShield(3, 4, 2, 20, 20, 9, 10, 8, 20, 20);
DualVNH5019MotorShield driver2 = DualVNH5019MotorShield(22, 21, 23, 20, 20, 14, 13, 15, 20, 20);

//Variabili che non mi interessa salvare

#define encoderA1
#define encoderB1

#define encoderA2
#define encoderB2

#define encoderA3
#define encoderB3

#define encoderA4
#define encoderB4

int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
int counter4 = 0;

int buzzer = 26; //buzzer
int sound = 1000; //suono 

File myFile;

//Variabili che voglio salvare

/////Setup/////

void setup() {

  //PinModes
  pinMode(buzzer, OUTPUT);

  pinMode(encoderA1, INPUT);
  pinMode(encoderB1, INPUT);

  pinMode(encoderA2, INPUT);
  pinMode(encoderB2, INPUT);

  pinMode(encoderA3, INPUT);
  pinMode(encoderB3, INPUT);

  pinMode(encoderA4, INPUT);
  pinMode(encoderB4, INPUT);

  //Serial Check
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  buzzzerok(buzzer, sound);
  Serial.println("Serial: GO");

  //SD check
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD: NO GO");
    buzzerfault(buzzer, sound);
  } else {
    Serial.println("SD: GO");
    buzzzerok(buzzer, sound);
  }

  //File Check & variable Extraction
  if (SD.exists("variabili.txt")) {

    myFile = SD.open("variabili.txt", FILE_READ);
    Serial.println("FILE: GO");
    buzzzerok(buzzer, sound);

  } else {

    myFile = SD.open("variabili.txt", FILE_WRITE);
    Serial.println("FILE: GO");
    buzzzerok(buzzer, sound);

  }
  //Check motors
  driver1.setSpeeds(100, 100);
  driver2.setSpeeds(100, 100);
  for (int i = 0; i < 200; i++) {
    counter1 = readencoder(encoderA1, encoderB1, counter1);
    counter2 = readencoder(encoderA2, encoderB2, counter2);
    counter3 = readencoder(encoderA3, encoderB3, counter3);
    counter4 = readencoder(encoderA4, encoderB4, counter4);
    delay(1);
  }
  driver1.setSpeeds(0, 0);
  driver2.setSpeeds(0, 0);

  if (counter1 != 0) {
    Serial.println("M1: GO");
  } else {
    Serial.println("M1:  NO GO");
  }

  if (counter2 != 0) {
    Serial.println("M2: GO");
  } else {
    Serial.println("M2:  NO GO");
  }

  if (counter3 != 0) {
    Serial.println("M3: GO");
  } else {
    Serial.println("M3:  NO GO");
  }

  if (counter4 != 0) {
    Serial.println("M4: GO");
  } else {
    Serial.println("M4:  NO GO");
  }

  //Start Check
  buzzzerok(buzzer, sound);
  Serial.println("test: GO");

}

/////Main/////

void loop() {

}

/////Funzioni/////

void buzzzerok(int buzzer, int sound) {
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

void buzzerfault(int buzzer, int sound) {

  tone(buzzer, sound);
  delay(300);
  noTone(buzzer);
  delay(700);
}

String readline() {

  String line = "";
  char ch;

  while (myFile.available()) {
    ch = myFile.read();
    if (ch == '\n') {
      return line;
    } else {
      line += ch;
    }
  }
  return "";

}

int readencoder(int inputDT, int inputCLK, int counter) {

  int currentStateCLK;
  int previousStateCLK;

  currentStateCLK = digitalRead(inputCLK);

  if (currentStateCLK != previousStateCLK) {
    if (digitalRead(inputDT) != currentStateCLK) {
      counter--;
    } else {
      counter++;
    }
  }
  previousStateCLK = currentStateCLK;

  return counter;

}
