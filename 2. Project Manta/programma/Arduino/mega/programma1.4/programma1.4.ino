#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>

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

#define velocita 125

bool msg = true;
byte input = "";





 #define outputA1 22
 #define outputB1 23

 #define outputA2 24
 #define outputB2 25

 #define outputA3 26
 #define outputB3 27

 #define outputA4 28
 #define outputB4 29
 
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

 int media=0;
 bool controllo;
 int pencoder[3];



#define pingPin 32
#define pingPin1 33
#define pingPin2 34
#define pingPin3 35
#define pingPin4 36
#define pingPin5 37
#define pingPin6 38
#define pingPin7 39
#define buttonPin 50
char raspy[3][3];
int pingArray[4][2] = { {pingPin, pingPin7},   //davanti
                        {pingPin1, pingPin2},  //sinistra
                        {pingPin3, pingPin4}, //dietro
                        {pingPin5, pingPin6}  //destra
                      }; 
long duration, cm;
float medie[4][2]; 
float somma;
int errore;
char mystr[2];


 int vel1 = 90; 
 int vel2 = 90;
 int vel3 = 90;
 int vel4 = 90; 







#define MPU 0x68
double AcX,AcY,AcZ;
int angolo, angoloiniziale;



//SoftwareSerial mySerial1(16, 17); // RX, TX
//SoftwareSerial mySerial2(18, 19); // RX, TX



void setup()
{
init_MPU();

  
pinMode(pwm1,OUTPUT) ;   //we have to set PWM pin as output
pinMode(ma1,OUTPUT) ;  //Logic pins are also set as output
pinMode(mb1,OUTPUT) ;

pinMode(pwm2,OUTPUT) ;   //we have to set PWM pin as output
pinMode(ma2,OUTPUT) ;  //Logic pins are also set as output
pinMode(mb2,OUTPUT) ;

pinMode(pwm3,OUTPUT) ;   //we have to set PWM pin as output
pinMode(ma3,OUTPUT) ;  //Logic pins are also set as output
pinMode(mb3,OUTPUT) ;

pinMode(pwm4,OUTPUT) ;   //we have to set PWM pin as output
pinMode(ma4,OUTPUT) ;  //Logic pins are also set as output
pinMode(mb4,OUTPUT) ;

   pinMode (outputA1,INPUT);
   pinMode (outputB1,INPUT);
   pinMode (outputA2,INPUT);
   pinMode (outputB2,INPUT);
   pinMode (outputA3,INPUT);
   pinMode (outputB3,INPUT);
   pinMode (outputA4,INPUT);
   pinMode (outputB4,INPUT);
   
   Serial.begin (9600);
   
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
  
  if (Serial.available()>0 && msg){
  Serial.println("----- Test movimento motori -----");
  Serial.println("   Utilizzare WASD per muoversi  ");
  Serial.println("  Utilizzare Q ed E per ruotare  ");
  Serial.println(" Utilizzare P per usare i sensori");
  Serial.println("---------------------------------");
  msg = false;
  }
  if (Serial.available()>0){
    input = Serial.read();
    if (input == 'w') {avanti(255);}
     else if (input == 'a'){ sinistra(255);}
     else if (input == 's'){ indietro(255);}
     else if (input == 'd'){ destra(255);}
     else if (input == 'q'){ girasinistra(255);}
     else if (input == 'e'){ giradestra(255);}
     else if (input == 'p'){ sensori();}
     else if (input == 'f'){ alt();}
  }
}







///////////////////////////////motori/////////////////////////////////

void avanti (int vel) { //direzioni dei motori messe a caso 😂/
  //motors(vel,vel,vel,vel,1,1,1,1);
  movimento('w');
}
void indietro (int vel) {
  //motors(vel,vel,vel,vel,2,2,2,2);
  movimento('s');
}
void destra (int vel) {
  //motors(vel,vel,vel,vel,1,2,1,2);
  movimento('d');
}
void sinistra (int vel) {
  //motors(vel,vel,vel,vel,2,1,2,1);
  movimento('a');
}
void giradestra (int vel) {
  //motors(vel,vel,vel,vel,1,1,2,2);
  movimento('e');
}
void girasinistra (int vel) {
  //motors(vel,vel,vel,vel,2,2,1,1);
  movimento('q');
}
void ferma () {
  //motors(0,0,0,0,0,0,0,0);
  alt();
}



////////////////////////movimento/////////////////////

void movimento (char direzione){
    
   if(direzione=='w'){

    do{
    media=encoder();
    fwd(vel1, vel2, vel3, vel4);
    Serial.println(media);
    delay(1);
    }while(media<200);
    media=0;
    counter1=0;
    counter2=0;
    counter3=0;
    counter4=0;
    alt();
    
    //////////////avanti////////////
    }else if(direzione=='s'){
      
    do{
    media=encoder();
    bk(vel1, vel2, vel3, vel4);
    Serial.println(media);
    delay(1);
    }while(media<200);
    media=0;
    counter1=0;
    counter2=0;
    counter3=0;
    counter4=0;
    alt();
    //////////////indietro////////////
    }else if(direzione=='q'){
      FunctionsMPU();
      angoloiniziale=FunctionsPitchRoll(AcX, AcY, AcZ);
    do{
    FunctionsMPU();
    gsx(vel1, vel2, vel3, vel4);
    delay(1);
    angolo=abs(abs(angoloiniziale)-abs(FunctionsPitchRoll(AcX, AcY, AcZ))); 
    delay(1);
    Serial.println(angolo);
    }while(abs(angolo)<80);
    alt();
    //////////////gsinistra////////////
    }else if(direzione=='e'){
      FunctionsMPU();
      angoloiniziale=FunctionsPitchRoll(AcX, AcY, AcZ);
    do{
    FunctionsMPU();
    gdx(vel1, vel2, vel3, vel4);
    delay(1);
    angolo=abs(abs(angoloiniziale)-abs(FunctionsPitchRoll(AcX, AcY, AcZ))); 
    delay(1);
    Serial.println(angolo);
    }while(abs(angolo)<80);
    alt();
    //////////////gdestra////////////
    }else if(direzione=='a'){
      
    do{
    delay(1);
    sx(vel1, vel2, vel3, vel4);
    }while(media<200);
    alt();
    //////////////sinistra////////////
    }else if(direzione=='d'){
      
    do{
    delay(1);
    dx(vel1, vel2, vel3, vel4);
    }while(media<200);
    alt();
    //////////////destra////////////
    }
}


///////////////////////////////driver/////////////////////////////////

void fwd (int vel1, int vel2, int vel3, int vel4) {
  analogWrite(pwm1,vel1) ;
  analogWrite(pwm2,vel2) ;
  analogWrite(pwm3,vel3) ;
  analogWrite(pwm4,vel4) ;
  digitalWrite(ma1,LOW) ;
  digitalWrite(mb1,HIGH);
  digitalWrite(ma2,LOW) ;
  digitalWrite(mb2,HIGH);
  digitalWrite(ma3,LOW) ;
  digitalWrite(mb3,HIGH);
  digitalWrite(ma4,LOW) ;
  digitalWrite(mb4,HIGH);
  
}
void bk (int vel1, int vel2, int vel3, int vel4) {
  analogWrite(pwm1,vel1) ;
  analogWrite(pwm2,vel2) ;
  analogWrite(pwm3,vel3) ;
  analogWrite(pwm4,vel4) ;
  digitalWrite(mb1,LOW) ;
  digitalWrite(ma1,HIGH);
  digitalWrite(mb2,LOW) ;
  digitalWrite(ma2,HIGH);
  digitalWrite(mb3,LOW) ;
  digitalWrite(ma3,HIGH);
  digitalWrite(mb4,LOW) ;
  digitalWrite(ma4,HIGH);
}
void dx (int vel1, int vel2, int vel3, int vel4) {
  analogWrite(pwm1,vel1) ;
  analogWrite(pwm2,vel2) ;
  analogWrite(pwm3,vel3) ;
  analogWrite(pwm4,vel4) ;
  digitalWrite(ma1,LOW) ;
  digitalWrite(mb1,HIGH);
  digitalWrite(mb2,LOW) ;
  digitalWrite(ma2,HIGH);
  digitalWrite(ma3,LOW) ;
  digitalWrite(mb3,HIGH);
  digitalWrite(mb4,LOW) ;
  digitalWrite(ma4,HIGH);
}
void sx (int vel1, int vel2, int vel3, int vel4) {
  analogWrite(pwm1,vel1) ;
  analogWrite(pwm2,vel2) ;
  analogWrite(pwm3,vel3) ;
  analogWrite(pwm4,vel4) ;
  digitalWrite(mb1,LOW) ;
  digitalWrite(ma1,HIGH);
  digitalWrite(ma2,LOW) ;
  digitalWrite(mb2,HIGH);
  digitalWrite(mb3,LOW) ;
  digitalWrite(ma3,HIGH);
  digitalWrite(ma4,LOW) ;
  digitalWrite(mb4,HIGH);
}
void gdx (int vel1, int vel2, int vel3, int vel4) {
  analogWrite(pwm1,vel1) ;
  analogWrite(pwm2,vel2) ;
  analogWrite(pwm3,vel3) ;
  analogWrite(pwm4,vel4) ;
  digitalWrite(ma1,LOW) ;
  digitalWrite(mb1,HIGH);
  digitalWrite(ma2,LOW) ;
  digitalWrite(mb2,HIGH);
  digitalWrite(mb3,LOW) ;
  digitalWrite(ma3,HIGH);
  digitalWrite(mb4,LOW) ;
  digitalWrite(ma4,HIGH);
}
void gsx (int vel1, int vel2, int vel3, int vel4) {
  analogWrite(pwm1,vel1) ;
  analogWrite(pwm2,vel2) ;
  analogWrite(pwm3,vel3) ;
  analogWrite(pwm4,vel4) ;
  digitalWrite(mb1,LOW) ;
  digitalWrite(ma1,HIGH);
  digitalWrite(mb2,LOW) ;
  digitalWrite(ma2,HIGH);
  digitalWrite(mb3,LOW) ;
  digitalWrite(ma3,HIGH);
  digitalWrite(mb4,LOW) ;
  digitalWrite(ma4,HIGH);
}
void alt() {
  analogWrite(pwm1,0) ;
  analogWrite(pwm2,0) ;
  analogWrite(pwm3,0) ;
  analogWrite(pwm4,0) ;
  digitalWrite(ma1,HIGH);
  digitalWrite(mb1,HIGH);
  digitalWrite(ma2,HIGH);
  digitalWrite(mb2,HIGH);
  digitalWrite(ma3,HIGH);
  digitalWrite(mb3,HIGH);
  digitalWrite(ma4,HIGH);
  digitalWrite(mb4,HIGH);
}


///////////////////////////////encoder/////////////////////////////////

int encoder(){
   aState1 = digitalRead(outputA1); 
   aState2 = digitalRead(outputA2); 
   aState3 = digitalRead(outputA3); 
   aState4 = digitalRead(outputA4);

    if (aState1 != aLastState1){
     if (digitalRead(outputB1) != aState1) {
       counter1 ++;
     } else {
       counter1 --;
     }
   } 
   aLastState1 = aState1;  
   if (aState2 != aLastState2){     
     if (digitalRead(outputB2) != aState2) { 
       counter2 ++;
     } else {
       counter2 --;
     }
   } 
   aLastState2 = aState2;
   if (aState3 != aLastState3){     
    
     if (digitalRead(outputB3) != aState3) { 
       counter3 ++;
     } else {
       counter3 --;
     }
   } 
   aLastState3 = aState3;
   if (aState4 != aLastState4){     
    
     if (digitalRead(outputB4) != aState4) {
       counter4 ++;
     } else {
       counter4 --;
     }
   } 
   aLastState4 = aState4;

   media=abs(counter1)+abs(counter2)+abs(counter3)+abs(counter4);
  media/=4;
  
  pencoder[0]=abs(counter2);
  pencoder[1]=abs(counter3);
  pencoder[2]=abs(counter4);

  

  pencoder[0]=abs(counter1);
  pencoder[1]=abs(counter3);
  pencoder[2]=abs(counter4);

  pencoder[0]=abs(counter1);
  pencoder[1]=abs(counter2);
  pencoder[2]=abs(counter4);

  pencoder[0]=abs(counter1);
  pencoder[1]=abs(counter2);
  pencoder[2]=abs(counter3);

  
  return media;
  }



//maxval(int z[]){
//  for(in
//}























///////////////////////////////sensori/////////////////////////////////


void sensori(){
    for(int i = 0; i < 4; i++){ 
   for(int y = 0; y < 2; y++){
   
       pinMode(pingArray[i][y], OUTPUT);
       digitalWrite(pingArray[i][y], LOW);
       delayMicroseconds(2);
       digitalWrite(pingArray[i][y], HIGH);
       delayMicroseconds(5);
       digitalWrite(pingArray[i][y], LOW);

       pinMode(pingArray[i][y], INPUT);
       duration = pulseIn(pingArray[i][y], HIGH);

       cm = microsecondsToCentimeters(duration);
        medie[i][y]=cm;
   }
   
  }


  if(medie[0][0]<8 && medie[0][1]<8){
    raspy[0][0]='1';
    raspy[0][2]='1';
  }else if(medie[1][0]<8 && medie[1][1]<8){
    raspy[0][0]='1';
    raspy[2][0]='1';  
  }else if(medie[2][0]<8 && medie[2][1]<8){
    raspy[2][0]='1';
    raspy[2][2]='1';
  }else if(medie[3][0]<8 && medie[0][1]<8){
    raspy[0][2]='1';
    raspy[2][2]='1';
  }else{
for (int g=0; g<3; g++){
  for (int f=0; f<3; f++){
      raspy[g][f]='0';
    }
  }

  }

  for (int i=0; i<3; i++){
  for (int j=0; j<3; j++){
 
      Serial.print(raspy[i][j]);
    }
    Serial.print("\n");
  }

  
  }

///////////////////////////////////////////////roba rubata//////////////////////////////////////////////////////////////

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void init_MPU(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  delay(1000);
}

//Funzione per il calcolo degli angoli Pitch e Roll
double FunctionsPitchRoll(double A, double B, double C){
  double DatoA, DatoB, Value;
  DatoA = A;
  DatoB = (B*B) + (C*C);
  DatoB = sqrt(DatoB);
  
  Value = atan2(DatoA, DatoB);
  Value = Value * 180/3.14;
  
  return (int)Value;
}

//Funzione per l'acquisizione degli assi X,Y,Z del MPU6050
void FunctionsMPU(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
}
