const int anode_pins[] = {12, 8, 5, 3, 2, 11, 6, 4};    // アノードに接続するArduinoのピン
const int cathode_pins[] = {7, 9, 10, 13};  // カソードに接続するArduinoのピン
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

// start
// LM60
// @url http://brown.ap.teacup.com/nekosan0/681.html
// @url http://ken-nou-kou.blogspot.com/2009/06/lm60biz.html

double max = - 424.0 / 6.25; // temperature at ADC=0
int analogpin0 = 0;

unsigned int summary = 0; // summary of input data
double t_value; //temperature value
// end

// 1桁の数字(n)を表示する
void display_number (int n, boolean use_dot) {
  for (int i = 0; i < number_of_anode_pins; i++) {
    digitalWrite(anode_pins[i], digits[n] & (1 << i) ? LOW : HIGH);
  }
  if (use_dot) {
    digitalWrite(4, LOW);
  }
}

// アノードをすべてLOWにする
void clear_segments() {
  for (int j = 0; j < number_of_anode_pins; j++) {
    digitalWrite(anode_pins[j], HIGH);
  }
}

void display_numbers () {
  int n = numbers_to_display;  // number_to_displayの値を書き換えないために変数にコピー
  for (int i = 0; i < number_of_cathode_pins; i++) {
    digitalWrite(cathode_pins[i], HIGH);
    if (i == 2) {
        display_number(n % 10, true); // 最後の一桁を表示する
    } else {
        display_number(n % 10, false); // 最後の一桁を表示する
    }
    delayMicroseconds(100);
    clear_segments();
    digitalWrite(cathode_pins[i], LOW);
    n = n / 10; // 10で割る
  }
}

void set_numbers(int n) {
  numbers_to_display = n;
}

int get_temp() {
  delay(1800); //1.8s//
  summary = 0;
  for(int i = 0; i < 10; i++) {
    summary = summary + analogRead(analogpin0);
    delay(100);
  }

  t_value = ((double)(summary)/10.0 /1024.0 * 1100.0 / 6.25) + max;
  
  return (int)(t_value * 100);
}

// setup()　は，最初に一度だけ実行される
void setup() {
  analogReference(INTERNAL); //use internal 1.1v reference

  for (int i = 0; i < number_of_anode_pins; i++) {
    pinMode(anode_pins[i], OUTPUT);  // anode_pinsを出力モードに設定する
  }
  for (int i = 0; i < number_of_cathode_pins; i++) {
    pinMode(cathode_pins[i], OUTPUT);  // cathode_pinを出力モードに設定する
    digitalWrite(cathode_pins[i], LOW);
  }
  
  // f = クロック周波数 / ( 2 * 分周比　*　( 1 + 比較レジスタの値))
  // 分周比=32, 比較レジスタの1値=255 -> f = 16000000 / (2 * 32 * 256) = 976 Hz
  OCR2A = 255; // 255クロックごとに割り込みをかける
  TCCR2B = 0b100; // 分周比を32に設定する
  bitWrite(TIMSK2, OCIE2A, 1); // TIMER2を
}

void loop () {
  /*
  for (int i = 0; i < 10000; i++) {
    set_numbers(i);
    delay(1000);
  }
  */
  int temp = get_temp();
  set_numbers(temp);
}

ISR(TIMER2_COMPA_vect)
{
  display_numbers();
}

