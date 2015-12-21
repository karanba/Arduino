#include <LCD5110_Basic.h>

const int trig = 2;
const int echo = 3;
const int lm35 = A0;

LCD5110 myGLCD(8, 9, 10, 11, 12);
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

int sure = 0;
int mesafe = 0;
int tk = 1;
int sicaklik = 0;
int p1 = 0;
void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(7, HIGH);
  myGLCD.InitLCD();
  myGLCD.setContrast(60);
}

void loop() {
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print("reosta:", 0, 0);
  myGLCD.print("derece:", 0, 15);
  myGLCD.print("mesafe:", 0, 20);
    
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  
  
  sure = pulseIn(echo, HIGH);
  mesafe = (sure / 2) / 29.1;
  p1 = analogRead(A1);
  sicaklik = analogRead(lm35);
  sicaklik = sicaklik * 0.48828125;
  
  //myGLCD.setFont(MediumNumbers);
  myGLCD.printNumI(p1, 42, 0);
  myGLCD.printNumI(sicaklik, 42, 15);
  myGLCD.printNumI(mesafe, 42, 20);
  delay(250);
}
