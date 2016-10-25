#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>

int msg[2];
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int MOTORA_PWM = 5;
int MOTORA_DIR = 4;
int MOTORB_PWM = 3;
int MOTORB_DIR = 2;
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
  pinMode(MOTORA_DIR, OUTPUT);
  pinMode(MOTORB_DIR, OUTPUT);
  pinMode(MOTORA_PWM, OUTPUT);
  pinMode(MOTORB_PWM, OUTPUT);

  digitalWrite(MOTORA_DIR, LOW);
  digitalWrite(MOTORA_PWM, LOW);
  digitalWrite(MOTORB_DIR, LOW);
  digitalWrite(MOTORB_PWM, LOW);
}

void loop(void) {

  while (radio.available()) {
    radio.read(msg, sizeof(msg));
    yL = constrain(map(msg[1], 0, 500, 128, 0), 0, 128);
    yR = constrain(map(msg[1], 550, 1023, 0, 128), 0, 128);
    if (msg[0] > 550) { // ileri
      xF = constrain(map(msg[0], 550, 1023, 0, 255), 0, 255);
      xB = 0;
      digitalWrite(MOTORA_DIR, LOW);
      analogWrite(MOTORA_PWM, constrain(xF + yL, 0, 255));

      digitalWrite(MOTORB_DIR, LOW);
      analogWrite(MOTORB_PWM, constrain(xF + yR, 0, 255));
    } else if (msg[0] < 450) { // geri
      xB = constrain(map(msg[0], 490, 0, 0, 255), 0, 255);
      xF = 0;

      analogWrite(MOTORA_DIR, constrain(xB + yL, 0, 255));
      digitalWrite(MOTORA_PWM, LOW);

      analogWrite(MOTORB_DIR, constrain(xB + yR, 0, 255));
      digitalWrite(MOTORB_PWM, LOW);
    } else {
      if (yL > 50) {
        digitalWrite(MOTORA_DIR, HIGH);
        digitalWrite(MOTORA_PWM, LOW);
        digitalWrite(MOTORB_DIR, LOW);
        digitalWrite(MOTORB_PWM, HIGH);

      } else if (yR > 50) {
        digitalWrite(MOTORA_DIR, LOW);
        digitalWrite(MOTORA_PWM, HIGH);
        digitalWrite(MOTORB_DIR, HIGH);
        digitalWrite(MOTORB_PWM, LOW);
      } else {
        digitalWrite(MOTORA_DIR, LOW);
        digitalWrite(MOTORA_PWM, LOW);
        digitalWrite(MOTORB_DIR, LOW);
        digitalWrite(MOTORB_PWM, LOW);
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


    delay(100);
  }
}
