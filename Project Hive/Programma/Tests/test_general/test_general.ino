#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Arduino_GFX_Library.h>
#include <DriverDkv.h>
#include <Adafruit_MLX90614.h>

//Costanti

#define reflection1A A10 //riflesso analogico 1
#define reflection2A A11 //riflesso analogico 2

#define reflection1D 11 //riflesso digitale 1
#define reflection2D 12 //riflesso digitale 2

#define morto1_led 20 //morto1
#define morto2_led 38 //morto2
#define morto3_led 39 //morto3

#define serial_led 7 //serial led
#define start_led 8 //start led

#define startsw 37 //start switch

#define buzzer 26 //buzzer

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

//Dischiarazioni oggetti

DriverDkv Driver1 = DriverDkv(3, 4, 2, 9, 10, 8); 
DriverDkv Driver2 = DriverDkv(22, 21, 23, 14, 13, 15); 
Adafruit_MLX90614 mlx;
File myFile; //dichiarazione file

//dichiarazione LCD
#if defined(DISPLAY_DEV_KIT)
Arduino_GFX * gfx = create_default_Arduino_GFX();
#else
Arduino_DataBus * bus = create_default_Arduino_DataBus();
Arduino_GFX * gfx = new Arduino_ILI9341(bus, TFT_RST, 0, false);
#endif

int sound = 2000; //suono 

bool ctrl = true;

//Variabili che voglio salvare

void setup() {

   mlx.begin(); 
   //Start screen
   gfx -> begin(); 
   gfx -> fillScreen(BLACK); //fill color black
   gfx -> setCursor(0, 0);
   gfx -> setTextColor(GREEN);
   gfx -> setTextSize(1);

   //PinModes
   pinMode(buzzer, OUTPUT);

   analogWriteFrequency(2, 375000);
   analogWriteFrequency(8, 375000);
   analogWriteFrequency(23, 375000);
   analogWriteFrequency(15, 375000);
   
   analogWriteResolution(8);

   //Serial Check
   Serial.begin(9600);
   while (!Serial) {
      ; // wait for serial port to connect.
   }
  
}

/////Main/////

void loop() {
  mlx.AddrSet(IR1); 
  Serial.print("IR1: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  mlx.temp1 = mlx.readObjectTempF();
  delay(250);
  mlx.AddrSet(IR2); 
  Serial.print("IR2: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  mlx.temp2 = mlx.readObjectTempF();
  delay(250);
  mlx.AddrSet(IR3); 
  Serial.print("IR3: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  mlx.temp3 = mlx.readObjectTempF();
  delay(250);
  Serial.println("Reflection 1: ");
  Serial.println(analogRead(reflection2A));
  Serial.println("Reflection 2: ");
  Serial.println(analogRead(reflection1A));
  delay(250);
  gfx -> println("Ciao");
  delay(250);
  digitalWrite(start_led, HIGH);
  digitalWrite(serial_led, HIGH);
  digitalWrite(morto1_led, HIGH);
  digitalWrite(morto2_led, HIGH);
  digitalWrite(morto3_led, HIGH);
  delay(250);
  digitalWrite(start_led, LOW);
  digitalWrite(serial_led, LOW);
  digitalWrite(morto1_led, LOW);
  digitalWrite(morto2_led, LOW);
  digitalWrite(morto3_led, LOW);
  delay(250);
  Driver1.setSpeed(200, 200);
  Driver2.setSpeed(200, 200);
  delay(250);
  Driver1.setSpeed(0, 0);
  Driver2.setSpeed(0, 0);
  while(!digitalRead(startsw)){
    Serial.println("Redy to start");
    delay(1500);
  }

}
