#include "arduino.h"
#include "LM60.h"

// LM60
// @url http://brown.ap.teacup.com/nekosan0/681.html
// @url http://ken-nou-kou.blogspot.com/2009/06/lm60biz.html

float lm60_get_temp(int pin) {

  long mV = 0;
  double sum_v = 0;

  for (int i = 0; i < 11; i++) {

    // 一回目は捨てる
    if (i == 0) {
        analogRead(pin);
        continue;
    }

    sum_v = sum_v + analogRead(pin);
    delay(10);
  }

  mV = map(sum_v / 10, 0, 1023, 0, 5150); //←測定結果を電圧に変換（0-1023の変化を 0V-1.1mV へ）
  //mV = map(sum_v / 20, 0, 1023, 0, 1100); //←測定結果を電圧に変換（0-1023の変化を 0V-1.1mV へ）
  return (mV - 424) / 6.25;
}
