#include <LM60.h>

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(lm60_get_temp(A1));
    delay(1000);
}
