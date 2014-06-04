
const int IR_IN = 8;
const int IR_OUT = 13;

unsigned int data[512] = {};

int before_value = 0;
unsigned long us = micros();

// セットアップ
void setup() {
  Serial.begin(57600);        // シリアル通信速度の設定

  pinMode(IR_IN, INPUT);  // 入出力ピンの設定
  pinMode(IR_OUT, OUTPUT);
}

// dataからリモコン信号を送信
void sendSignal() {

  for (int i = 0; i < 512; i++) {

    unsigned long block_count = data[i] * 10;  // dataは10us単位でON/OFF時間を記録している

    // 0なら終端。
    if (block_count == 0) {
      break;
    }

    unsigned long us = micros();

    do {
      digitalWrite(IR_OUT, 1 - (i & 1)); // iが偶数なら赤外線ON、奇数なら0のOFFのまま
      delayMicroseconds(8);  // キャリア周波数38kHzでON/OFFするよう時間調整
      digitalWrite(IR_OUT, 0);
      delayMicroseconds(7);
    } while (long(us + block_count - micros()) > 0); // 送信時間に達するまでループ
  }
}

// シリアルからの受信をチェック
void checkSerial() {

  if (Serial.available() <= 0) {
    return;
  }

  // スペース受信で入力開始
  if (Serial.read() != ' ') {
    return;
  }

  Serial.print(">");
  unsigned int data_block = 0;
  int i = 0;
  bool is_readed = false;
  while (true) {

    // 次のバイトが来るまで無限ループで待つ
    while (Serial.available() == 0) {}

    int readed_byte = Serial.read();
    if (readed_byte >= '0' && readed_byte <= '9') {    // 0～9を受信なら
      data_block *= 10;
      data_block += readed_byte - '0';
      is_readed = true;
    } else if (is_readed) {    // 数値を受信済み、かつ数値以外が来たら
      data[i++] = data_block; // 受信した数値をdataに記憶
      Serial.print(i);
      Serial.print(":");
      Serial.print(data_block);
      Serial.print("\t");
      if (data_block == 0 || i >= 512) { // 0 受信で赤外線送信開始
        sendSignal();
        Serial.println("OK");
        return;
      }
      data_block = 0;
      is_readed = false;
    }
  }
}

void loop() {
  unsigned int val;
  unsigned int loop_count = 0;

  // Wait for incoming IR signal
  while ((val = digitalRead(IR_IN)) == before_value) {  // パルスが切り替わるまで待機
    if (++loop_count >= 30000) {  // 30000回ループで信号が終了したとみなす
      if (loop_count == 30000) {
        Serial.print("\n");
      } else {
        checkSerial();   // シリアル通信が来ているかチェック
      }
      loop_count = 30000;
    }
  }

  unsigned long us2 = micros();
  Serial.print((us2 - us) / 10, DEC);   // 赤外線のON/OFFが続いた時間を10us単位で送信
  Serial.print(" ");
  before_value = val;
  us = us2;
}
