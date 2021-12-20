#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float max_v;
float max_i ;

int k;
int kmax;
int cold;

bool avvio;

byte input = "";



void setup() {
  
Wire.begin();    

  Serial.begin(9600);

  pinMode(2, OUTPUT);

  bool status;
  status = amg.begin(); 

  amg.readPixels(pixels);
    max_i = 0;
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
            if (pixels[k] > max_i) {
    
      max_i = pixels[k];
          
      }
    }

     cold = max_i * 1.7;
}


void loop() {
  
  if (Serial.available()>0){
    input = Serial.read();

  if(input=='1'){

    digitalWrite(2, HIGH);
    
    amg.readPixels(pixels);
    max_i = 0;
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
            if (pixels[k] > max_i) {
    
      max_i = pixels[k];
          
      }
    }
 

      if (max_i > cold){
        Serial.write('c'); 
        Serial.flush();
      }
      else
      {
        Serial.write('0'); 
        Serial.flush();
      }
      input = '0';
      digitalWrite(2, LOW);
    }
  }
}
