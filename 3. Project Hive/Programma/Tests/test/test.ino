#include <Adafruit_MLX90614.h>
#include <Wire.h>

Adafruit_MLX90614 mlx;

#define IR1 0x5C //indirizzo ir davanti
#define IR3 0x5B //indirizzo ir destra
#define reflection1A A10 //riflesso analogico 1
#define reflection2A A11 //riflesso analogico 2

void setup() {
  Serial.begin(9600);
  mlx.begin(); 

}

void loop() {
  mlx.AddrSet(IR1); 
  Serial.print("IR1: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  mlx.temp1 = mlx.readObjectTempF();
  delay(250);
  mlx.AddrSet(IR3); 
  Serial.print("IR3: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  mlx.temp3 = mlx.readObjectTempF();
  delay(250);
  Serial.println();
  delay(1000);
  Serial.println(analogRead(reflection1A));
  Serial.println("nero");
  Serial.println(analogRead(reflection2A));
}
