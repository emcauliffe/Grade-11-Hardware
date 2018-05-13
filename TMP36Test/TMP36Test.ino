// Purpose: To monitor a TMP36 voltage-varying device on an analog input pin
// Link:    http://mail.rsgc.on.ca/~cdarcy/Datasheets/TMP35_36_37.pdf
// Author:  Prepared for TEI3M
// Date:    2016 10 13

uint8_t sensorPin = A0;   // use the first analog input pin, why not?
float vRef = 5.0;         // define the voltage reference (2.7V <-> 5.0V)
uint16_t rawADC;          // the raw 10-bit ADC reading
float tempC;              // the temperature in degrees Celsius

/* one-time prep */
void setup() {
  pinMode(sensorPin, INPUT);  // will be reading an analog voltage
  Serial.begin(9600);         // establish the baud rate for communication
}

void loop() {
  // Obtain (and display) a stream of results...
  rawADC = analogRead(sensorPin);
  delayMicroseconds(13);
  // reading > mV > #degC > offset...
  tempC = map(rawADC, 0, 1024, 0, vRef * 1000) / 10.0 - 50.0;
  delay(500);
  // Publish results
  Serial.print("raw ADC (0-1023): "+String(rawADC));
  Serial.println("\tCelsius: "+String(tempC));
}
