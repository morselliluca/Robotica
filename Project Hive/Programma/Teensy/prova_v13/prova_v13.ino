//#include <SD.h>
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

#define morto1_led 28 //morto1
#define morto2_led 16 //morto2
#define morto3_led 17 //morto3

#define serial_led 5 //serial led
#define start_led 6 //start led

#define startsw 37 //start switch

#define buzzer 26 //buzzer

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

//indirizzi I2C

#define IR1 0x5C //indirizzo ir davanti
#define IR2 0x5A //indirizzo ir sinistra
#define IR3 0x5B //indirizzo ir destra

//Dischiarazioni oggetti

DriverDkv Driver1 = DriverDkv(3, 4, 2, 9, 10, 8);
DriverDkv Driver2 = DriverDkv(22, 21, 23, 14, 13, 15);
Adafruit_MLX90614 mlx;
//File myFile; //dichiarazione file

//dichiarazione LCD
#if defined(DISPLAY_DEV_KIT)
Arduino_GFX * gfx = create_default_Arduino_GFX();
#else
Arduino_DataBus * bus = create_default_Arduino_DataBus();
Arduino_GFX * gfx = new Arduino_ILI9341(bus, TFT_RST, 0, false);
#endif

int sound = 2000; //suono 
int reflection = 0; //rifelsso medio

String input;
String speedL;
String speedR;
String cubi;

const int tonePin = 12;  // for rEDI board

#define OCTAVE_OFFSET 0

// These values can also be found as constants in the Tone library (Tone.h)
int notes[] = { 0,
262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
};

const char songa[] PROGMEM = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
const char songb[] PROGMEM = "Indiana:d=4,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
const char songc[] PROGMEM = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
const char songd[] PROGMEM = "Entertainer:d=4,o=5,b=140:8d,8d#,8e,c6,8e,c6,8e,2c.6,8c6,8d6,8d#6,8e6,8c6,8d6,e6,8b,d6,2c6,p,8d,8d#,8e,c6,8e,c6,8e,2c.6,8p,8a,8g,8f#,8a,8c6,e6,8d6,8c6,8a,2d6";
const char songe[] PROGMEM = "Muppets:d=4,o=5,b=250:c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,8a,8p,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,8e,8p,8e,g,2p,c6,c6,a,b,8a,b,g,p,c6,c6,a,8b,a,g.,p,e,e,g,f,8e,f,8c6,8c,8d,e,8e,d,8d,c";
const char songf[] PROGMEM = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
const char songg[] PROGMEM = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
const char songh[] PROGMEM = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
const char songi[] PROGMEM = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
const char songj[] PROGMEM = "MASH:d=8,o=5,b=140:4a,4g,f#,g,p,f#,p,g,p,f#,p,2e.,p,f#,e,4f#,e,f#,p,e,p,4d.,p,f#,4e,d,e,p,d,p,e,p,d,p,2c#.,p,d,c#,4d,c#,d,p,e,p,4f#,p,a,p,4b,a,b,p,a,p,b,p,2a.,4p,a,b,a,4b,a,b,p,2a.,a,4f#,a,b,p,d6,p,4e.6,d6,b,p,a,p,2b";
const char songk[] PROGMEM = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
const char songl[] PROGMEM = "GoodBad:d=4,o=5,b=56:32p,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,d#,32a#,32d#6,32a#,32d#6,8a#.,16f#.,16g#.,c#6,32a#,32d#6,32a#,32d#6,8a#.,16f#.,32f.,32d#.,c#,32a#,32d#6,32a#,32d#6,8a#.,16g#.,d#";
const char songm[] PROGMEM = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
const char songn[] PROGMEM = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
const char songo[] PROGMEM = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
const char songp[] PROGMEM = "Jeopardy:d=4,o=6,b=125:c,f,c,f5,c,f,2c,c,f,c,f,a.,8g,8f,8e,8d,8c#,c,f,c,f5,c,f,2c,f.,8d,c,a#5,a5,g5,f5,p,d#,g#,d#,g#5,d#,g#,2d#,d#,g#,d#,g#,c.7,8a#,8g#,8g,8f,8e,d#,g#,d#,g#5,d#,g#,2d#,g#.,8f,d#,c#,c,p,a#5,p,g#.5,d#,g#";
const char songq[] PROGMEM = "Gadget:d=16,o=5,b=50:32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,32d#,32f,32f#,32g#,a#,d#6,4d6,32d#,32f,32f#,32g#,a#,f#,a,f,g#,f#,8d#";
const char songr[] PROGMEM = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
const char songs[] PROGMEM = "MahnaMahna:d=16,o=6,b=125:c#,c.,b5,8a#.5,8f.,4g#,a#,g.,4d#,8p,c#,c.,b5,8a#.5,8f.,g#.,8a#.,4g,8p,c#,c.,b5,8a#.5,8f.,4g#,f,g.,8d#.,f,g.,8d#.,f,8g,8d#.,f,8g,d#,8c,a#5,8d#.,8d#.,4d#,8d#.";
const char songt[] PROGMEM = "LeisureSuit:d=16,o=6,b=56:f.5,f#.5,g.5,g#5,32a#5,f5,g#.5,a#.5,32f5,g#5,32a#5,g#5,8c#.,a#5,32c#,a5,a#.5,c#.,32a5,a#5,32c#,d#,8e,c#.,f.,f.,f.,f.,f,32e,d#,8d,a#.5,e,32f,e,32f,c#,d#.,c#";
const char songu[] PROGMEM = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
const char songv[] PROGMEM = "TMNT:d=4,o=5,b=100:8e,8f#,8e,8f#,8e,16f#,8e.,8f#,8g,8a,8g,8a,8g,16a,8g.,8a,8c6,8d6,8c6,8d6,8c6,16d6,8c.6,8d6,16a,16a,16a,16a,8g,8a,8p,16a,16a,16a,16a";
const char songw[] PROGMEM = "BackFuture:d=4,o=5,b=160:32p,p,8c.,16p,g,16p,16c.6,16p,a#.,16p,16a,16p,16g,16p,8a,16p,8g,16p,8f,16p,1g.,1p,g.,16p,c.,16p,2f#.,16p,32g.,32p,32a.,32p,8g,32p,8e,32p,8c,32p,f#,16p,32g.,32p,32a.,32p,8g.,32p,8d.,32p,8g.,32p,8d.6,32p,d6,16p,c#6,16p,32b.,32p,32c#.6,32p,2d6";
const char songx[] PROGMEM = "Thriller:d=8,o=5,b=112:b,d6,b,e6,16p,2d6,4p,d6,16p,c#6,16p,b,4p,p,b,b,32a,16p,32p,a,16g,g,16p,e,g,a,b,a,a,16g,b";
const char songy[] PROGMEM = "SuperMan:d=4,o=5,b=180:32p,8g,8g,8g,c6,8c6,2g6,8p,8g6,8a.6,16g6,8f6,1g6,8p,8g,8g,8g,c6,8c6,2g6,8p,8g6,8a.6,16g6,8f6,8a6,2g.6,p,8c6,8c6,8c6,2b.6,g.6,8c6,8c6,8c6,2b.6,g.6,8c6,8c6,8c6,8b6,8a6,8b6,2c7,8c6,8c6,8c6,8c6,8c6,2c.6";
const char *allsongs[] = {songa,
                    songb, 
                    songc,
                    songd, 
                    songe, 
                    songf, 
                    songg, 
                    songh, 
                    songi, 
                    songj, 
                    songk, 
                    songl, 
                    songm, 
                    songn, 
                    songo, 
                    songp, 
                    songq, 
                    songr, 
                    songs, 
                    songt, 
                    songu,
                    songv,
                    songw,      
                    songx,
                    songy
                    };


void setup() {
    Serial.begin(9600);

    mlx.begin();
    //Start screen
    gfx -> begin();
    gfx -> fillScreen(BLACK); //fill color black
    gfx -> setCursor(0, 0);
    gfx -> setTextColor(GREEN);
    gfx -> setTextSize(1);

    //PinModes
    pinMode(buzzer, OUTPUT);
    pinMode(startsw, INPUT);

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
          digitalWrite(serial_led, HIGH);
          delay(50);
          digitalWrite(serial_led, LOW);
          delay(50);
          digitalWrite(serial_led, HIGH);
          delay(50);
          digitalWrite(serial_led, LOW);
          delay(50);
          digitalWrite(serial_led, HIGH);
          delay(50);
          digitalWrite(serial_led, LOW);
          delay(50);
          digitalWrite(serial_led, HIGH);

    mlx.AddrSet(IR1);
    Serial.print("IR1: ");
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = ");
    Serial.print(mlx.readObjectTempC());
    Serial.println("*C");
    mlx.temp1 = mlx.readObjectTempF();
    delay(250);
    mlx.AddrSet(IR2);
    Serial.print("IR2: ");
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = ");
    Serial.print(mlx.readObjectTempC());
    Serial.println("*C");
    mlx.temp2 = mlx.readObjectTempF();
    delay(250);
    mlx.AddrSet(IR3);
    Serial.print("IR3: ");
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = ");
    Serial.print(mlx.readObjectTempC());
    Serial.println("*C");
    mlx.temp3 = mlx.readObjectTempF();
    delay(250);
    Serial.println("Reflection 1: ");
    Serial.println(analogRead(reflection2A));
    Serial.println("Reflection 2: ");
    Serial.println(analogRead(reflection1A));
    reflection = (analogRead(reflection2A) + analogRead(reflection1A)) / 2;
    delay(250);
    gfx -> println("Ciao");
    while (!digitalRead(startsw)) {
        Serial.println("redy to start");
        delay(1000);
    }
    Serial.println("start");

    input = Serial.read();
    while (input != "start") {
        input = Serial.read();
        Serial.println("start");
          digitalWrite(start_led, HIGH);
          delay(50);
          digitalWrite(start_led, LOW);
          delay(50);
          digitalWrite(start_led, HIGH);
          delay(50);
          digitalWrite(start_led, LOW);
          delay(50);
          digitalWrite(start_led, HIGH);
          delay(50);
          digitalWrite(start_led, LOW);
          delay(50);
          digitalWrite(start_led, HIGH);
    }
      play_rtttl(songw);

}

/////Main/////

void loop() {
    while(digitalRead(startsw)) {
        digitalWrite(start_led, HIGH);
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

        Driver1.setSpeeds(speedL.toInt(), speedR.toInt());
        Driver2.setSpeeds(speedL.toInt(), speedR.toInt());

        for (int i = 0; i < cubi.toInt(); i++) {
            //cagailcubo
        }

        Serial.println(speedL);
        Serial.println(speedR);
        Serial.println(cubi);
    }
    digitalWrite(start_led, LOW);
    Serial.println("stop");

}

void dead() {
    digitalWrite(morto1_led, HIGH);
    digitalWrite(morto2_led, HIGH);
    digitalWrite(morto3_led, HIGH);
    delay(200);
    digitalWrite(morto1_led, LOW);
    digitalWrite(morto2_led, LOW);
    digitalWrite(morto3_led, LOW);
}

void bttf() {
  digitalWrite(morto1_led, HIGH);
  delay(50);
  digitalWrite(morto2_led, HIGH);
  delay(50);
  digitalWrite(morto3_led, HIGH);
  delay(50);
  digitalWrite(morto1_led, LOW);
  delay(50);
  digitalWrite(morto2_led, LOW);
  delay(50);
  digitalWrite(morto3_led, LOW);
  delay(50);
}

#define isdigit(n) (n >= '0' && n <= '9')

void play_rtttl(const char *signMessage)
{

  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  int pauses = 2;

  int p = 0;

 
  while(pgm_read_byte_near(signMessage + p) != ':') p++;    // ignore name
  p++;                     // skip ':'

  // get default duration
  if(pgm_read_byte_near(signMessage + p) == 'd')
  {
    p++; p++;              // skip "d="
    num = 0;
    while(isdigit(pgm_read_byte_near(signMessage + p)))
    {
      num = (num * 10) + (pgm_read_byte_near(signMessage + p++) - '0');
    }
    if(num > 0) default_dur = num;
    p++;                   // skip comma
  }

  Serial.print("ddur: "); Serial.println(default_dur, 10);

  // get default octave
  if(pgm_read_byte_near(signMessage + p) == 'o')
  {
    p++; p++;              // skip "o="
    num = pgm_read_byte_near(signMessage + p++) - '0';
    if(num >= 3 && num <=7) default_oct = num;
    p++;                   // skip comma
  }

  Serial.print("doct: "); Serial.println(default_oct, 10);

  // get BPM
  if(pgm_read_byte_near(signMessage + p) == 'b')
  {
    p++; p++;              // skip "b="
    num = 0;
    while(isdigit(pgm_read_byte_near(signMessage + p)))
    {
      num = (num * 10) + (pgm_read_byte_near(signMessage + p++) - '0');
    }
    bpm = num;
    p++;                   // skip colon
  }

  Serial.print("bpm: "); Serial.println(bpm, 10);

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  Serial.print("wn: "); Serial.println(wholenote, 10);


  // now begin note loop
  while(pgm_read_byte_near(signMessage + p))
  {
    // first, get note duration, if available
    num = 0;
    while(isdigit(pgm_read_byte_near(signMessage + p)))
    {
      num = (num * 10) + (pgm_read_byte_near(signMessage + p++) - '0');
    }
   
    if(num) duration = wholenote / num;
    else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

    // now get the note
    note = 0;

    switch(pgm_read_byte_near(signMessage + p))
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    // now, get optional '#' sharp
    if(pgm_read_byte_near(signMessage + p) == '#')
    {
      note++;
      p++;
    }

    // now, get optional '.' dotted note
    if(pgm_read_byte_near(signMessage + p) == '.')
    {
      duration += duration/2;
      p++;
    }
 
    // now, get scale
    if(isdigit(pgm_read_byte_near(signMessage + p)))
    {
      scale = pgm_read_byte_near(signMessage + p) - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if(pgm_read_byte_near(signMessage + p) == ',')
      p++;       // skip comma for next note (or we may be at the end)

    // now play the note

    if(note)
    {
 
      tone(tonePin, notes[(scale - 4) * 12 + note]);
      delay(duration);
      noTone(tonePin);
    }
    else
    {
      
      delay(duration);
      if(!pauses && duration) return;
      if(duration > 950) pauses--; 
    }
  }
}

char c;
