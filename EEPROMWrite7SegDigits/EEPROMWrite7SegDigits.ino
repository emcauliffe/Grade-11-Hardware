// Purpose:  Demonstrate the writing of a lookup table of 7-Segment Character Maps EEPROM
// Reference:http://darcy.rsgc.on.ca/ACES/TEI3M/images/7Seq3D.png
// Authors:  2017 TEI3M (class effort)
// Date:     2017 11 30

#include <EEPROM.h>
// Segment order: ABCDEFG.
uint8_t digitMap[] = {
  0b11111100, //zero
  0b01100000, //one
  0b11011010, //two
  0b11110010, //three
  0b01100110, //four
  0b10110110,  //5
  0b10111110,  //6
  0b11100000,  //7
  0b11111110,  //8
  0b11110110,  //9
  };
uint8_t sizeMap = sizeof(digitMap);

// One-shot effort so it can all go in the setup function :)
void setup() {
  Serial.begin(9600);
  for(int i=0; i<sizeMap; i++){
    EEPROM.write(i,digitMap[i]);
  }

  uint8_t number = 28;
  uint8_t units = number%10;
  uint8_t tens = number/10%10;
  uint8_t hundreds = number/100%10;

  Serial.println(EEPROM.read(units),BIN);
  Serial.println(EEPROM.read(tens),BIN);
  Serial.println(EEPROM.read(hundreds),BIN);
  



  
}

void loop() {
  // no need...
}
