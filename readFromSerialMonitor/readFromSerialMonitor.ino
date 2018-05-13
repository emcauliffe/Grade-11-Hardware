byte charRead;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    charRead = Serial.read();
    Serial.print(char(charRead));
  }
  
}
