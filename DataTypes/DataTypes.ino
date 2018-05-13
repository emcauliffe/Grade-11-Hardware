// Purpose:   To confirm fundamental AVR-gcc data type elements and integer storage sizes
// Reference: https://en.wikipedia.org/wiki/C_data_types
// Author:    C. D'Arcy
// Date:      2017 03 17
// Status:    Working
#include <limits.h>
char buff[50];
char data = 0x80;
void setup() {
  // Open the serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial);
  Serial.println("AVR-libc's (implementation of Standard C) Fixed Point Data Types (memory size in bytes):");
  Serial.println(sizeof(char) + String(" :char"));
  Serial.println(sizeof(signed char) + String(" :signed char"));
  Serial.println(sizeof(unsigned char) + String(" :unsigned char"));
  Serial.println(sizeof(short) + String(" :short"));
  Serial.println(sizeof(short int) + String(" :short int"));
  Serial.println(sizeof(signed short) + String(" :signed short"));
  Serial.println(sizeof(signed short int) + String(" :signed short int"));
  Serial.println(sizeof(unsigned short) + String(" :unsigned short"));
  Serial.println(sizeof(unsigned short int) + String(" :unsigned short int"));
  Serial.println(sizeof(int) + String(" :int"));
  Serial.println(sizeof(signed) + String(" :signed"));
  Serial.println(sizeof(signed int) + String(" :signed int"));
  Serial.println(sizeof(unsigned) + String(" :unsigned"));
  Serial.println(sizeof(unsigned int) + String(" :unsigned int"));
 
  Serial.println(sizeof(long) + String(" :long"));
  Serial.println(sizeof(long int) + String(" :long int"));
  Serial.println(sizeof(signed long) + String(" :signed long"));
  Serial.println(sizeof(signed long int) + String(" :signed long int"));
 
  Serial.println(sizeof(unsigned long) + String(" :unsigned long"));
  Serial.println(sizeof(unsigned long int) + String(" :unsigned long int"));
 
  Serial.println(sizeof(long long) + String(" :long long"));
  Serial.println(sizeof(long long int) + String(" :long long int"));
  Serial.println(sizeof(signed long long) + String(" :signed long long"));
  Serial.println(sizeof(signed long long int) + String(" :signed long long int"));
 
  Serial.println(sizeof(unsigned long long) + String(" :unsigned long long"));
  Serial.println(sizeof(unsigned long long int) + String(" :unsigned long long int"));
  // Floating point...
  Serial.println("Standard C Floating Point Data Types (memory size in bytes):");
  Serial.println(sizeof(float) + String(" :float"));
  Serial.println(sizeof(double) + String(" :double"));
  Serial.println(sizeof(long double) + String(" :long double"));
  // limits...
  sprintf(buff, "Signed char:\t[%hi,%hi]", SCHAR_MIN, SCHAR_MAX);
  Serial.println(buff);
  sprintf(buff, "Unsigned char:\t[0,%hu]",UCHAR_MAX);
  Serial.println(buff);
  sprintf(buff, "Signed short:\t[%d,%d]", SHRT_MIN, SHRT_MAX);
  Serial.println(buff);
  sprintf(buff, "Unsigned short:\t[0,%u]", USHRT_MAX);
  Serial.println(buff);
  sprintf(buff, "Signed int:\t[%i,%i]", INT_MIN, INT_MAX);
  Serial.println(buff);
  sprintf(buff, "Unsigned int:\t[0,%u]", UINT_MAX);
  Serial.println(buff);
  sprintf(buff, "Signed long:\t[%li,%li]", LONG_MIN, LONG_MAX);
  Serial.println(buff);
  sprintf(buff, "Unsigned long:\t[0,%lu]", ULONG_LONG_MAX);
  Serial.println(buff);
}
 
void loop() {}

