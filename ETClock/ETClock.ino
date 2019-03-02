#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <SevSeg.h>
#include <FlexiTimer2.h>

SevSeg sevseg; //Instantiate a seven segment object

// #define USE_SERIAL

void setup() {

#ifdef USE_SERIAL
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");
#endif

  byte numDigits = 4;
  byte digitPins[] = {10, 14, 15, 16};
  byte segmentPins[] = {0, 1, 4, 5, 6, 7, 8, 9};
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setNumber(10,0);
  sevseg.setBrightness(20);
  FlexiTimer2::set(10, flash);
  FlexiTimer2::start();
}

// RealTime -> EorzeaTime
int eorzea_time_convert() {
    
    unsigned long earth_time = now(); // JPの9時間;
    
    uint64_t eorzea_time = ((uint64_t)earth_time * 205714285) / 600000000; // 最後に小数点以下を落としてるせいで精度が落ちる

    //int et_hour = (unsigned long)((float)earth_time / ((float)3600.0 / ((float)1440.0 / (float)70.0))) % 24;
    int et_hour = (unsigned long)((((uint64_t)earth_time * 205714285) / 36000000000) % 24);
    
    // int et_minute = (unsigned long)((float)earth_time / ((float)60.0 / ((float)1440.0 / (float)70.0))) % 60;
    int et_minute = (unsigned long)(eorzea_time % 60);
    
    return et_hour * 100 + et_minute;    
}

int real_time() {
  return hour() * 100 + minute();
}

void loop() {
  tmElements_t tm;
  int eorzea_time;

  if (RTC.read(tm)) {
    setTime(makeTime(tm));
    eorzea_time = eorzea_time_convert();

#ifdef USE_SERIAL
    Serial.print("Ok, Time = ");
    Serial.print(tm.Hour);
    Serial.write(':');
    Serial.print(tm.Minute);
    Serial.write(':');
    Serial.print(tm.Second);
    Serial.print(", Date = ");
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.write('-');
    Serial.print(tm.Month);
    Serial.write('-');
    Serial.print(tm.Day);
    Serial.print(" / ");
    Serial.print(eorzea_time);
    Serial.println();
#endif
    
    sevseg.setNumber(eorzea_time, 2);
    //sevseg.setNumber(real_time(), 2);
    delay(300);
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(10000);
  }
}

void flash() {
  sevseg.refreshDisplay();
}
