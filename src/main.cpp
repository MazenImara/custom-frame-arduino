#include <Arduino.h>
#include "setup.h"
#include "power.h"

void setup() {
  setupSerial();
  setupPins();
  serial.println("before MX_DMA_Init");
  MX_DMA_Init();
  serial.println("before MX_ADC1_Init");
  MX_ADC1_Init();
}

void loop() {  
  isPowerBtnPressed();

  
    // قراءة القيم أصبحت تلقائية عبر DMA في مصفوفة adcValues
  serial.print("Throttle: ");
  serial.print(adcValues[0]);
  serial.print("  Current: ");
  serial.print(adcValues[1]);
  serial.print("  Battery: ");
  serial.println(adcValues[2]);

  delay(500);
}