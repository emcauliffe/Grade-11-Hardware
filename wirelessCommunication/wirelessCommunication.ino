#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#define RECEIVER 1
#define TRANSMITTER 0

bool radioNumber = RECEIVER;
uint8_t received = 0;
int ledPin = 3;
int pot = A0;
uint8_t potVal = 0;

RF24 radio(7, 8);

byte addresses[][6] = {"1Node", "2Node"};

void setup() {
  // put your setup code here, to run once:
  radio.begin();
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(pot, INPUT);

  radio.setPALevel(RF24_PA_HIGH);

  radio.setChannel(73);

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
  // put your main code here, to run repeatedly:
  if (radioNumber == TRANSMITTER) {
    radio.stopListening();
    potVal = map(analogRead(pot), 0, 1023, 0, 255);
    if (!radio.write(&potVal, sizeof(uint8_t))) {
      Serial.println("Failed");
    }
    radio.startListening();
  } else {
    while (radio.available()) {
      radio.read(&received, sizeof(uint8_t));
    }
    analogWrite(ledPin, received);
    Serial.println(received);
  }
}
