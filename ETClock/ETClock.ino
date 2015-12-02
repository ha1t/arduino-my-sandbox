
// DS1302_Serial_Easy (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// A quick demo of how to use my DS1302-library to 
// quickly send time and date information over a serial link
//
// I assume you know how to connect the DS1302.
// DS1302:  CE pin    -> Arduino Digital 2
//          I/O pin   -> Arduino Digital 3
//          SCLK pin  -> Arduino Digital 4

#include <DS1302.h>
#include <BM428G.h>

// Init the DS1302
DS1302 rtc(2, 3, 4);

// RealTime -> EorzeaTime
int convert(int hours, int minutes, int seconds) {
    int now_time = (hours * 3600) + (minutes * 60) + seconds;

    float et_hours = (float)now_time / 175;
    int et_minutes = (int)((et_hours - floor(et_hours)) * 60);

    while (et_hours > 24) {
        et_hours = et_hours - 24;
    }

    return (((int)et_hours * 100) + et_minutes);
}

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  //rtc.halt(false);
  //rtc.writeProtect(false);  

  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(17, 40, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(14, 8, 2015);   // Set the date to August 6th, 2010

  //bm428g_setup();
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);

  // Setup Serial connection
  Serial.begin(9600);
/*
  // f = クロック周波数 / ( 2 * 分周比　*　( 1 + 比較レジスタの値))
  // 分周比=32, 比較レジスタの1値=255 -> f = 16000000 / (2 * 32 * 256) = 976 Hz
  OCR1A = 255; // 255クロックごとに割り込みをかける
  TCCR1B = 0b100; // 分周比を32に設定する
  bitWrite(TIMSK1, OCIE1A, 1); // TIMER2を
*/
}

void loop()
{
  Time now = rtc.getTime();
  
  set_numbers(convert(now.hour, now.min, now.sec));
  // Send Day-of-Week
  //Serial.print(rtc.getDOWStr());

  Serial.print(now.hour);
  Serial.print(" -- ");

  Serial.print(now.min);
  Serial.print(" -- ");

  Serial.print(now.sec);
  Serial.print(" -- ");
// Send date
  //Serial.print(rtc.getDateStr());
  //Serial.print(" -- ");

  // Send time
  //Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating :)
  delay (1000);
}

ISR(TIMER1_COMPA_vect) {
  display_numbers();
}

