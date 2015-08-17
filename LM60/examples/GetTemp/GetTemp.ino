#include <LM60.h>

void setup() {
    analogReference(INTERNAL);
    Serial.begin(9600);
}

void loop() {
    // Serial.println(lm60_get_temp(A1, 1100)); // for 328P
    Serial.println(lm60_get_temp(A1, 2560)); // for 32u4
    delay(1000);
}
