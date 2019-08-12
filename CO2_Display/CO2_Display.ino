#include <Wire.h>
#include <SPI.h>
#include <SparkFunCCS811.h>
#include <U8g2lib.h>

#define CCS811_ADDR 0x5B

CCS811 mySensor(CCS811_ADDR);

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(
  U8G2_R0,
  /* clock=*/ 13,
  /* data=*/ 11,
  /* cs=*/ 10,
  /* dc=*/ 9,
  /* reset=*/ 8
);

void setup() {
  delay(3000);

  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(0,10,"Loading...");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);

  Wire.begin();
  
  CCS811Core::status returnCode = mySensor.begin();
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    u8g2.clearBuffer(); 
    u8g2.drawStr(0,10,".begin() returned with an error.");
    u8g2.sendBuffer();
    while (1);
  }
}

void loop() {
  if (mySensor.dataAvailable())
  {
    mySensor.readAlgorithmResults();
    u8g2.clearBuffer();         // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB14_tr); // choose a suitable font
    u8g2.drawStr(0,20, (String(mySensor.getCO2()) + "ppm").c_str());  // write something to the internal memory
    u8g2.drawStr(0,40, ("TVOC" + String(mySensor.getTVOC())).c_str());
    u8g2.sendBuffer();          // transfer internal memory to the display
  }
  
  delay(1350);
}
