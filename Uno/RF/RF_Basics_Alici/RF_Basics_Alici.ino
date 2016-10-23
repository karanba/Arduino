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
int x = 0, y = 0, v = 0, l = 1, r = 1;

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
  digitalWrite(MOTORB_DIR, LOW);
  digitalWrite(MOTORA_PWM, LOW );
  digitalWrite(MOTORB_PWM, LOW );
}

void loop(void) {

  while (radio.available()) {
    radio.read(msg, sizeof(msg));
    x = map(msg[0], 0, 1023, -255, 255);
    y = map(msg[1], 0, 1023, -100, 100);
 Serial.print("X: ");
    Serial.println(x);

    Serial.print("Y: ");
    Serial.println(y);


    if (x > -10 && x < 10) {
      digitalWrite(MOTORA_DIR, LOW);
      digitalWrite(MOTORB_DIR, LOW);
      digitalWrite(MOTORA_PWM, LOW );
      digitalWrite(MOTORB_PWM, LOW );
      break;
    } else if (x < -10) {
      digitalWrite(MOTORA_DIR, HIGH);
      digitalWrite(MOTORB_DIR, HIGH);
     
    } else {
      digitalWrite(MOTORA_DIR, LOW);
      digitalWrite(MOTORB_DIR, LOW);
    
    }


    if (y > 20) {
      l = 0; r = 1;
     
    } else if (y < -25) {
      l = 1; r = 0;
      
    } else {
      l = 1; r = 1;
    }
   
    Serial.print("l: ");
    Serial.println(l);
    Serial.print("r: ");
    Serial.println(r);
    analogWrite(MOTORB_PWM, x*l);
    analogWrite(MOTORA_PWM, x*r);

  }

  delay(100);
}
