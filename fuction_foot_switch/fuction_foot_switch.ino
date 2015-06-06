#include <EEPROM.h>
#include <GM34031.h>

// Arduino IDE 1.6.4
const int PEDAL_IN    = 10;
const int PEDAL_OUT   = 16;
const int PEDAL_CHECK = 18;

const int SWITCH_BACK = 14;
const int SWITCH_NEXT = 15;

const int ENABLED_LED = 19;

const int KEYS[] = {
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
};
int key_number;

// setup()　は，最初に一度だけ実行される
void setup() {
  Keyboard.begin();
  
  gm34031_setup();
  
  pinMode(PEDAL_IN, OUTPUT);
  pinMode(PEDAL_OUT, INPUT);
  pinMode(PEDAL_CHECK, INPUT);

  pinMode(SWITCH_BACK, INPUT_PULLUP);
  pinMode(SWITCH_NEXT, INPUT_PULLUP);

  pinMode(ENABLED_LED, OUTPUT); // アクティブ判断用のLED
  
  digitalWrite(PEDAL_IN, HIGH);

  // f = クロック周波数 / ( 2 * 分周比　*　( 1 + 比較レジスタの値))
  // 分周比=32, 比較レジスタの1値=255 -> f = 16000000 / (2 * 32 * 256) = 976 Hz
  OCR1A = 255; // 255クロックごとに割り込みをかける
  TCCR1B = 0b100; // 分周比を32に設定する
  bitWrite(TIMSK1, OCIE1A, 1); // TIMER2を

  key_number = (int)EEPROM.read(0);
  if (key_number < 1 || key_number > 12) {
    key_number = 10;
  }
  set_numbers(key_number);
}

bool is_connected = false;
void loop () {  

  // コネクタが刺さっているかどうか確認
  if (digitalRead(PEDAL_CHECK) == HIGH) {
      digitalWrite(ENABLED_LED, HIGH);   // set the LED on
      set_numbers(key_number);
  } else {
      digitalWrite(ENABLED_LED, LOW);   // set the LED off
      set_numbers(0);
      return;
  }
  
  // スイッチに反応
  if (digitalRead(SWITCH_BACK) == LOW) {
      key_number -= 1;
      if (key_number < 1) {
        key_number = 12;
      }
      EEPROM.write(0, key_number);
      set_numbers(key_number);
      delay(250);
  } else if (digitalRead(SWITCH_NEXT) == LOW) {
      key_number += 1;
      if (key_number > 12) {
        key_number = 1;
      }
      EEPROM.write(0, key_number);
      set_numbers(key_number);
      delay(250);
  }
    
  // ペダルが押されている間
  while (digitalRead(PEDAL_OUT) == LOW) {

    // コネクタが抜けた時は操作無効にする
    if (digitalRead(PEDAL_CHECK) == LOW) {
      return;
    }

    Keyboard.write(KEYS[key_number -1]);
    delay(150);
  }

}

ISR(TIMER1_COMPA_vect) {
  display_numbers();
}

