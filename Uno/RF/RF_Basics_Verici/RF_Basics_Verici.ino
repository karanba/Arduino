#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#include  <SPI.h> // SPI Arayüzünü dahil ettik.

int msg[2]; //Göndereceğimiz mesaj değişkenini oluşturduk.
RF24 radio(9, 10); //RF24 kütüphanesi tarafından kullanılacak olan 2 pinin 9. ve 10. pinlerin olduğunu belirttik.
const uint64_t pipe = 0xE8E8F0F0E1LL; // Pipe (kanal) tanımlamasını yaptık.
int Y = 0, X = 0;
const int BUTTON_PIN = 8;
const int X_PIN = 0;
const int Y_PIN = 1;

void setup(void) {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);

  radio.begin();
  radio.openWritingPipe(pipe);
  radio.printDetails();
}

void loop(void) {
  X = analogRead(X_PIN);
  Y = analogRead(Y_PIN);
  Serial.print("X: ");
  Serial.println(msg[0]);

  Serial.print("Y: ");
  Serial.println(msg[1]);
  msg[1] = X;
  msg[0] = Y;
  radio.write(msg, sizeof(msg));
} //Sonra da bu mesaj gönderilsin.
