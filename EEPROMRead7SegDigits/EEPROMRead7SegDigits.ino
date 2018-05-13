// Purpose:  Demonstrate the writing of a lookup table of 7-Segment Character Maps EEPROM
// Reference:http://darcy.rsgc.on.ca/ACES/TEI3M/images/7Seq3D.png
// Authors:  2017 TEI3M (class effort)
// Date:     2017 11 30

#include <EEPROM.h>
// Segment order: ABCDEFG.

// One-shot effort so it can all go in the setup function :)
void setup() {
  Serial.begin(9600);
  for(int i=48; i<57; i++){
    Serial.println("The contents of EEPROM at address "+String(i)+" are "+String(EEPROM.read(i),HEX));
  }
}

void loop() {
  // no need...
}
