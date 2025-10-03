#define UTIL_H

#include "defines.h"
#include "setup.h"
#include "power.h"


float getBatteryVoltage(void);
float getCurrentAmps(void);
float getInternalTemperature(void);
void isCurrentSafe(void);
void isBatteryVoltageSafe(void);
