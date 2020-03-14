// Arduino Leonardo
// https://www.denshi.club/cookbook/output/led/7seg/7led74-tm1637.html
// https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193

#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// Moisture Sensor
#define AOUT A1

TM1637Display display(CLK, DIO);

int soil_moisture;

void setup(){ 
  Serial.begin(9600); 
}
 
void loop(){
  display.setBrightness(0x0f);

  soil_moisture = analogRead(AOUT);
  display.showNumberDecEx(soil_moisture, 0x0, true);

  Serial.println(soil_moisture);
  delay(500);
}
