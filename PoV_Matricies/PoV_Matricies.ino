//Name: Ethan McAuliffe
//Date: 2016-12-02
//Project: PoV 7 Segment
//Status: Working

//libraries
#include <EEPROM.h>
//constants
#define data 2
#define clock 4
#define latch 3
#define digitSelect 13
//variables
unsigned long time;
uint8_t ones;
uint8_t tens;
byte refreshRate = 144; //refersh rate in HZ

void setup() {
  //registers pins
  pinMode(digitSelect, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
}

void loop() {

  time = millis() / 1000; //sets time equal to time in seconds
  ones = EEPROM.read(time % 10); //finds ones digit
  tens = EEPROM.read(time / 10 % 10); //finds tens digit

  digitalWrite(digitSelect, HIGH); //selects ones digit by sending high signal to the base pins of the transistors
  digitalWrite(latch, LOW); //prepares shift register to recieve data
  shiftOut(data, clock, LSBFIRST, tens); //sends tens digit
  digitalWrite(latch, HIGH);//tells the shift register to display data

  delay(1000 / refreshRate); //delays time respective to the refresh rate specified

  digitalWrite(digitSelect, LOW);//selects tens digit by sending low signal to the base pins of the transistors
  digitalWrite(latch, LOW);//prepares shift register to recieve data
  shiftOut(data, clock, LSBFIRST, ones);//sends ones digit
  digitalWrite(latch, HIGH);//tells the shift register to display data

  delay(1000 / refreshRate); //delays time respective to the refresh rate specified
}
