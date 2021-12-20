
// sensori
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



//motori
#define ma1 7
#define mb1 6
#define pwm1 2

#define ma2 9
#define mb2 8
#define pwm2 3

#define ma3 11
#define mb3 10
#define pwm3 4

#define ma4 13
#define mb4 12
#define pwm4 5

int ciao;
int pluto=1;


                      
void setup() {
  Serial.begin(9600);


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

}


void loop() {

  
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

    
  
   //Serial.print(i);
   //Serial.print(y);
  //Serial.print(medie[i][y]);
  //Serial.print('\n');
   //delay(100);
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

  pluto = Serial.read();
 
/*Serial.print("nuovo:\n");

for (int i=0; i<3; i++){
  for (int j=0; j<3; j++){
 
      Serial.print(raspy[i][j]);
    }
    Serial.print("\n");
  }*/
motors(pluto,pluto,pluto,pluto,pluto,pluto,pluto,pluto);
}



//fine programma//

//ultrasuoni

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

//motori

int motors (int v1,int v2,int v3,int v4,int dir1,int dir2,int dir3,int dir4){
  if (dir1==0){
    digitalWrite(ma1,HIGH) ;
    digitalWrite(mb1,HIGH) ;
    analogWrite(pwm1,0) ;
  }else if (dir1==1){
    digitalWrite(ma1,LOW) ;
    digitalWrite(mb1,HIGH) ;
    analogWrite(pwm1,v1) ;
  }else{
    digitalWrite(ma1,HIGH) ;
    digitalWrite(mb1,LOW) ;
    analogWrite(pwm1,v1) ;
  }
  
  if (dir2==0){
    digitalWrite(ma2,HIGH) ;
    digitalWrite(mb2,HIGH) ;
    analogWrite(pwm2,0) ;
  }else if (dir2==1){
    digitalWrite(ma2,LOW) ;
    digitalWrite(mb2,HIGH) ;
    analogWrite(pwm2,v2) ;
  }else{
    digitalWrite(ma2,HIGH) ;
    digitalWrite(mb2,LOW) ;
    analogWrite(pwm2,v2) ;
  }

  if (dir3==0){
    digitalWrite(ma3,HIGH) ;
    digitalWrite(mb3,HIGH) ;
    analogWrite(pwm3,0) ;
  }else if (dir3==1){
    digitalWrite(ma3,LOW) ;
    digitalWrite(mb3,HIGH) ;
    analogWrite(pwm3,v3) ;
  }else{
    digitalWrite(ma3,HIGH) ;
    digitalWrite(mb3,LOW) ;
    analogWrite(pwm3,v3) ;
  }

  if (dir4==0){
    digitalWrite(ma4,HIGH) ;
    digitalWrite(mb4,HIGH) ;
    analogWrite(pwm4,0) ;
  }else if (dir4==1){
    digitalWrite(ma4,LOW) ;
    digitalWrite(mb4,HIGH) ;
    analogWrite(pwm4,v4) ;
  }else{
    digitalWrite(ma4,HIGH) ;
    digitalWrite(mb4,LOW) ;
    analogWrite(pwm4,v4) ;
  } 
}
