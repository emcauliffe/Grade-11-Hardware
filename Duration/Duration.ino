// Purpose:   To demonstrate when an interval has elapsed
// Reference:
// Author:    C. D'Arcy
// Date:      2016
// Status:    Working

int duration = 2000;

long startTime = millis();

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (millis() - startTime > duration)
  {
    Serial.println("2000 ms (2s) have elapsed.");
    startTime = millis();
  }
}

