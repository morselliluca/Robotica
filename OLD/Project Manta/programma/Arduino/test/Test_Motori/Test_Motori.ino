//For providing logic to L298 IC to choose the direction of the DC motor 

void setup()
{
pinMode(2,OUTPUT) ;   //we have to set PWM pin as output
pinMode(7,OUTPUT) ;  //Logic pins are also set as output
pinMode(6,OUTPUT) ;

pinMode(3,OUTPUT) ;   //we have to set PWM pin as output
pinMode(9,OUTPUT) ;  //Logic pins are also set as output
pinMode(8,OUTPUT) ;

pinMode(4,OUTPUT) ;   //we have to set PWM pin as output
pinMode(11,OUTPUT) ;  //Logic pins are also set as output
pinMode(10,OUTPUT) ;

pinMode(5,OUTPUT) ;   //we have to set PWM pin as output
pinMode(13,OUTPUT) ;  //Logic pins are also set as output
pinMode(12,OUTPUT) ;
}

void loop()
{
//For Clock wise motion , in_1 = High , in_2 = Low

digitalWrite(7,HIGH) ;
digitalWrite(6,LOW) ;
analogWrite(2,150) ;

/*setting pwm of the motor to 255
we can change the speed of rotaion
by chaning pwm input but we are only
using arduino so we are using higest
value to driver the motor  */

//Clockwise for 3 secs
delay(3000) ;     

//For brake
digitalWrite(7,HIGH) ;
digitalWrite(6,HIGH) ;
delay(1000) ;

//For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
digitalWrite(6,HIGH) ;
digitalWrite(7,LOW) ;
delay(3000) ;

//For brake
digitalWrite(7,HIGH) ;
digitalWrite(6,HIGH) ;
delay(1000) ;


//////////////////////////////////

digitalWrite(9,HIGH) ;
digitalWrite(8,LOW) ;
analogWrite(3,150) ;

/*setting pwm of the motor to 255
we can change the speed of rotaion
by chaning pwm input but we are only
using arduino so we are using higest
value to driver the motor  */

//Clockwise for 3 secs
delay(3000) ;     

//For brake
digitalWrite(9,HIGH) ;
digitalWrite(8,HIGH) ;
delay(1000) ;

//For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
digitalWrite(8,HIGH) ;
digitalWrite(9,LOW) ;
delay(3000) ;

//For brake
digitalWrite(9,HIGH) ;
digitalWrite(8,HIGH) ;
delay(1000) ;

//////////////////////////////////

digitalWrite(11,HIGH) ;
digitalWrite(10,LOW) ;
analogWrite(4,150) ;

/*setting pwm of the motor to 255
we can change the speed of rotaion
by chaning pwm input but we are only
using arduino so we are using higest
value to driver the motor  */

//Clockwise for 3 secs
delay(3000) ;     

//For brake
digitalWrite(11,HIGH) ;
digitalWrite(10,HIGH) ;
delay(1000) ;

//For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
digitalWrite(10,HIGH) ;
digitalWrite(11,LOW) ;
delay(3000) ;

//For brake
digitalWrite(11,HIGH) ;
digitalWrite(10,HIGH) ;
delay(1000) ;

//////////////////////////////////

digitalWrite(13,HIGH) ;
digitalWrite(12,LOW) ;
analogWrite(5,150) ;

/*setting pwm of the motor to 255
we can change the speed of rotaion
by chaning pwm input but we are only
using arduino so we are using higest
value to driver the motor  */

//Clockwise for 3 secs
delay(3000) ;     

//For brake
digitalWrite(13,HIGH) ;
digitalWrite(12,HIGH) ;
delay(1000) ;

//For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
digitalWrite(12,HIGH) ;
digitalWrite(13,LOW) ;
delay(3000) ;

//For brake
digitalWrite(13,HIGH) ;
digitalWrite(12,HIGH) ;
delay(1000) ;
 }
