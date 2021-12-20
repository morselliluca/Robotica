#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library

IRTherm therm; 

const byte oldAddress = 0x5A;
const byte newAddress = 0x5B;

void setup() 
{
  Serial.begin(9600); // Initialize Serial to log output
  Serial.println("Press a key to begin");
  while (!Serial.available()) ;
  
  therm.begin(oldAddress); // Try using the old address first
  
  byte address;
  if (!therm.readID()) // Try reading the ID registers
  {
    // If the read fails, try re-initializing with the
    // new address. Maybe we've already set it.
    therm.begin(newAddress);
    
    if (therm.readID()) // Read from the ID registers
    { // If the read succeeded, print the ID:
      Serial.println("Communicated with new address.");
      Serial.println("ID: 0x" + 
                     String(therm.getIDH(), HEX) +
                     String(therm.getIDL(), HEX));
    }
    else
    {
      Serial.println("Failed to communicate with either address.");      
    }
  }
  else
  {
    // If the read suceeds, change the address to something
    // new.
    if (!therm.setAddress(newAddress))
    {
      Serial.println("Failed to set new address.");
    }
    else
    {
      Serial.println("Set the address to 0x" + String(newAddress, HEX));
      Serial.println("Cycle power to try it out.");
    }
  }
}

void loop() 
{

}
