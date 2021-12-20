#define ma1 7
#define mb1 6
#define pwm1 2

#define ma2 9
#define mb2 8
#define pwm2 3

#define ma3 10
#define mb3 11
#define pwm3 4

#define ma4 12
#define mb4 13
#define pwm4 5

#define velocita 255
#define direzione 1

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

 int media1;
 int media2;
 bool controllo;




const int pingPin = 32;
const int pingPin1 = 33;
const int pingPin2 = 34;
const int pingPin3 = 35;
const int pingPin4 = 36;
const int pingPin5 = 37;
const int pingPin6 = 38;
const int pingPin7 = 39;
const int buttonPin = 50;
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

 




void setup()
{
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

  
  
  if (Serial.available()>0 && msg){
  //motors(velocita,velocita,velocita,velocita,direzione,direzione,direzione,direzione);
  Serial.println("----- Test movimento motori -----");
  Serial.println("   Utilizzare WASD per muoversi  ");
  Serial.println("  Utilizzare Q ed E per ruotare  ");
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
  }
}

int avanti (int vel) { //direzioni dei motori messe a caso 😂/
  motors(vel,vel,vel,vel,1,1,1,1);
}
int indietro (int vel) {
  motors(vel,vel,vel,vel,2,2,2,2);
}
int destra (int vel) {
  motors(vel,vel,vel,vel,1,2,1,2);
}
int sinistra (int vel) {
  motors(vel,vel,vel,vel,2,1,2,1);
}
int giradestra (int vel) {
  motors(vel,vel,vel,vel,1,1,2,2);
}
int girasinistra (int vel) {
  motors(vel,vel,vel,vel,2,2,1,1);
}
int ferma () {
  motors(0,0,0,0,0,0,0,0);
}

int motors (int v1,int v2,int v3,int v4,int dir1,int dir2,int dir3,int dir4){
  do{

   aState1 = digitalRead(outputA1); 
   aState2 = digitalRead(outputA2); 
   aState3 = digitalRead(outputA3); 
   aState4 = digitalRead(outputA4);
   
    
  if (dir1==0){
    digitalWrite(ma1,HIGH) ;
    digitalWrite(mb1,HIGH) ;
    analogWrite(pwm1,0) ;
    controllo=false;
  }else if (dir1==1){
    digitalWrite(ma1,LOW) ;
    digitalWrite(mb1,HIGH) ;
    analogWrite(pwm1,v1) ;
    controllo=true;
  }else{
    digitalWrite(ma1,HIGH) ;
    digitalWrite(mb1,LOW) ;
    analogWrite(pwm1,v1) ;
    controllo=true;
  }
  
  if (dir2==0){
    digitalWrite(ma2,HIGH) ;
    digitalWrite(mb2,HIGH) ;
    analogWrite(pwm2,0) ;
    controllo=false;
  }else if (dir2==1){
    digitalWrite(ma2,LOW) ;
    digitalWrite(mb2,HIGH) ;
    analogWrite(pwm2,v2) ;
    controllo=true;
  }else{
    digitalWrite(ma2,HIGH) ;
    digitalWrite(mb2,LOW) ;
    analogWrite(pwm2,v2) ;
    controllo=true;
  }

  if (dir3==0){
    digitalWrite(ma3,HIGH) ;
    digitalWrite(mb3,HIGH) ;
    analogWrite(pwm3,0) ;
    controllo=false;
  }else if (dir3==1){
    digitalWrite(ma3,LOW) ;
    digitalWrite(mb3,HIGH) ;
    analogWrite(pwm3,v3) ;
    controllo=true;
  }else{
    digitalWrite(ma3,HIGH) ;
    digitalWrite(mb3,LOW) ;
    analogWrite(pwm3,v3) ;
    controllo=true;
  }

  if (dir4==0){
    digitalWrite(ma4,HIGH) ;
    digitalWrite(mb4,HIGH) ;
    analogWrite(pwm4,0) ;
    controllo=false;
  }else if (dir4==1){
    digitalWrite(ma4,LOW) ;
    digitalWrite(mb4,HIGH) ;
    analogWrite(pwm4,v4) ;
    controllo=true;
  }else{
    digitalWrite(ma4,HIGH) ;
    digitalWrite(mb4,LOW) ;
    analogWrite(pwm4,v4) ;
    controllo=true;
  } 

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

media1=abs(counter1)+abs(counter2)+abs(counter3)+abs(counter4);
media1=media1/4;
Serial.print(media1);
Serial.print("\n");

if(dir1==dir2 && dir3==dir4){
  
  }

  }while(media1<200 && controllo==true);
  if(controllo==true){
    media1=0;
    counter1=0;
    counter2=0;
    counter3=0;
    counter4=0;
  ferma();
  }


}


int sensori(){
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


long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
