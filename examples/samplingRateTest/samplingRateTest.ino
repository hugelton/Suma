#include "Suma.h"

const uint16_t WAVE_LENGTH = 1024;

bool checkState = false;

void setup() {
  pinMode(2, OUTPUT);
  
  sumaBegin(48000);  // Suma function
}

void loop() {
  // nothing
}

void audioLoop() {

  checkState = !checkState;
  digitalWrite(2, checkState);
}
