#include <AFMotor.h>

AF_DCMotor motor(1, MOTOR12_1KHZ);
const int M1A = 12;
const int M1B = 13;

void setup() {
  motor.setSpeed(150);

  // put your setup code here, to run once:
  /*pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);

  digitalWrite(M1A, LOW);
  digitalWrite(M1B, HIGH);*/
}

void loop() {
  // put your main code here, to run repeatedly:
  motor.run(FORWARD); 

}
