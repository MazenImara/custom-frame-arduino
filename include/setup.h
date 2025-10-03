#define SETUP_H

#include "stm32f1xx_hal.h"
#include <Arduino.h>
#include "defines.h"

extern HardwareSerial serial;
extern ADC_HandleTypeDef hadc1;
extern uint16_t adcValues[ADC_CHANNEL_COUNT];

void setupPins(void);
void setupSerial(void);
void MX_ADC1_Init(void);
void MX_DMA_Init(void);