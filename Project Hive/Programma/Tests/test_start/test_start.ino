#define startsw 37 //start switch

bool ctrl = true;

void setup() {
    while (!digitalRead(startsw)) {
        Serial.println("redy to start");
        delay(1000);
    }
    Serial.println("start");

}
void loop() {
    while (digitalRead(startsw)) {
        if (ctrl) {
            Serial.println("start");
            ctrl = false;
            while (input != "start") {
                input = Serial.read();
                Serial.println("start yep");
            }
        } else {
            Serial.println("il mio codice");
        }
    }
    if (!ctrl) {
        Serial.println("stop");
        ctrl = true;
        while (input != "stop") {
            input = Serial.read();
            Serial.println("stop yep");
        }
    } else {
        Serial.println("il mio codice");
    }
}
