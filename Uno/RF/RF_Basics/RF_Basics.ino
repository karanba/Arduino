#include <SPI.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(7, 8);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    unsigned int msg=8;
    radio.read(&msg, sizeof(unsigned int));
    Serial.println(msg);
  } else {
    Serial.println("radio not avalible");
  }

}
