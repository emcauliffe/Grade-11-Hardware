#define RED 1

uint8_t sunriseDDR[] = {0x16, 0x36, 0x66, 0xC6, 0x66, 0x36, 0x16, 0x00};//sunrise value array
uint8_t sunriseFrames = sizeof(sunriseDDR) / sizeof(uint8_t); //calculates length of sunrise array in bytes

void setup() {
  DDRA = 0xFF;//preemptively enables output for all matrix ports
}
void loop() {
  countDownSquare(100);
  explodeMatrix();
  sunrise(100);
  // sunset(100);
}
void countDownSquare(uint16_t countSpeed) {
  DDRA = 0x66;
  matrix(1);
  PORTA = 0x60; //full green square
  delay(countSpeed);
  uint16_t povTime = millis();
  while (povTime + 200 >= millis()) { //shows POV of 3 dots in centre of matrix
    DDRA = 0x22;
    PORTA = 0x20; //bottom left green dot
    DDRA = 0x64;
    PORTA = 0x60; //two green line left
  }
  DDRA = 0x64;//shows 2 dots on left side of matrix
  delay(countSpeed);
  DDRA = 0x44;// shows upper left dot
  delay(countSpeed);
  DDRA = 0x44; // keeps red dot in sync with other dots to be displayed
  PORTA ^= 0xFF; //invert colours of top left dot
  DDRA ^= 1 << PORTA2;
  DDRB = 1 << PORTB2;//enables specific port on PORTB for buzzer
  for (uint8_t i; i < 8; i++) {
    PORTB ^= 1 << PORTB2;//turns on and off the buzzer
    DDRA ^= 1 << PORTA2; //turn on and off the top left dot
    delay(countSpeed);
  }
  DDRB = 0x00; //turn off port as interference from other ports can cause noise in the buzzer
}
void firework(uint8_t explosionSpeed, uint8_t startingLEDY, uint8_t startingLEDX) {
  matrix(RED);
  for (uint8_t i = 0; i <= 4; i++) {
    uint16_t povDuration = millis() + explosionSpeed;
    while (povDuration >= millis()) { // uses POV and loop to show "explosion" animation where lit LEDs move out in a cross from the original LED
      DDRA = 1 << startingLEDY + i | 1 << startingLEDX;
      DDRA = 1 << startingLEDY - i | 1 << startingLEDX;
      DDRA = 1 << startingLEDY | 1 << startingLEDX + i;
      (startingLEDX - i) < 0 ? DDRA = 0x00 : DDRA = (1 << startingLEDY | 1 << startingLEDX - i); // if conditional is not used, the LED linked to PORTA0 will stay on, as negatives are not accepted
    }
  }
}

void matrix(uint8_t colour) { //sets matrix either all green or all red
  colour == 1 ? PORTA = 0x0F : PORTA = 0xF0;
}
void explodeMatrix() { //runs through a loop of firework animations; one animation per led on the matrix
  for (uint8_t i = 0; i <= 3; i++) {
    for (uint8_t j = 4; j <= 7; j++) {
      firework(40, j, i);
    }
  }
}
void sunrise(uint16_t duration) { // animates sunrise array
  PORTA = 0x0F;
  for (uint8_t i = 0; i < sunriseFrames; i++) {
    uint16_t povTime = millis() + duration;
    while (povTime > millis()) {
      DDRA = sunriseDDR[i];//loops through array and displays appropriate value
      PORTA ^= 0xFF;
    }
  }
}
void sunset(uint16_t duration) {
  PORTA = 0x0F;
  for (uint8_t i = sunriseFrames - 1; i >= 0; i--) {
    uint16_t povTime = millis() + duration;
    while (povTime > millis()) {
      DDRA = sunriseDDR[i];//loops through array and displays appropriate value
      PORTA ^= 0xFF;
    }
  }
  DDRA = 0x00;
}
