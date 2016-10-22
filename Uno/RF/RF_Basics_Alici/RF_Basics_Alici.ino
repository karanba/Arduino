#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>

int msg[2];
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int LED1 = 8;

void setup(void) {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  pinMode(LED1, OUTPUT);
}

void loop(void) {
  while (radio.available()) {
    radio.read(msg, 2);

    if (msg[0] > 500) {
      digitalWrite(LED1, HIGH);
      delay(300);
    }
    Serial.print("X: ");
    Serial.println(msg[0]);

    Serial.print("Y: ");
    Serial.println(msg[1]);
  }

  digitalWrite(LED1, LOW);
  delay(100);
}
