long previousMillis;
long currentMillis;

int loopTime = 1;

int cicliodom = 10;
int ciclivel = 100;
int cicliencoder;

int counter = 0;

void setup() {
    Serial.begin(9600);

}

void loop() {
    currentMillis = millis();

    if (currentMillis - previousMillis >= loopTime) { // start timed loop for everything else
        previousMillis = currentMillis;
        if (counter % cicliodom == 0) {
            f1();
        }
        if (counter % ciclivel == 0) {
            f2();
        }
        counter++;
    }
}

void f1() {
    Serial.println("f1");
}

void f2() {
    Serial.println("f2");
}
