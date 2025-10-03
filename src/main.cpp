#include <Arduino.h>
#include "setup.h"
#include "power.h"
#include "stm32f1xx_hal.h"
#include "util.h"

void setup() {
  setupSerial();
  setupPins();
  MX_DMA_Init();
  MX_ADC1_Init();
  delay(1000);
  serial.println("Setup Complete");
}

void loop() {  
  isPowerBtnPressed();
  isCurrentSafe();
  //isBatteryVoltageSafe();
  
  
}