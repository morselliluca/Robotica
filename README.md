# Robotica

From Teensy POV

Input: 

	//L:100,R:100,0
		
		//100 Speed Values
				
		//0 N of cubes to drop
				
	//STOP
		
		//After Teensy Sends Stop Command it waits for AK from the Raspby
				
	//START
		
		//After Teensy Sends Start Command it waits for AK from the Raspby
				
    
Output:

	//L:0,F:1,R:0,B:
		
		//3 Temp sensor 1=Hot 0=Cold
				
		//B is the color of the Tile 0=white 1=black 2=chechpoint, use last checkpoint as the current reset position
				
	//STOP
		
		//When i want to Stop
				
	//START
		
		//I want to start
				

To find the Modified pololu Library: Robotica/Arduino/libraries/DriverDkv/

Commands:

	//Constructors:

		//DriverDkv(unsigned char INA1, unsigned char INB1, unsigned char PWM1, unsigned char INA2, unsigned char INB2, unsigned char PWM2);
			//Use only basic Functions:
						//void SetM1Speed(int speed); 
							// Set speed for M1.
    						//void SetM2Speed(int speed); 
							// Set speed for M2.
    						//void SetSpeeds(int m1Speed, int m2Speed);
							// Set speed for both M1 and M2.

	

