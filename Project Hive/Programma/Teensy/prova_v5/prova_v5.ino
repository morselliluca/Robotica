#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Arduino_GFX_Library.h>
#include <DualVNH5019MotorShield.h>

//Costanti

#define encoderA1 29 //encoder A motore 1
#define encoderB1 30 //encoder B motore 1

#define encoderA2 31 //encoder A motore 2
#define encoderB2 32 //encoder B motore 2

#define encoderA3 33 //encoder A motore 3
#define encoderB3 34 //encoder B motore 3

#define encoderA4 35 //encoder A motore 4
#define encoderB4 36 //encoder B motore 4

#define reflection1A A10 //riflesso analogico 1
#define reflection2A A11 //riflesso analogico 2

#define reflection1D 11 //riflesso digitale 1
#define reflection2D 12 //riflesso digitale 2

#define startsw 37 //start switch

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

//indirizzi I2C

#define IR1 0x5C //indirizzo ir davanti
#define IR2 0x5A //indirizzo ir sinistra
#define IR3 0x5B //indirizzo ir destra

#define gyroaddr 55 //indirizzo Gyro

//Dischiarazioni oggetti

DualVNH5019MotorShield driver1 = DualVNH5019MotorShield(3, 4, 2, 20, 20, 9, 10, 8, 20, 20);       //dichiarazione driver 1
DualVNH5019MotorShield driver2 = DualVNH5019MotorShield(22, 21, 23, 20, 20, 14, 13, 15, 20, 20);  //dichiarazione driver 2 

Adafruit_BNO055 bno = Adafruit_BNO055(gyroaddr); //dichiarazione giroscopio

File myFile; //dichiarazione file

//dichiarazione LCD
#if defined(DISPLAY_DEV_KIT)
Arduino_GFX * gfx = create_default_Arduino_GFX();
#else
Arduino_DataBus * bus = create_default_Arduino_DataBus();
Arduino_GFX * gfx = new Arduino_ILI9341(bus, TFT_RST, 0, false);
#endif

//Variabili che non salvo

int counter1 = 0; //counter encoder 1
int counter2 = 0; //counter encoder 2
int counter3 = 0; //counter encoder 3
int counter4 = 0; //counter encoder 4

int buzzer = 26; //buzzer
int sound = 1500; //suono 

//Variabili che voglio salvare

void setup() {

   //Start screen
   gfx -> begin(); 
   gfx -> fillScreen(BLACK); //fill color black
   gfx -> setCursor(0, 0);
   gfx -> setTextColor(GREEN);
   gfx -> setTextSize(1);

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
   gfx -> println("Serial: GO");

   //SD check
   if (!SD.begin(BUILTIN_SDCARD)) {
      Serial.println("SD: NO GO");
      gfx -> println("SD: NO GO");
      buzzerfault(buzzer, sound);
   } else {
      Serial.println("SD: GO");
      gfx -> println("SD: GO");
      buzzzerok(buzzer, sound);
   }

   //File Check & variable Extraction
   if (SD.exists("variabili.txt")) {
      myFile = SD.open("variabili.txt", FILE_READ);
      Serial.println("FILE: GO");
      gfx -> println("FILE: GO");
      buzzzerok(buzzer, sound);
   } else {
      myFile = SD.open("variabili.txt", FILE_WRITE);
      Serial.println("FILE: GO");
      gfx -> println("FILE: GO");
      buzzzerok(buzzer, sound);

   }
   
   //Check motors
   driver1.setSpeeds(100, 100); //imposto velocita driver 1
   driver2.setSpeeds(100, 100); //imposto velocita driver 2
   for (int i = 0; i < 200; i++) {
      counter1 = readencoder(encoderA1, encoderB1, counter1); //read encoder 1
      counter2 = readencoder(encoderA2, encoderB2, counter2); //read encoder 2
      counter3 = readencoder(encoderA3, encoderB3, counter3); //read encoder 3
      counter4 = readencoder(encoderA4, encoderB4, counter4); //read encoder 4
      delay(1);
   }
   driver1.setSpeeds(0, 0); //imposto velocita driver 1
   driver2.setSpeeds(0, 0); //imposto velocita driver 2

   if (counter1 != 0) {
      Serial.println("M1: GO");
      gfx -> println("M1: GO");
      buzzzerok(buzzer, sound);
   } else {
      Serial.println("M1: NO GO");
      gfx -> println("M1: NO GO");
      buzzerfault(buzzer, sound);
   }

   if (counter2 != 0) {
      Serial.println("M2: GO");
      gfx -> println("M2: GO");
      buzzzerok(buzzer, sound);
   } else {
      Serial.println("M2: NO GO");
      gfx -> println("M2: NO GO");
      buzzerfault(buzzer, sound);
   }

   if (counter3 != 0) {
      Serial.println("M3: GO");
      gfx -> println("M3: GO");
      buzzzerok(buzzer, sound);
   } else {
      Serial.println("M3: NO GO");
      gfx -> println("M3: NO GO");
      buzzerfault(buzzer, sound);
   }

   if (counter4 != 0) {
      Serial.println("M4: GO");
      gfx -> println("M4: GO");
      buzzzerok(buzzer, sound);
   } else {
      Serial.println("M4: NO GO");
      gfx -> println("M4: NO GO");
      buzzerfault(buzzer, sound);
   }

   //Check reflection
   if (analogRead(reflection1A) > 0) {
      Serial.println("Reflection 1: GO");
      gfx -> println("Reflection 1: GO");
      buzzzerok(buzzer, sound);
   } else {
      Serial.println("Reflection 1: NO GO");
      gfx -> println("Reflection 1: NO GO");
      buzzerfault(buzzer, sound);
   }

   if (analogRead(reflection2A) > 0) {
      Serial.println("Reflection 2: GO");
      gfx -> println("Reflection 2: GO");
      buzzzerok(buzzer, sound);
   } else {
      Serial.println("Reflection 2: NO GO");
      gfx -> println("Reflection 2: NO GO");
      buzzerfault(buzzer, sound);
   }

   //Gyro check
   if (bno.begin()) {
      Serial.println("Gyro: GO");
      gfx -> println("Gyro: GO");
      buzzzerok(buzzer, sound);
   } else {
      Serial.println("Gyro: NO GO");
      gfx -> println("Gyro: NO GO");
      buzzerfault(buzzer, sound);
   }
   bno.setExtCrystalUse(true);

   //Start Check
   buzzzerok(buzzer, sound);
   Serial.println("test: GO");
   gfx -> println("test: GO");

}

/////Main/////

void loop() {

}

/////Funzioni/////

void buzzzerok(int buzzer, int sound) {

   tone(buzzer, sound);
   delay(200);
   noTone(buzzer);
   tone(buzzer, sound);
   delay(200);
   noTone(buzzer);
   delay(700);

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

   int currentStateCLK = 0;
   int previousStateCLK = 0;

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
