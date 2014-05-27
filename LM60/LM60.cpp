#include "arduino.h"
#include "LM60.h"

float lm60_get_temp(int pin) {

  long mV = 0;
  double sum_v = 0;

  for (int i = 0; i < 20; i++) {
    sum_v = sum_v + analogRead(pin);
    delay(10);
  }

  //mV = map(sum_v / 20, 0, 1023, 0, 5000); //←測定結果を電圧に変換（0-1023の変化を 0V-1.1mV へ）
  mV = map(sum_v / 10, 0, 1023, 0, 1100); //←測定結果を電圧に変換（0-1023の変化を 0V-1.1mV へ）
  return (mV - 424) / 6.25;
}
