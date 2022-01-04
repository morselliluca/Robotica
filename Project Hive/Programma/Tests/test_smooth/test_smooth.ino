double speedsmooth;
double speedprev = 10;
int media = 0;
int counter = 0;
int cicli = 700;

void setup() {
  Serial.begin(9600);

    while (speedsmooth < 255) {
    speedsmooth = (speedprev * 0.05) + speedprev;
    speedprev = speedsmooth;
    counter += 1;
  }
  speedprev = 10;
  speedsmooth = 0;
  while (media < cicli) {
    if (media < (counter-1) && media<cicli/2) {
        speedsmooth = (speedprev * 0.05) + speedprev;
        speedprev = speedsmooth;
        Serial.println(speedsmooth);
    } else if((cicli-media)<counter && media>=cicli/2){
        speedsmooth = speedprev - (speedprev * 0.05);
        speedprev = speedsmooth;
        Serial.println(speedsmooth);
    }
    else{
      Serial.println(255);
    }
    media += 1;
  }
  speedprev = 10;
  speedsmooth = 0;
}

void loop() {

}
