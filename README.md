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
			//Use onlu basic Functions:
						//void SetM1Speed(int speed); 
							// Set speed for M1.
    						//void SetM2Speed(int speed); 
							// Set speed for M2.
    						//void SetSpeeds(int m1Speed, int m2Speed);
							// Set speed for both M1 and M2.

		//DriverDkv(unsigned char INA1, unsigned char INB1, unsigned char PWM1, unsigned char INA2, unsigned char INB2, unsigned char PWM2, unsigned char ENA1, unsigned char ENB1, unsigned char ENA2, unsigned char ENB2, unsigned char ROT, unsigned char DIAM, unsigned char LARG, unsigned char BASESPEED);
			//use both normal and advanced Funcions:
								//int Setup(); 
									//necessary to run for advanced functions
    								//int readencoder(int inputDT, int inputCLK, int counter); 
									//Retrun the number of turn from encoder (put in a while loop);
								
								//void SetM1Speed(int speed); 
									// Set speed for M1.
								//void SetM2Speed(int speed); 
									// Set speed for M2.
								//void SetSpeeds(int m1Speed, int m2Speed); 
									// Set speed for both M1 and M2.
								
								//void SmoothSetM1Speed(int speed); 
									// Set speed for M1 by increasing it slowly
								//void SmoothSetM2Speed(int speed); 
									// Set speed for M2 by increasing it slowly
								//void SmoothSetSpeeds(int m1Speed, int m2Speed); 
									// Set speed for both M1 and M2 by increasing it slowly
								
								//void Move(int speed, int mm); 
									//move forward a set amount of mm
								//void Turn(int angolo);
									//turn a certain amount of degrees


