#include <Wire.h>
#include <Adafruit_AMG88xx.h>

pinMode(44, OUTPUT);

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float max_v;
float max_i ;

int k;
int kmax;

bool avvio;

byte input = "";


void setup() {
  
Wire.begin();    

  Serial.begin(9600);

  bool status;
  status = amg.begin(); 
  
}


void loop() {
  
  if (Serial.available()>0){
    input = Serial.read();

  if(input=='1'){

    digitalWrite(2, HIGH);
    
    amg.readPixels(pixels);
    max_i = 0;
    for (byte k=0; k<65; k++)
 
      if (pixels[k] > max_i) {
    
      max_i = pixels[k];
     
      kmax = k;
     
      }
      if (max_i>25){
        Serial.write('c'); 
        Serial.flush();
      }
      else
      {
        Serial.write('0'); 
        Serial.flush();
      }
      input = '0';
      digitalWrite(44, LOW);
    }
  }
}
