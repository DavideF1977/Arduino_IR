#include <IRremote.h>
#include <EEPROM.h>

byte Velocita = 0;
byte Stato = 0;

const int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;

const int pwmPin = 0;
const int powerPin = 1;
const int Passi = 28;

void setup() {

  irrecv.enableIRIn();
  irrecv.blink13(true);

  pinMode(powerPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(RECV_PIN, INPUT);

  Velocita = EEPROM.read(1);
  Stato = EEPROM.read(0);

}

void loop() {

  if (irrecv.decode(&results)) {
    irrecv.resume();

    EEPROM.write(0, Stato);     //Memorizzazione ultimo stato
    EEPROM.write(1, Velocita);     //Memorizzazione velocità di funzionamento

    switch (results.value) {
      case 0xFF4AB5: //Keypad button "0"
        Velocita = 0;
        Stato = 0;
    }

    switch (results.value) {
      case 0xFF6897: //Keypad button "1"
        Velocita = 1 * Passi;
    }

    switch (results.value) {
      case 0xFF9867: //Keypad button "2"
        Velocita = 2 * Passi;
    }

    switch (results.value) {
      case 0xFFB04F: //Keypad button "3"
        Velocita = 3 * Passi;
    }

    switch (results.value) {
      case 0xFF30CF: //Keypad button "4"
        Velocita = 4 * Passi;
    }

    switch (results.value) {
      case 0xFF18E7: //Keypad button "5"
        Velocita = 5 * Passi;
    }

    switch (results.value) {
      case 0xFF7A85: //Keypad button "6"
        Velocita = 6 * Passi;
    }

    switch (results.value) {
      case 0xFF10EF: //Keypad button "7"
        Velocita = 7 * Passi;
    }

    switch (results.value) {
      case 0xFF38C7: //Keypad button "8"
        Velocita = 8 * Passi;
    }

    switch (results.value) {
      case 0xFF5AA5: //Keypad button "9"
        Velocita = 9 * Passi;
    }

    switch (results.value) {
      case 0xFF02FD: //Keypad button "OK"
        Stato = 1;
    }

    EEPROM.write(0, Stato);
    EEPROM.write(1, Velocita);

  }

  if (Stato == 1)
  {
    // Accensione
    digitalWrite(powerPin, HIGH);
  }
  else
  {
    // Spegnimento
    digitalWrite(powerPin, LOW);
  }

  // Imposto la velocità della ventola
  analogWrite(pwmPin, Velocita);

}
