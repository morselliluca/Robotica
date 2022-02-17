void setup() {
  Serial.begin(9600);
  }

String input;
String speedL;
String speedR;
String cubi;

void loop() {

    input = Serial.readStringUntil('x');
        speedL = String(input[2]) + String(input[3]) + String(input[4]);
        speedR = String(input[8]) + String(input[9]) + String(input[10]);
        cubi = String(input[12]);
        Serial.println(speedL);
        Serial.println(speedR);
        Serial.println(cubi);
        
        Serial.println(Serial.dtr());
}
