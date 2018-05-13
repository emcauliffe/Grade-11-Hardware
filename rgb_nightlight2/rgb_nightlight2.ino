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

struct RGB {
  byte red;
  byte green;
  byte blue;
};

RGB mode0 = {0, 0, 0};
RGB mode1 = {255, 0, 0};
RGB mode2 = {0, 255, 0};
RGB mode3 = {0, 0, 255};
RGB mode4 = {127, 0, 127};
RGB mode5 = {0, 127, 127};
RGB mode6 = {127, 127, 0};
RGB mode7 = {127, 127, 127};

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
      analogWrite(RLED, mode0.red);
      analogWrite(GLED, mode0.green);
      analogWrite(BLED, mode0.blue);
      break;
    case 1: //red
      analogWrite(RLED, mode1.red);
      analogWrite(GLED, mode1.green);
      analogWrite(BLED, mode1.blue);
      break;
    case 2: //green
      analogWrite(RLED, mode2.red);
      analogWrite(GLED, mode2.green);
      analogWrite(BLED, mode2.blue);
      break;
    case 3: //blue
      analogWrite(RLED, mode3.red);
      analogWrite(GLED, mode3.green);
      analogWrite(BLED, mode3.blue);
      break;
    case 4: //purple
      analogWrite(RLED, mode4.red);
      analogWrite(GLED, mode4.green);
      analogWrite(BLED, mode4.blue);
      break;
    case 5: //teal
      analogWrite(RLED, mode5.red);
      analogWrite(GLED, mode5.green);
      analogWrite(BLED, mode5.blue);
      break;
    case 6: //orange
      analogWrite(RLED, mode6.red);
      analogWrite(GLED, mode6.green);
      analogWrite(BLED, mode6.blue);
      break;
    default://white
      analogWrite(RLED, mode7.red);
      analogWrite(GLED, mode7.green);
      analogWrite(BLED, mode7.blue);
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

