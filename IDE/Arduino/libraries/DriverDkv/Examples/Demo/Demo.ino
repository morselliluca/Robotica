#include <DriverDkv.h>

DriverDkv Driver1 = DriverDkv(3, 4, 2, 9, 10, 8); //ridefinisci i pin con quelli del tuo robot guarda la documentazione 
DriverDkv Driver2 = DriverDkv(22, 21, 23, 14, 13, 15); //commenta questo se ne hai solo 1

void setup()
{  
//commenta tutto se non usate una teensy
analogWriteFrequency(2, 375000);
analogWriteFrequency(8, 375000);
analogWriteFrequency(23, 375000);
analogWriteFrequency(15, 375000);
analogWriteResolution(8);
}

void loop()
{
	Driver1.setSpeeds(254, 254);
	Driver2.setSpeeds(254, 254); //commenta	questo se ne hai solo 1
}