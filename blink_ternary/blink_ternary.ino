/*
  Exploring Arduino - Code Listing 2-2: LED with Changing Blink Rate
  http://www.exploringarduino.com/content/ch2

  Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License v3 as published by
  the Free Software Foundation.
*/

#define LED 9         //define LED for Pin 9
int msInitialization = 100;    // define delay parameters
int msCondition = 1000;
int msIncrement = 100;

int ms = msInitialization;

void setup()
{
  pinMode (LED, OUTPUT); //Set the LED pin as an output

}

void loop()
{
  digitalWrite(LED, HIGH);
  delay(ms);
  digitalWrite(LED, LOW);
  delay(ms);
  // prepare for next iteration of the loop
  ms < msCondition ? ms = ms + msIncrement : msInitialization;
//  if (ms < msCondition)
//    ms = ms + msIncrement;
//  else ms = msInitialization;

}

