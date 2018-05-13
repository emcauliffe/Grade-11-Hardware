#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#define RECEIVER 1
#define TRANSMITTER 0
#define SRCLK 4
#define RCLK 3
#define SER 2

double inputChar;
double readChar;
bool radioNumber = RECEIVER;

RF24 radio(7, 8);
byte addresses[][6] = {"1Node", "2Node"};

void setup() {
  // put your setup code here, to run once:
  radio.begin();
  Serial.begin(9600);

  shiftData(0x00);

  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SER, OUTPUT);

  radio.setPALevel(RF24_PA_MAX);

  radio.setChannel(106);

  if (radioNumber == RECEIVER) {
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1, addresses[0]);
  } else {
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
  }
  radio.startListening();
}

void loop() {
  if (radioNumber == TRANSMITTER) {
    radio.stopListening();
    readChar = readSerial();
    if (!radio.write(&readChar, sizeof(double))) {
      //Serial.println("Failed");
    }
    radio.startListening();
    shiftData(readChar);
  }
  if (radioNumber == RECEIVER) {
    double oldChar = inputChar;
    inputChar = readWireless();
    shiftData(inputChar);
    if (inputChar != oldChar) {
      Serial.println(inputChar);
      Serial.println();
    }
  }
}
double readSerial() {
  while (Serial.available()) {
    double charRead = Serial.read();// reads ASCII value of character typed
    return charRead;
  }
}
double readWireless() {
  double received;
  while (radio.available()) {
    radio.read(&received, sizeof(double));
  }
  return received;
}
void shiftData (byte data) {
  digitalWrite(RCLK, LOW);
  shiftOut(SER, SRCLK, LSBFIRST, data);
  digitalWrite(RCLK, HIGH);
}
