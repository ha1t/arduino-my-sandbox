#include <OneWire.h>
#include <DallasTemperature.h>
#include <SevSeg.h>
#include <FlexiTimer2.h>

SevSeg sevseg; //Instantiate a seven segment object

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 14

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

float before_temp = 0;

void setup(void)
{
  // start serial port
  //Serial.begin(9600);
  //Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  sensors.setResolution(TEMP_12_BIT);

  byte numDigits = 4;
  byte digitPins[] = {5, 2, 0, 9};
  byte segmentPins[] = {4, 1, 10, 7, 6, 3, 16, 8};
  
  // 9 = 12(X)
  //16 =  5(G)
  //10 =  4(C)
  // 8 =  3(DP)
  // 7 =  2(D)
  // 6 =  1(E)
  // 5 =  6XXXX
  // 4 = 11(A)
  // 3 = 10(F)
  // 2 =  9XXX
  // 1 =  7(B)
  // 0 =  8XX

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setNumber(1000,0);
  sevseg.setBrightness(5);

  FlexiTimer2::set(10, flash);
  FlexiTimer2::start();
}

void loop(void)
{  
  sensors.requestTemperatures(); // Send the command to get temperatures
  float temp = sensors.getTempCByIndex(0);
  float display_temp = 0;

  if (temp <= 0) {
    return;
  }

  if (before_temp != 0) {
    display_temp = (temp + before_temp) / 2;
  } else {
    display_temp = temp;
  }
  
  before_temp = temp;

  //Serial.print("Temperature for the device 1 (index 0) is: ");
  //Serial.println(temp);
  
  sevseg.setNumber(display_temp, 2);
  delay(1000);
}

void flash() {
  sevseg.refreshDisplay();
}
