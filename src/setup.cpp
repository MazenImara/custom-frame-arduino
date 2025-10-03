#include "setup.h"

HardwareSerial MySerial(PB7, PB6);

void setupPins(void)
{
  pinMode(POWER_BTN_PIN, INPUT);
  pinMode(SELF_HOLD_PIN, OUTPUT);
  pinMode(FRONT_LED_PIN, OUTPUT);
}

void setupSerial(void) 
{
  MySerial.begin(57600);
  MySerial.println("Enable serial on PB6 and PB7 \r\n");
}