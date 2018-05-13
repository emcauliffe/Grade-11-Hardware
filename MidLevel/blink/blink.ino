void setup() {
  // put your setup code here, to run once:
  //DDRB = 0x20;
  DDRB = 1 << PB5;

  /*
    DDRB |= 1<<PB5;//set required bit to output
    DDRB &= ~(1<<PB5);//clear the required bit
    DDRB ^= 1<<PB5;//invert the required bit
  */
}

void loop() {
  /*
    PORTB |= 1 << PORTB5; //turn status pin ON
    delay(1000);
    PORTB &= ~(1 << PB5); //turn status pin OFF
    delay(1000);
  */

  PORTB ^= 1 << PORTB5;
  delay(1000);
}
