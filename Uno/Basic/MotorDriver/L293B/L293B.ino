void setup() {
  pinMode(A1, INPUT); // Analog Input Potansiyometre
  pinMode(3, OUTPUT); // PWM
  pinMode(4, OUTPUT); // PWM

}

void loop() {
  int konum = analogRead(A1);
  konum = map(konum, 0, 1023, 0, 255);
  delay(50);
  analogWrite(3, konum);
  analogWrite(4, konum);
}
