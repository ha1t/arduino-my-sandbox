#include "arduino.h"
#include "BM428G.h"

// Arduino IDE 1.6.4

// PD0からPD7
const int anode_pins[] = {3, 7, 10, 12, 13, 4, 9};    // アノードに接続するArduinoのピン
//const int cathode_pins[] = {0, 3, 4, 6};  // カソードに接続するArduinoのピン
const int cathode_pins[] = {8, 6, 5, 2};  // カソードに接続するArduinoのピン
const int number_of_anode_pins = sizeof(anode_pins) / sizeof(anode_pins[0]);
const int number_of_cathode_pins = sizeof(cathode_pins) / sizeof(cathode_pins[0]);
int numbers_to_display = 0; // LEDに表示する数字を保持する変数

// 下の桁から7セグのABC...
const int digits[] = {
  0b01000000, // 0
  0b01111001, // 1
  0b00100100, // 2
  0b00110000, // 3
  0b00011001, // 4
  0b00010010, // 5
  0b00000010, // 6
  0b11011000, // 7
  0b00000000, // 8
  0b00010000, // 9
};

bool COMMON_ON = LOW;
bool COMMON_OFF = HIGH;
bool PIN_ON = HIGH;
bool PIN_OFF = LOW;

void display_numbers() {

  // number_to_displayの値を書き換えないために変数にコピー
  int n = numbers_to_display;

  for (int i = 0; i < number_of_cathode_pins; i++) {

    //PORTD = digits[n % 10];
    for (int j = 0; j < number_of_anode_pins; j++) {
      if (bitRead(digits[n % 10], j)) {
        digitalWrite(anode_pins[j], PIN_OFF);
      } else {
        digitalWrite(anode_pins[j], PIN_ON);
      }
    }

    digitalWrite(cathode_pins[i], COMMON_ON);
    delayMicroseconds(1000);
    digitalWrite(cathode_pins[i], COMMON_OFF);
    n = n / 10; // 10で割る
  }
}

void set_numbers(int n) {
  numbers_to_display = n;
}

// setup()　は，最初に一度だけ実行される
void bm428g_setup() {

  for (int i = 0; i < number_of_anode_pins; i++) {
    pinMode(anode_pins[i], OUTPUT);
    digitalWrite(anode_pins[i], PIN_OFF);
  }

  for (int i = 0; i < number_of_cathode_pins; i++) {
    pinMode(cathode_pins[i], OUTPUT);
    digitalWrite(cathode_pins[i], COMMON_OFF);
  }

}

