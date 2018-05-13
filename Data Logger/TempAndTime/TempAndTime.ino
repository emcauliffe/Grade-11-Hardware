#include <Wire.h>
#include <LiquidCrystal.h>

#define rtc 0x68
#define eeprom 0x50
#define tSensor 0x9A

uint8_t seconds = 0;
uint8_t minutes = 0;
uint8_t hours = 0;
String currentTime = "";

int8_t temp = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

}

void loop() {
//  // put your main code here, to run repeatedly:
//  Wire.beginTransmission(rtc);
//  Wire.write(0); //prepare rtc to be read from
//  Wire.endTransmission();
//  //read current second, minute and hour
//  Wire.requestFrom(rtc, 7);
//  seconds = readTime((Wire.read())); //second
//  minutes = readTime(Wire.read() & 0x7f); //minute
//  hours = readTime(Wire.read() & 0x3f); //hour
//  currentTime = (hours,  ":" + minutes, ":" , seconds);

  Wire.beginTransmission(tSensor);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(tSensor, 1);
  while(Wire.available() == 0);
  temp = Wire.read();

  Serial.print("Time: ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println("º");

  delay(1000);

}

uint8_t readTime (uint8_t input) { //makes time human readable (0-60 and 0-24)
  return ((input / 16 * 10) + (input % 16));
}
