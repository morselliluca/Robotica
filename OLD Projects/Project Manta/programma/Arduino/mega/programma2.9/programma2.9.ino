#include <SPI.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <DHT.h>

//costanti

#define ma1 6
#define mb1 7
#define pwm1 2

#define ma2 8
#define mb2 9
#define pwm2 3

#define ma3 11
#define mb3 10
#define pwm3 4

#define ma4 13
#define mb4 12
#define pwm4 5

#define velocita 90

#define outputA1 22
#define outputB1 23
#define outputA2 24
#define outputB2 25
#define outputA3 26
#define outputB3 27
#define outputA4 28
#define outputB4 29

#define pingPin 32
#define pingPin1 33
#define pingPin2 34
#define pingPin3 35
#define pingPin4 36
#define pingPin5 37
#define pingPin6 38
#define pingPin7 39
#define buttonPin 50
#define DHTPIN 46
#define DHTTYPE DHT11


MPU6050 mpu6050(Wire);
DHT dht(DHTPIN, DHTTYPE);

int counter1 = 0;
int aState1;
int aLastState1;

int counter2 = 0;
int aState2;
int aLastState2;

int counter3 = 0;
int aState3;
int aLastState3;

int counter4 = 0;
int aState4;
int aLastState4;

int media = 0;
int pencoder[3];

int erroreM = 5;  //errore percentuale ancoder
int angolostandard = 90;  //angolo

int vel = 90;
int Nping = 2;

int pingArray[4][2] = { {pingPin, pingPin7},   //davanti
                        {pingPin1, pingPin2},  //sinistra
                        {pingPin3, pingPin4}, //dietro
                        {pingPin5, pingPin6}  //destra
                      }; 


//float

float medie[4][2];
float somma;

float angoloiniziale = 0;
float kAng = 0.9;  //costante rallentamento
float kFwd = 0.9;  //costante rallentamento
float vsuono;

//char

char raspy[3][3];

char mystr[2];


//bool

bool controllo;
bool msg = true;


//byte

byte input;


//long

long duration;
long cm;
double Suono;
long Temp;
long Hum;
long distanza = 8;  //distanza a cui dice che ce un muro in mm
long microspulse;    //variabile usata per memorizzare il DeltaT in microsecondi
 

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  Wire.begin();
  dht.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(44, OUTPUT);

  pinMode(pwm1, OUTPUT);  //we have to set PWM pin as output
  pinMode(ma1, OUTPUT); //Logic pins are also set as output
  pinMode(mb1, OUTPUT);

  pinMode(pwm2, OUTPUT);  //we have to set PWM pin as output
  pinMode(ma2, OUTPUT); //Logic pins are also set as output
  pinMode(mb2, OUTPUT);

  pinMode(pwm3, OUTPUT);  //we have to set PWM pin as output
  pinMode(ma3, OUTPUT); //Logic pins are also set as output
  pinMode(mb3, OUTPUT);

  pinMode(pwm4, OUTPUT);  //we have to set PWM pin as output
  pinMode(ma4, OUTPUT); //Logic pins are also set as output
  pinMode(mb4, OUTPUT);

  pinMode(outputA1, INPUT);
  pinMode(outputB1, INPUT);
  pinMode(outputA2, INPUT);
  pinMode(outputB2, INPUT);
  pinMode(outputA3, INPUT);
  pinMode(outputB3, INPUT);
  pinMode(outputA4, INPUT);
  pinMode(outputB4, INPUT);

  aLastState1 = digitalRead(outputA1);
  aLastState2 = digitalRead(outputA2);
  aLastState3 = digitalRead(outputA3);
  aLastState4 = digitalRead(outputA4);

}

void loop()
{
  //Serial1.readBytes(mystr,1);
  //Serial1.println(mystr); 

  //Serial2.readBytes(mystr,1);
  //Serial2.println(mystr); 
  
  if (Serial.available() > 0 && msg)
  {
    Serial.println("----- Test movimento motori -----");
    Serial.println("   Utilizzare WASD per muoversi  ");
    Serial.println("  Utilizzare Q ed E per ruotare  ");
    Serial.println(" Utilizzare P per usare i sensori");
    Serial.println("---------------------------------");
    msg = false;
  }
  
  inputs();
   
}

////////////////////////input/////////////////////

void inputs(){
  if (Serial.available()>0){
    input = Serial.read();
     if (input == 'w')     { digitalWrite(44, HIGH); movimento('w'); digitalWrite(44, LOW); Serial.println("f");}
     else if (input == 'a'){ digitalWrite(44, HIGH); movimento('a'); digitalWrite(44, LOW); Serial.println("f");}
     else if (input == 's'){ digitalWrite(44, HIGH); movimento('s'); digitalWrite(44, LOW); Serial.println("f");}
     else if (input == 'd'){ digitalWrite(44, HIGH); movimento('d'); digitalWrite(44, LOW); Serial.println("f");}
     else if (input == 'q'){ digitalWrite(44, HIGH); movimento('q'); digitalWrite(44, LOW); Serial.println("f");}
     else if (input == 'e'){ digitalWrite(44, HIGH); movimento('e'); digitalWrite(44, LOW); Serial.println("f");}
     else if (input == 't'){ digitalWrite(44, HIGH); test(); digitalWrite(44, LOW); Serial.println("f");}
     else if (input == 'p'){ digitalWrite(44, HIGH); prova(); digitalWrite(44, LOW); Serial.println("f");}
     else if (input == 'f'){ motori(0, 0, 0, 0, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);}
    }
}


////////////////////////movimento/////////////////////


void movimento(char direzione)
{
  //avanti
  if (direzione == 'w')
  {
    do {
      media = encoder();
      motori(vel, vel, vel, vel, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW);
      vel = vel = velocita - media * kFwd;
      Serial.println(media);
      delay(1);
    } while (media < 20000);
    vel = 90;
    media = 0;
    counter1 = 0;
    counter2 = 0;
    counter3 = 0;
    counter4 = 0;
    motori(0, 0, 0, 0, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);

  }

  //Indietro
  else if (direzione == 's')
  {
    do {
      media = encoder();
      motori(vel, vel, vel, vel, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH);
      vel = vel = velocita - media * kFwd;
      Serial.println(media);
      delay(1);
    } while (media < 20000);
    vel = 90;
    media = 0;
    counter1 = 0;
    counter2 = 0;
    counter3 = 0;
    counter4 = 0;
    motori(0, 0, 0, 0, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);

  }

  //Girasinistra
  else if (direzione == 'q')
  {
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    mpu6050.update();
    angoloiniziale = abs(mpu6050.getAngleZ());
    Serial.println(angoloiniziale);

    do {
      motori(vel, vel, vel, vel, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH);
      mpu6050.update();
      vel = velocita - (abs(mpu6050.getAngleZ() - angoloiniziale) * kAng);
      Serial.println(vel);
    } while (abs(mpu6050.getAngleZ() - angoloiniziale) <= angolostandard);
    motori(0, 0, 0, 0, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);

  }

  //Giradestra
  else if (direzione == 'e')
  {
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    mpu6050.update();
    angoloiniziale = abs(mpu6050.getAngleZ());
    Serial.println(angoloiniziale);

    do {
      motori(vel, vel, vel, vel, HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW);
      mpu6050.update();
      vel = velocita - (abs(mpu6050.getAngleZ() - angoloiniziale) * kAng);
      Serial.println(vel);
    } while (abs(mpu6050.getAngleZ() - angoloiniziale) <= angolostandard);
    motori(0, 0, 0, 0, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);

  }

  //Sinistra
  else if (direzione == 'a')
  {
    do {
      delay(1);
      motori(vel, vel, vel, vel, LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW);
    } while (Serial.read() == 't');
    motori(0, 0, 0, 0, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);

  }

  //Destra
  else if (direzione == 'd')
  {
    do {
      delay(1);
      motori(vel, vel, vel, vel, HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH);
    } while (Serial.read() == 't');
    motori(0, 0, 0, 0, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);

  }
}

///////////////////////////////encoder/////////////////////////////////

int encoder()
{
  aState1 = digitalRead(outputA1);
  aState2 = digitalRead(outputA2);
  aState3 = digitalRead(outputA3);
  aState4 = digitalRead(outputA4);

  //conta endoder1

  if (aState1 != aLastState1)
  {
    if (digitalRead(outputB1) != aState1)
    {
      counter1++;
    }
    else
    {
      counter1--;
    }
  }

  aLastState1 = aState1;

  //conta endoder2

  if (aState2 != aLastState2)
  {
    if (digitalRead(outputB2) != aState2)
    {
      counter2++;
    }
    else
    {
      counter2--;
    }
  }

  aLastState2 = aState2;

  //conta endoder3

  if (aState3 != aLastState3)
  {
    if (digitalRead(outputB3) != aState3)
    {
      counter3++;
    }
    else
    {
      counter3--;
    }
  }

  aLastState3 = aState3;

  //conta endoder4

  if (aState4 != aLastState4)
  {
    if (digitalRead(outputB4) != aState4)
    {
      counter4++;
    }
    else
    {
      counter4--;
    }
  }

  aLastState4 = aState4;

  if (counter1 > counter2 && counter1 > counter3 && counter1 > counter4)
  {
    media = ErroreEncoder(counter1, counter2, counter3, counter4);
  }
  else if (counter2 > counter1 && counter2 > counter3 && counter2 > counter4)
  {
    media = ErroreEncoder(counter2, counter1, counter3, counter4);
  }
  else if (counter3 > counter1 && counter3 > counter2 && counter3 > counter4)
  {
    media = ErroreEncoder(counter3, counter1, counter2, counter4);
  }
  else if (counter4 > counter1 && counter4 > counter2 && counter4 > counter3)
  {
    media = ErroreEncoder(counter4, counter1, counter2, counter3);
  }
  else
  {
    media = abs(counter1) + abs(counter2) + abs(counter3) + abs(counter4);
    media /= 4;
  }

  return media;
}

int ErroreEncoder(int countererr, int counter1, int counter2, int counter3)
{
  media = abs(counter1) + abs(counter2) + abs(counter3);
  media /= 3;
  if ((media - media / 100 *erroreM)<countererr < (media + media / 100 *erroreM))
  {
    //funziona bene
    media = abs(countererr) + abs(counter1) + abs(counter2) + abs(counter3);
    media /= 4;
  }
  else
  {
    //da problemi viene ignorato          
    media = abs(counter1) + abs(counter2) + abs(counter3);
    media /= 3;
  }

  return media;
}

////////////////////////driver/////////////////////////////

void motori(int velocita1, int velocita2, int velocita3, int velocita4, int driverMB1, int driverMA1, int driverMB2, int driverMA2, int driverMB3, int driverMA3, int driverMB4, int driverMA4)
{
  analogWrite(pwm1, velocita1);
  analogWrite(pwm2, velocita2);
  analogWrite(pwm3, velocita3);
  analogWrite(pwm4, velocita4);
  
  digitalWrite(mb1, driverMB1);
  digitalWrite(ma1, driverMA1);
  
  digitalWrite(mb2, driverMB2);
  digitalWrite(ma2, driverMA2);
  
  digitalWrite(mb3, driverMB3);
  digitalWrite(ma3, driverMA3);
                  
  digitalWrite(mb4, driverMB4);
  digitalWrite(ma4, driverMA4);

}

////////////////////////sensori/////////////////////////////

void prova(){
  for (int i=0; i<2; i++){
      sensori();
      camere();
      delay(100);
      }
      
  for (int i=0; i<3; i++){
    for (int j=0; j<3; j++){
      Serial.print(raspy[i][j]);
      }
      
    Serial.println();
    
  }
  
}


void sensori(){
  pulisciseriali();

  camere();
  delay(1);
   for(int i = 0; i < 4; i++){ 
   for(int y = 0; y < 2; y++){


      digitalWrite(pingArray[i][y], LOW);                          //pin portato a low (per scamaranzia)
      delayMicroseconds(5);                                 //dalay 5 microsecondi
      digitalWrite(pingArray[i][y], HIGH);                         //pin portato a high (inizio emisione impulso)
      delayMicroseconds(10);                                //delay di 10 secondi (nonchè durata approssimativa dell'impulso)
      digitalWrite(pingArray[i][y], LOW);                          //pin portato a low
      microspulse = pulseIn(pingArray[i][y], HIGH);                //calcolo durata ricezzione impulso
      float temp = dht.readTemperature();                   //lettura temperatura
      vsuono = 331.3 + (0.606 * 20);                          //calcolo della velocità del suono in m/s
      medie[i][y] = microspulse * (vsuono / 10000 ) / 2;              //calcolo distanza in cm:
      Serial.println(microspulse * (331.3 / 10000 ) / 2);
   }
   
  }


  if(medie[0][0]<distanza && medie[0][1]<distanza){ //destra
    raspy[2][0]='1';
    raspy[2][2]='1';
  }if(medie[1][0]<distanza && medie[1][1]<distanza){ //sinistra
    raspy[0][2]='1';
    raspy[2][2]='1';
  }if(medie[2][0]<distanza && medie[2][1]<distanza){ //sopra
    raspy[0][2]='1';
    raspy[0][0]='1';
  }if(medie[3][0]<distanza && medie[3][1]<distanza){ //sotto
    raspy[0][0]='1';
    raspy[2][0]='1';  
  }
 
}

  void camere(){ //termiche
    for (int g=0; g<3; g++){
  for (int f=0; f<3; f++){
      raspy[g][f]='0';
    }
  }
    Serial1.write('1');
Serial2.print("\n");
    Serial1.flush();
  // read 1:
  if (Serial1.available()) {
    char inByte = Serial1.read();
    if (inByte=='c'){
      raspy[1][2]='c';
    }
  }

Serial2.write('1');
Serial2.print("\n");
    Serial2.flush();
  // read 2:
  if (Serial2.available()) {
    char inByte = Serial2.read();
    if (inByte=='c'){
      raspy[1][0]='c';
    }
  }
  }

 void pulisciseriali(){

  Serial.flush();

  Serial1.flush();

  Serial2.flush();
 }

 void test(){
  for(int i = 0; i < 20; i++){
      Serial.print(mpu6050.getAngleZ());
  }

 }
