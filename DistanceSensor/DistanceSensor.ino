//Name: Ethan McAuliffe
//Date: 2016-10-21
//Project: Distance Sensor Challenge
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

uint8_t customs[] [8] = {
  {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f
  },
  {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x1f
  },
  {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x1f, 0x1f
  },
  {
    0x0, 0x0, 0x0, 0x0, 0x1f, 0x1f, 0x1f, 0x1f
  },
  {
    0x0, 0x0, 0x0, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f
  },
  {
    0x0, 0x0, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f
  },
  {
    0x0, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f
  },
  {
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f
  }
};

byte numCustom = sizeof(customs) >> 3;
uint16_t iRead = 0;
byte distance = 0;
byte disp = 0;
//byte lastDisp = 0;

void clearScreen(byte col, byte row, byte numCells) {
  lcd.setCursor(col, row);
  for (byte i = 0; i < numCells; i++) {
    lcd.print(" ");
  }
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  for (byte i = 0; i < numCustom; i++) {
    lcd.createChar(i + 1, customs[i]);
  }
  lcd.setCursor(0, 0);
  lcd.print("Read:");
  lcd.setCursor(9, 0);
  lcd.print("Dist:");
  lcd.setCursor(0, 1);
  lcd.print("Disp:");
}

void loop() {
  // clear inputs
  clearScreen(5, 1, disp);
  //clearScreen(5+lastDisp, 1, disp);
  clearScreen(5, 0, 4);
  clearScreen(14, 0, 2);
  //read and map inputs
  iRead = analogRead(0);
  distance = map(iRead, 0, 634, 32, 3);
  //  lastDisp = disp;
  disp = distance / 4;

  // output
  lcd.setCursor(5, 0);
  lcd.print(iRead);
  lcd.setCursor(14, 0);
  lcd.print(distance);
  lcd.setCursor(5, 1);
  for (byte i = 0; i < disp; i++) {
    lcd.write(i + 1);                //prints distance graph characters
  }
  delay(500);
}
