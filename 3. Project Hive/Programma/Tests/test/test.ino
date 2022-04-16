#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx;

#define IR1 0x5C //indirizzo ir davanti
#define IR2 0x5A //indirizzo ir sinistra
#define IR3 0x5B //indirizzo ir destra
#define reflection1A A10 //riflesso analogico 1
#define reflection2A A11 //riflesso analogico 2

void setup() {
  Serial.begin(9600);

}

void loop() {
  mlx.AddrSet(IR1);
  Serial.println("calore");
  Serial.println(String(mlx.readAmbientTempC() - mlx.readObjectTempC()));
    mlx.AddrSet(IR2);
    Serial.println("calore");
  Serial.println(String(mlx.readAmbientTempC() - mlx.readObjectTempC()));
    mlx.AddrSet(IR3);
    Serial.println("calore");
  Serial.println(String(mlx.readAmbientTempC() - mlx.readObjectTempC()));
  Serial.println("nero");
  Serial.println(analogRead(reflection1A));
  Serial.println("nero");
  Serial.println(analogRead(reflection2A));
}
