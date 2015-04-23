#include <LM60.h>

const int anode_pins[] = {0, 1, 2, 3, 4, 5, 6, 7};    // アノードに接続するArduinoのピン
const int cathode_pins[] = {8, 9, 10, 11};  // カソードに接続するArduinoのピン
const int number_of_anode_pins = sizeof(anode_pins) / sizeof(anode_pins[0]);
const int number_of_cathode_pins = sizeof(cathode_pins) / sizeof(cathode_pins[0]);
int numbers_to_display = 0; // LEDに表示する数字を保持する変数

const int digits[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00100111, // 7
  0b01111111, // 8
  0b01101111, // 9
};

bool COMMON_ON = HIGH;
bool COMMON_OFF = LOW;
bool PIN_ON = LOW;
bool PIN_OFF = HIGH;

// 1桁の数字(n)を表示する
void display_number(int n, boolean use_dot) {
  for (int i = 0; i < number_of_anode_pins; i++) {
    digitalWrite(anode_pins[i], digits[n] & (1 << i) ? PIN_ON : PIN_OFF);
  }
  if (use_dot) {
    digitalWrite(anode_pins[7], PIN_ON);
  }
}

// アノードをすべてPIN_OFFにする
void clear_segments() {
  for (int j = 0; j < number_of_anode_pins; j++) {
    digitalWrite(anode_pins[j], PIN_OFF);
  }
}

void display_numbers() {
  int n = numbers_to_display;  // number_to_displayの値を書き換えないために変数にコピー
  for (int i = 0; i < number_of_cathode_pins; i++) {
    digitalWrite(cathode_pins[i], COMMON_ON);
    if (i == 2) {
        display_number(n % 10, true); // 最後の一桁を表示する
    } else {
        display_number(n % 10, false); // 最後の一桁を表示する
    }
    delayMicroseconds(100);
    clear_segments();
    digitalWrite(cathode_pins[i], COMMON_OFF);
    n = n / 10; // 10で割る
  }
}

void set_numbers(int n) {
  numbers_to_display = n;
}

float get_temp(int pin) {
  
  long mV = 0;
  double sum_v = 0;

  for (int i = 0; i < 20; i++) {
    sum_v = sum_v + analogRead(pin);
    delay(10);
  }

  //mV = map(sum_v / 20, 0, 1023, 0, 5000); //←測定結果を電圧に変換（0-1023の変化を 0V-1.1mV へ）
  mV = map(sum_v / 20, 0, 1023, 0, 1100); //←測定結果を電圧に変換（0-1023の変化を 0V-1.1mV へ）
  Serial.print(mV);
  Serial.print(" ");  
  Serial.print(analogRead(pin));
  Serial.print(" ");
  return (mV - 424) / 6.25;
}

// setup()　は，最初に一度だけ実行される
void setup() {
  //analogReference(INTERNAL); //use internal 1.1v reference

  for (int i = 0; i < number_of_anode_pins; i++) {
    pinMode(anode_pins[i], OUTPUT);
    digitalWrite(anode_pins[i], PIN_OFF);
  }
  for (int i = 0; i < number_of_cathode_pins; i++) {
    pinMode(cathode_pins[i], OUTPUT);
    digitalWrite(cathode_pins[i], COMMON_OFF);
  }
  
  // f = クロック周波数 / ( 2 * 分周比　*　( 1 + 比較レジスタの値))
  // 分周比=32, 比較レジスタの1値=255 -> f = 16000000 / (2 * 32 * 256) = 976 Hz
  OCR1A = 255; // 255クロックごとに割り込みをかける
  TCCR1B = 0b100; // 分周比を32に設定する
  bitWrite(TIMSK1, OCIE1A, 1); // TIMER2を

  Serial.begin(9600);
}

void loop () {

  //for (int i = 0; i < 10000; i++) {
    //set_numbers(i);
    //display_numbers();
    //delay(1000);
  //}
  
  int temp = lm60_get_temp(A0) * 100;
  Serial.println(temp);
  set_numbers(temp);
  delay(1000);
}

ISR(TIMER1_COMPA_vect)
{
  display_numbers();
}

