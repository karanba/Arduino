#include <LCD5110_Graph.h>
#include <Servo.h>


const int trig = 2;
const int echo = 3;
const int servoPin = 6;
const int posStart = 60;
const int posStop = 150;

Servo myservo;
LCD5110 myGLCD(8, 9, 10, 11, 12);

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

int sure = 0;
int mesafe = 0;
int pos = 30; // servo position
float rad = 0;
float oposite = 0;
float xdis = 0;
int x = 0;
int y = 0;
void setup() {
  Serial.begin(9600);
  myGLCD.InitLCD();
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object

  pinMode(7, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(7, HIGH);

  myGLCD.invert(true); //Resmin gözükebilmesi için ekranı güncelliyoruz.

}

void loop() {
  //myGLCD.clrScr();


  for (pos = posStart; pos <= posStop; pos += 1) { // goes from 0 degrees to 180 degrees
    don();
  }
  myGLCD.clrScr();

  for (pos = posStop; pos >= posStart; pos -= 1) { // goes from 180 degrees to 0 degrees
    don()    ;                   // waits 15ms for the servo to reach the position
  }
  myGLCD.clrScr();
}

void olcum() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);


  sure = pulseIn(echo, HIGH);
  mesafe = (sure / 2) / 29.1;
  Serial.println("mesafe");
  Serial.println(mesafe);
  int hip = map(mesafe, 0, 400, 0, 35);

  if (pos > 90) {
    rad = (180 - pos) * 0.0174533;
    oposite = sin(rad) * hip;
    xdis = cos(rad) * hip;
    x = (int)(42 - xdis);
    y = (int)(46 - oposite);

  } else {
    rad = pos * 0.0174533;
    oposite = sin(rad) * hip;
    xdis = cos(rad) * hip;
    x = (int)(42 + xdis);
    y = (int)(46 - oposite);
  }
  Serial.println("x");
  Serial.println(x);
  Serial.println("y");
  Serial.println(y);
  myGLCD.drawLine(42, 46, x, y);
  myGLCD.update();
}

void don() {
  // in steps of 1 degree
  myservo.write(pos);
  Serial.println("aci");
  // tell servo to go to position in variable 'pos'
  Serial.println(pos);
  olcum();
  delay(15);


}

