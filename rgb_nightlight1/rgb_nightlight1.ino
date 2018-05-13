/*
Exploring Arduino - Code Listing 2-6: Toggling LED Nightlight
http://www.exploringarduino.com/content/ch2

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

const int BLED = 9;  //Blue LED on Pin 9
const int GLED = 10; //Green LED on Pin 10
const int RLED = 11; //Red LED on Pin 11
const int BUTTON = 2;  //The Button is connected to pin 2

boolean lastButton = LOW;    //Last Button State
boolean currentButton = LOW; //Current Button State
int ledMode = 0;             //Cycle between LED states

void setup()
{
  pinMode (BLED, OUTPUT);   //Set Blue LED as Output
  pinMode (GLED, OUTPUT);   //Set Green LED as Output
  pinMode (RLED, OUTPUT);   //Set Red LED as Output
  pinMode (BUTTON, INPUT);  //Set button as input (not required)
}

/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);       //Read the button state
  if (last != current)                         //if it's different...
  {
    delay(5);                                  //wait 5ms
    current = digitalRead(BUTTON);             //read it again
  }
  return current;                              //return the current value
}

/*
* LED Mode Selection
* Pass a number for the LED state and set it accordingly
*/
void setMode(int mode)
{
  //RED
  switch (mode) {
    case 0: //off
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);
      break;
    case 1: //red
      analogWrite(RLED, 255);
      analogWrite(GLED, 0);
      analogWrite(BLED, 0);
      break;
    case 2: //green
      analogWrite(RLED, 0);
      analogWrite(GLED, 255);
      analogWrite(BLED, 0);
      break;
    case 3: //blue
      analogWrite(RLED, 0);
      analogWrite(GLED, 0);
      analogWrite(BLED, 255);
      break;
    case 4: //purple
      analogWrite(RLED, 127);
      analogWrite(GLED, 0);
      analogWrite(BLED, 127);
      break;
    case 5: //teal
      analogWrite(RLED, 0);
      analogWrite(GLED, 127);
      analogWrite(BLED, 127);
      break;
    case 6: //orange
      analogWrite(RLED, 127);
      analogWrite(GLED, 127);
      analogWrite(BLED, 0);
      break;
    default://white
      analogWrite(RLED, 85);
      analogWrite(GLED, 85);
      analogWrite(BLED, 85);
  }
}

void loop()
{
  currentButton = debounce(lastButton);           //read debounced state
  if (lastButton == LOW && currentButton == HIGH) //if it was pressed...
  {
    ledMode++;                                    //increment the LED value
  }
  lastButton = currentButton;                     //reset button value
  //if you’ve cycled through the different options, reset the counter to 0
  if (ledMode == 8) ledMode = 0;
  setMode(ledMode);                              //change the LED state
}

