/*
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
*/
#define morto1_led 28 //morto1
#define morto2_led 16 //morto2
#define morto3_led 17 //morto3

#define serial_led 5 //serial led
#define start_led 6 //start led

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
/*
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

String input;
String speedL;
String speedR;
String cubi;
//Variabili che voglio salvare
*/
void setup() {
 Serial.begin(9600);
  
/*
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

     mlx.AddrSet(IR1); 
  Serial.print("IR1: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  mlx.temp1 = mlx.readObjectTempF();
  delay(250);
  mlx.AddrSet(IR2); 
  Serial.print("IR2: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  mlx.temp2 = mlx.readObjectTempF();
  delay(250);
  mlx.AddrSet(IR3); 
  Serial.print("IR3: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  mlx.temp3 = mlx.readObjectTempF();
  delay(250);
  Serial.println("Reflection 1: ");
  Serial.println(analogRead(reflection2A));
  Serial.println("Reflection 2: ");
  Serial.println(analogRead(reflection1A));
  delay(250);
  gfx -> println("Ciao");
  */
pinMode(37, INPUT);
  
}

/////Main/////

void loop() {
  
  digitalWrite(start_led, HIGH);
  delay(50);
  digitalWrite(serial_led, HIGH);
  delay(50);
  digitalWrite(morto1_led, HIGH);
  delay(50);
  digitalWrite(morto2_led, HIGH);
  delay(50);
  digitalWrite(morto3_led, HIGH);
  delay(50);
  digitalWrite(start_led, LOW);
  delay(50);
  digitalWrite(serial_led, LOW);
  delay(50);
  digitalWrite(morto1_led, LOW);
  delay(50);
  digitalWrite(morto2_led, LOW);
  delay(50);
  digitalWrite(morto3_led, LOW);
  delay(50);

  Serial.println(digitalRead(37));
  
  /*
  Driver1.setSpeeds(200, 200);
  Driver2.setSpeeds(200, 200);
//input 
    //L:100,R:100,0
        //100 sono valori di velocita
        //0 rappresenta i cubi da 1 a x che puo buttare giu
    //STOP
        //dopo aver mandato lo stop la teensy si blocca e aspetta uno stop di AK dalla raspby
    //START
        //dopo aver mandato lo start la teensy si blocca e aspetta uno start di AK dalla raspby
    
//output 
    //L:0,F:1,R:0,B:
        //i 3 sensori di calore 0=freddo 1=caldo
        //la B e il nero sotto puo essere 0 nulla 1 nero 2 checkpoint, il checkpoin piu recente e quello che riparti se ti incricchi
    //STOP
        //lo mando quando spegno con lo switch per dire mi sono incriccato
    //START
        //partenza

input = Serial.read();
gfx -> println(input);
Serial.flush();

speedL = input[2] + input[3] + input[4];
speedR = input[8] + input[9] + input[10];
cubi = input[12];

Driver1.SetSpeeds(speedL.toInt(), speedR.toInt());
Driver2.SetSpeeds(speedL.toInt(), speedR.toInt());

for(int i = 0; i < cubi.toInt(); i++){
  //cagailcubo
}


Serial.println(speedL);
Serial.println(speedR);
Serial.println(cubi);
*/


}
