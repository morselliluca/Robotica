char dataString[50] = {0};
int a =0; 

void setup() {
Serial.begin(9600);              //Starting serial communication
}
  
void loop() {
  a++;                          // a value increase every loop
  Serial.println(a);   // send the data
  delay(1000);                  // give the loop some break
}
