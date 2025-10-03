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
  
  serial.println("Setup Complete");
}

void loop() {  
  isPowerBtnPressed();

  
    // قراءة القيم أصبحت تلقائية عبر DMA في مصفوفة adcValues
  serial.print("Throttle: ");
  serial.print(adcValues[0]);
  serial.print("  Current: ");
  serial.print(getCurrentAmps());
  serial.print("  Battery: ");
  serial.print(getBatteryVoltage());
  serial.print("  temperture: ");
  serial.println(getInternalTemperature());
  
}