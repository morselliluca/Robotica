int Pwm;
float Pwmsmooth;
float Pwmrevius;
float k = 0.9;

void setup() {

  Serial.begin(9600);

}

void loop() {

  Pwm = digitalRead(12);      // read switch
  Pwm = Pwm * 100;        // multiply by 100

  // *** smoothing ***

  Pwm = (Pwm * (1 - k)) + (Pwmrevius * k);
  Pwmrevius = Pwmsmooth;

  // *** end of smoothing ***

  Serial.print(switch1);                  // print to serial terminal/plotter
  Serial.print(" , ");   
  Serial.println(Pwmsmooth);

  delay(10);                      // run loop 100 times/second

}
