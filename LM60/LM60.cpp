#include "arduino.h"
#include "LM60.h"

// LM60
// @url http://brown.ap.teacup.com/nekosan0/681.html
// @url http://ken-nou-kou.blogspot.com/2009/06/lm60biz.html
// vrefは5150,2560,1100のいずれか
float lm60_get_temp(int pin, int vref) {

  long mV = 0;
  int sum_v = 0;
  int LOOP_COUNT = 5;

  // 1回目は捨てるから一回多くまわる
  for (int i = 0; i <= LOOP_COUNT; i++) {

    // 1回目は捨てる
    if (i == 0) {
        analogRead(pin);
        continue;
    }

    sum_v = sum_v + analogRead(pin);
    delay(10);
  }

  mV = map(sum_v / LOOP_COUNT, 0, 1023, 0, vref); //←測定結果を電圧に変換（0-1023の変化を 0V-1.1mV へ）
  return (mV - 424) / 6.25;
}
