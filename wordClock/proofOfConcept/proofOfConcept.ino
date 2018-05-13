/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <LowPower.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1015.0)

//Adafruit_BME280 bme; // I2C
Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

RF24 radio(7, 8);
unsigned long delayTime;
byte addresses[][6] = {"1Node", "2Node"};

void setup() {
  Serial.begin(9600);
  radio.begin();
  Serial.println(F("BME280 test"));

  pinMode(4, OUTPUT);
  ACSR = B10000000;
  ADCSRA = ADCSRA & B01111111;
  DIDR0 = DIDR0 | B00111111;

  bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF   );

  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(106);
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);

  bool status;

  // default settings
  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 3000;

  delay(100); // let sensor boot up
}


void loop() {
  //  radio.powerUp();
  printValues();
  //  radio.powerDown();
  //  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  digitalWrite(BME_CS, LOW);
  digitalWrite(BME_CS, HIGH);
  delay(delayTime);
  Serial.println();
}


void printValues() {
  Serial.println();


  float readChar = bme.readTemperature();
  radio.write(&readChar, sizeof(float));

  Serial.print("Temperature = ");
//  Serial.print(bme.readTemperature());
  Serial.print(readChar);
  Serial.println(" ºC");
  delay(100);

  Serial.print("Pressure = ");

//  Serial.print(bme.readPressure() / 1000.0F);
  bme.readPressure();
  readChar = bme.readPressure() / 1000.0F;
  radio.write(&readChar, sizeof(float));
  Serial.print(readChar);
  Serial.println(" kPa");


  delay(100);

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
//  Serial.print(bme.readHumidity());

  readChar = bme.readHumidity();
  radio.write(&readChar, sizeof(float));
  Serial.print(readChar);
  Serial.println(" %");

  delay(100);
}
