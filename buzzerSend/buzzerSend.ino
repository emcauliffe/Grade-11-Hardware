#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#define RECEIVER 1
#define TRANSMITTER 0

#define APITCH A0
#define ADURATION 2

#define BUZZER 3

bool radioNumber = TRANSMITTER;
uint8_t received = 0;

RF24 radio(7, 8);
byte addresses[][6] = {"1Node", "2Node"};
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
