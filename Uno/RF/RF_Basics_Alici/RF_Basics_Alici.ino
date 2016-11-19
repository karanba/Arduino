#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>

int msg[2];
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int M1A = 5;
int M1B = 4;
int M2A = 3;
int M2B = 2;
int xF = 0, xB = 0, yR = 0, yL = 0;
/*
              A1  A2  B1  B2
              --------------
     Forward  L   H   L   H
     BackWard H   L   H   L

*/
void setup(void) {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  pinMode(M1B, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M1A, OUTPUT);
  pinMode(M2A, OUTPUT);

  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);


  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
}

void loop(void) {

  while (radio.available()) {
    radio.read(msg, sizeof(msg));
    yL = constrain(map (msg[1], 0, 500, 128, 0), 0, 128);
    yR = constrain(map(msg[1], 550, 1023, 0, 128), 0, 128);
    if (msg[0] > 550) { // ileri
      xF = constrain(map(msg[0], 550, 1023, 0, 255), 0, 255);
      xB = 0;
      digitalWrite(M1A, HIGH);
      digitalWrite(M1B, LOW);
     // analogWrite(M1A, constrain(xF + yL, 0, 255));

      digitalWrite(M2A, HIGH);
      digitalWrite(M2B, LOW);
     // analogWrite(M2A, constrain(xF + yR, 0, 255));
    } else if (msg[0] < 450) { // geri
      xB = constrain(map(msg[0], 490, 0, 0, 255), 0, 255);
      xF = 0;
      digitalWrite(M1B, HIGH);
      digitalWrite(M1A, LOW);
     // analogWrite(M1A, constrain(xF + yL, 0, 255));

      digitalWrite(M2B, HIGH);
      digitalWrite(M2A, LOW);
     /* analogWrite(M1B, constrain(xB + yL, 0, 255));
      digitalWrite(M1A, LOW);

      analogWrite(M2B, constrain(xB + yR, 0, 255));
      digitalWrite(M2A, LOW);*/
    } else {
      if (yL > 50) {
        digitalWrite(M1B, HIGH);
        digitalWrite(M1A, LOW);

        digitalWrite(M2A, HIGH);
        digitalWrite(M2B, LOW);
      } else if (yR > 50) {
        digitalWrite(M1B, LOW);
        digitalWrite(M1A, HIGH);

        digitalWrite(M2A, LOW);
        digitalWrite(M2B, HIGH);
      } else {
        digitalWrite(M1B, LOW);
        digitalWrite(M1A, LOW);
        digitalWrite(M2B, LOW);
        digitalWrite(M2A, LOW);
      }
    }

    Serial.print("\nlelf\tRight\txF\txB\n");
    Serial.print(yL);

    Serial.print("\t");
    Serial.print(yR);

    Serial.print("\t");
    Serial.print(xF);

    Serial.print("\t");
    Serial.print(xB);
    Serial.print("\t");
    Serial.print(msg[0]);


    delay(20);
  }
}
