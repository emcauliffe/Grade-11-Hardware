#include <Arduino.h>

//Ethan McAuliffe
//TEI3M
//Saffir-Simpson Scale with RGB LED
#define redPin 11
#define greenPin 10
#define bluePin 9
int green;
int red;
int blue;
int category;
String damage;
int windSpeed;

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  windSpeed = random(74, 201);
  if (windSpeed >= 74) {
    category = 1;
    damage = "Minimal";
    red = 0;
    green = 255;
    blue = 0;
  }
  if (windSpeed >= 96) {
    category = 2;
    damage = "Moderate";
    red = 255;
    green = 255;
    blue = 0;
  }
  if (windSpeed >= 111) {
    category = 3;
    damage = "Extensive";
    red = 255;
    green = 128;
    blue = 0;
  }
  if (windSpeed >= 131) {
    category = 4;
    damage = "Extreme";
    red = 255;
    green = 69;
    blue = 0;

  }
  if (windSpeed >= 155) {
    category = 5;
    damage = "Catastrophic";
    red = 255;
    green = 0;
    blue = 0;
  }

  //output
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  Serial.print("Category: ");
  Serial.print(category);
  Serial.print("\t");
  Serial.print("Wind Speed: ");
  Serial.print(windSpeed);
  Serial.print(" mph");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("Damage at Landfall: ");
  Serial.println(damage);
  delay(1000);
}
