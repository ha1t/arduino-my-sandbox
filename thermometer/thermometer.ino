#include <SevSeg.h>
#include <FlexiTimer2.h>
#include <LM60.h>

SevSeg sevseg; //Instantiate a seven segment object
float g_temp = 0;

void setup() {
  analogReference(INTERNAL);
  //Serial.begin(9600);
  byte numDigits = 4;
  byte digitPins[] = {3, 2, 1, 0};
  byte segmentPins[] = {11, 10 ,9 ,8, 7, 6, 5, 4};
  //sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);

  sevseg.setNumber(1000,0);
  sevseg.setBrightness(5);

  FlexiTimer2::set(10, flash);
  FlexiTimer2::start();
}

void loop() {
  if (g_temp == 0) {
    g_temp = lm60_get_temp(A3, 2560);
  } else {
    g_temp = (g_temp + lm60_get_temp(A3, 2560)) / 2.0;
  }
  //Serial.println(lm60_get_temp(A3, 2560)); // for 32u4
  sevseg.setNumber(g_temp, 2);
  delay(1000);
}

void flash() {
  sevseg.refreshDisplay();
}
