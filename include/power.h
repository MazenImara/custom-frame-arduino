#define POWER_H

#include "defines.h"
#include <Arduino.h>
#include "setup.h"

void isPowerBtnPressed(void);
void powerOn(void);
void powerOff(void);
void powerOnMelody(void);
void powerOffMelody(void);
void readyMelody(void);