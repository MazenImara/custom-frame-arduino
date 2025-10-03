#include <Arduino.h>
#include "setup.h"
#include "power.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
  setupSerial();
  setupPins();
}

void loop() {

  
  isPowerBtnPressed();
  
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}