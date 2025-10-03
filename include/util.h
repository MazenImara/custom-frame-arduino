#define UTIL_H

#include "defines.h"
#include "setup.h"
#include "power.h"


float getBatteryVoltage(void);
float getCurrentAmps(void);
void currentProtect(void);
float getInternalTemperature(void);
