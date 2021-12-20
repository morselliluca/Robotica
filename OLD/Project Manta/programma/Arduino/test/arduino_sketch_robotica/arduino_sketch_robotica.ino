
// this constant won't change. It's the pin number of the sensor's output:
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
       
                      
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  //
//  pinMode(ledPin, OUTPUT);
}


void loop() {
//buttonState = digitalRead(buttonPin);
//while(buttonState == HIGH){
  
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
  Serial.print(medie[i][y]);
  Serial.print('\n');
   delay(100);
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
 
Serial.print("nuovo:\n");

for (int i=0; i<3; i++){
  for (int j=0; j<3; j++){
 
      Serial.print(raspy[i][j]);
    }
    Serial.print("\n");
  }

}
//}
//fine programma//
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
