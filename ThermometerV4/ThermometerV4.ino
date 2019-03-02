// https://gist.github.com/ha1t/ee1fdc6dded24a272f44c788c200bd00

#include <Arduino.h>
#include <U8g2lib.h>
#include <BME280I2C.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// BME280I2C bme;
BME280I2C bme(2, 1, 5, 3, 0, 4); // Indoor Navigation
void printBME280Data(Stream * client);
void printBME280CalculatedData(Stream* client);

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(
  U8G2_R0,
  /* clock=*/ 13,
  /* data=*/ 11,
  /* cs=*/ 10,
  /* dc=*/ 9,
  /* reset=*/ 8
);

void setup(void) {
  u8g2.begin();
  while(!bme.begin()){
    delay(1000);
  }
}

void loop(void) {

  bool metric = true;
  float temp(NAN), hum(NAN), pres(NAN);
  uint8_t pressureUnit(1);
  bme.read(pres, temp, hum, metric, pressureUnit);

  u8g2.clearBuffer();         // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB14_tr); // choose a suitable font
  u8g2.drawStr(0,20, (String(temp) + "'C").c_str());  // write something to the internal memory
  u8g2.drawStr(0,40, (String(hum) + "%").c_str());
  u8g2.drawStr(0,60, (String(pres) + "hPa").c_str());
  u8g2.sendBuffer();          // transfer internal memory to the display

  delay(1350);  
}

