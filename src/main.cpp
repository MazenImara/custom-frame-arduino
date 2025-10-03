#include <Arduino.h>
#include "setup.h"
#include "power.h"
#include "stm32f1xx_hal.h"

void setup() {
  setupSerial();
  setupPins();
  MX_DMA_Init();
  MX_ADC1_Init();
  
  serial.println("Setup Complete");
}

void loop() {  
  isPowerBtnPressed();

  
    // قراءة القيم أصبحت تلقائية عبر DMA في مصفوفة adcValues
  serial.print("  Battery: ");
  serial.println(adcValues[2]);
  delay(500);
  
}