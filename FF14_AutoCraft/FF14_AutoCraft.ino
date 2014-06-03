
void setup() {
  // make pin 2 an input and turn on the 
  // pullup resistor so it goes high unless
  // connected to ground:
  pinMode(2, INPUT_PULLUP);

  // initialize control over the keyboard:
  Keyboard.begin();
}

void mohansagyou() {
  select_action('3');
  Keyboard.write(KEY_RIGHT_ARROW);
  delay(100);
  Keyboard.write('6');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(3500);
}

void mohansagyou2() {
  select_action('3');
  Keyboard.write(KEY_RIGHT_ARROW);
  delay(100);
  Keyboard.write('8');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(3500);
}

void heisty_touch() {
  select_action('3');
  Keyboard.write(KEY_RIGHT_ARROW);
  delay(100);
  Keyboard.write(KEY_RIGHT_ARROW);
  delay(100);
  Keyboard.write('3');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2900);
}

void tyuukyuukakou() {
  select_action('3');
  Keyboard.write('4');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(3500);
}

void kakou() {
  select_action('3');
  Keyboard.write('2');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(3000);
}

void masters_mend() {
  select_action('3');
  Keyboard.write('3');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2500);
}

void masters_mend2() {
  select_action('3');
  Keyboard.write('5');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2500);
}

void inner_quiet() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('8');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(1500);
}

void relax() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('1');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2000);
}

void great_stride() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('9');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2000);
}

void stedy_hand2() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('5');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(1500);
}

void stedy_hand() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('7');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(1500);
}

void kenyaku() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('4');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2500);
}

void kenyaku2() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('8');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2500);
}

void manipulation() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('3');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2500);
}

void inovation() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('7');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2500);
}

void comfart_zone() {
  select_action('2');
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write('9');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(1800);
}

void bierugo() {
  select_action('3');
  delay(100);
  Keyboard.write('9');
  delay(100);
  Keyboard.print(" <me>");
  delay(200);
  Keyboard.write(KEY_RETURN);
  delay(2200);
}

void select_action(char number) {
  Keyboard.print("/ac ");
  Keyboard.write(KEY_TAB);
  delay(100);
  Keyboard.write(KEY_RIGHT_ARROW);
  delay(100);
  Keyboard.write(KEY_RIGHT_ARROW);
  delay(100);
  Keyboard.write(KEY_RIGHT_ARROW);
  delay(100);
  Keyboard.write(number);
  delay(100);
}

// Lv38 CP304
void create_80() {
  comfart_zone();
  inner_quiet();
  stedy_hand2();
  inovation();
  kakou();
  kakou();
  kakou();
  heisty_touch();
  manipulation();
  mohansagyou2();

  comfart_zone();
  stedy_hand2();
  heisty_touch();
  heisty_touch();
  heisty_touch();
  great_stride();
  bierugo();
  heisty_touch();
  mohansagyou2();
}

// boa rather Lv30 CP279
void create_40() {
  comfart_zone();
  inner_quiet();
  kenyaku2();

  stedy_hand2();
  kakou();
  kakou();
  kakou();
  kakou();
  kakou();
 
  stedy_hand();
  great_stride();
  inovation();
  bierugo();
  mohansagyou2();
}

void loop() {

  while (digitalRead(2) == HIGH) {
    // do nothing until pin 2 goes low
    delay(500);
  }
  
  Keyboard.print("/echo v29");
  delay(100);
  Keyboard.write(KEY_RETURN);
  delay(500);

  for (int i = 0; i < 110; i++) {  

    Keyboard.write(KEY_RETURN);
    delay(100);
    /*
    Keyboard.write(KEY_UP_ARROW);
    delay(100);
    Keyboard.write(KEY_UP_ARROW);
    delay(100);
    Keyboard.write(KEY_RIGHT_ARROW);
    delay(100);
    Keyboard.write(KEY_RIGHT_ARROW);
    delay(100);
  
    Keyboard.write(KEY_RETURN);
    delay(100);
    Keyboard.write(KEY_DOWN_ARROW);
    delay(100);
    Keyboard.write(KEY_DOWN_ARROW);
    delay(100);
    */
    Keyboard.write(KEY_RETURN);
    delay(2000);

    create_40();
    delay(3000);
  }
}






