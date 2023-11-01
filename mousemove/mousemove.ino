#include <Mouse.h>

void setup() {
  Mouse.begin();
}

void loop() {
  Mouse.move(2, 2);
  delay(25);
  Mouse.move(0, 0);
  delay(25);
  Mouse.move(-2, -2);
  delay(25);
  Mouse.move(0,0);
  delay(25);
}
