// https://gist.github.com/ha1t/ee1fdc6dded24a272f44c788c200bd00
// https://github.com/finitespace/BME280 2.3.0

#include <Arduino.h>
#include <U8g2lib.h>
#include <BME280I2C.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
Connecting the BME280 Sensor:
Sensor              ->  Board
-----------------------------
Vin (Voltage In)    ->  3.3V
Gnd (Ground)        ->  Gnd
SDA (Serial Data)   ->  A4 on Uno/Pro-Mini, 20 on Mega2560/Due, 2 Leonardo/Pro-Micro
SCK (Serial Clock)  ->  A5 on Uno/Pro-Mini, 21 on Mega2560/Due, 3 Leonardo/Pro-Micro
*/
// Indoor Setting
BME280I2C::Settings settings(
  BME280::OSR_X2, // temp
  BME280::OSR_X1, // hum
  BME280::OSR_X16, // pres
  BME280::Mode_Forced,
  BME280::StandbyTime_1000ms,
  BME280::Filter_16,
  BME280::SpiEnable_False,
  0x76 // I2C address. I2C specific.
);
BME280I2C bme(settings);
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
  delay(3000);
  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(0,10,"Loading...");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);

  Wire.begin();

  while(!bme.begin()){
    delay(1000);
  }
}

void loop(void) {

  float temp(NAN), hum(NAN), pres(NAN);
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);
  bme.read(pres, temp, hum, tempUnit, presUnit);

  u8g2.clearBuffer();         // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB14_tr); // choose a suitable font
  u8g2.drawStr(0,20, (String(temp) + "'C").c_str());  // write something to the internal memory
  u8g2.drawStr(0,40, (String(hum) + "%").c_str());
  u8g2.drawStr(0,60, (String(pres / 100) + "hPa").c_str());
  u8g2.sendBuffer();          // transfer internal memory to the display

  delay(1350);  
}
