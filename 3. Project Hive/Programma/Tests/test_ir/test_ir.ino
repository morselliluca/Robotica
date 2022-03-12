
void setup() 
{
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect.
    }


  pinMode (A10, INPUT); // sensor pin INPUT
  pinMode (A11, INPUT); // sensor pin INPUT
}

void loop()
{
 Serial.println(analogRead(A10));
 Serial.println(analogRead(A11)); 
 delay(500);

}
