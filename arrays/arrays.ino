//Name: Ethan McAuliffe
//Date:
//Project

byte pins[] = {6, 7, 8};
int state[3];
int len = sizeof(state) / sizeof(int);

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < len; i++) {
    state[i] = random(2) ? LOW : HIGH;
    Serial.println(state[i]);
  }


}
