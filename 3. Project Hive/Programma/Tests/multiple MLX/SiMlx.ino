/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define IR1 0x5C
#define IR2 0x5A
#define IR3 0x5B
Adafruit_MLX90614 mlx;

void setup() {
  Serial.begin(9600);
  

  Serial.println("Adafruit MLX90614 test");  

  mlx.begin(); 
  
  
}

void loop() {
  
  mlx.AddrSet(IR1); 
  Serial.print("IR1: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  mlx.temp1 = mlx.readObjectTempF();
  delay(250);
  mlx.AddrSet(IR2); 
  Serial.print("IR2: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  mlx.temp2 = mlx.readObjectTempF();
  delay(250);
  mlx.AddrSet(IR3); 
  Serial.print("IR3: ");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  mlx.temp3 = mlx.readObjectTempF();
  delay(250);
  Serial.print("\n***********Average Temp:"); Serial.print(mlx.avgF=(mlx.temp1+mlx.temp2+mlx.temp3)/3); 
  Serial.print("***********\n");
  Serial.println();
  delay(1000);
}
