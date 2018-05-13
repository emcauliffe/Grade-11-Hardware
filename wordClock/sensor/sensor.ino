#include <SPI.h> // for interfacing with the data sensor
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#define SENSORSS 10
#define SENSORSPEED 10000000

RF24 radio(7, 8);
uint8_t addresses[][6] = {"3g8wM", "0Us9x"};

struct SENSORDATA {
  float temp;
  float pressure;
  float humidity;
};

SENSORDATA transmissionData;

void setup() {
  Serial.begin(9600);
  radio.begin();
  SPI.begin();

  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(99);
  radio.openWritingPipe(addresses[0]);

  pinMode(SENSORSS, OUTPUT);
}
void loop() {
  Serial.print(SPI.transfer(0xFA),BIN);//MSB
  Serial.print("/t");
  Serial.print(SPI.transfer(0xFB),BIN);//LSB
  Serial.print("/t");
  Serial.print(SPI.transfer(0xFC),BIN);//XLSB
  Serial.println();
}
float temp() {//returns temp in degrees celcius
    SPI.transfer(0xFA);//TEMP MSB
    SPI.transfer(0xFB);//TEMP LSB
    SPI.transfer(0xFC);//TEMP XLSB
}
float pressure() {//returns pressure in kPa
    SPI.transfer(0xF7);//PRESSURE MSB
    SPI.transfer(0xF8);//PRESSURE LSB
    SPI.transfer(0xF9);//PRESSURE XLSB
}
float humidity() {//returns percent relative humidity
    SPI.transfer(0xFD);//HUMIDITY MSB
    SPI.transfer(0xFE);//HUMIDITY LSB
}
SENSORDATA getMeasurements() {
  SENSORDATA currentData;
  digitalWrite(SENSORSS, LOW);
  SPI.beginTransaction(SPISettings(SENSORSPEED, MSBFIRST, SPI_MODE0));
  // currentData.temp = SPI.transfer(


  SPI.endTransaction();
  digitalWrite(SENSORSS, LOW);
}
void transmit(SENSORDATA data) { //sends data to the main clock
  radio.powerUp();
  delay(6);
  radio.write(&data, sizeof(SENSORDATA));
}
void sensorConfig() {
  digitalWrite(SENSORSS, LOW);
  SPI.beginTransaction(SPISettings(SENSORSPEED, MSBFIRST, SPI_MODE0));
  SPI.transfer(0x72);//initiate write to ctrl_hum 
  SPI.transfer(0x01);//set filtering to 1x
  SPI.transfer(0x74);//initiate write to ctrl_meas
  SPI.transfer(0x29);//set pressure filter to 1x, temp filter to 2x and mode to forced
}
void deepSleep() { //powers down peripherals and ATmega328
  radio.powerDown();
}
