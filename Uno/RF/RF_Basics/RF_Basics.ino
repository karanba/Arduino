#include <SPI.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int msg[1];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop() {
  if (radio.available()) {

    radio.read(msg, 1);
    Serial.println(msg[0]);
    delay(100);

  }

}
