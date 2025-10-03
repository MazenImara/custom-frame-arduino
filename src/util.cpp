#include "util.h"

float getBatteryVoltage(void)
{
    const float Vmin = 30.0f;
    const float Vmax = 42.0f;
    const int ADCmin = 2308;
    const int ADCmax = 3335;

    int adcValue = adcValues[2]; // قراءة من القناة المطلوبة

    // حماية ضد القيم الخارجة عن النطاق
    if (adcValue < ADCmin) adcValue = ADCmin;
    if (adcValue > ADCmax) adcValue = ADCmax;

    // معادلة التحويل
    float voltage = Vmin + ((adcValue - ADCmin) * (Vmax - Vmin)) / (float)(ADCmax - ADCmin);

    return voltage;
}

float getCurrentAmps(void)
{
    uint16_t raw = adcValues[1];
    float voltage = (3.3f * (float)raw) / 4095.0f;
    float voltage_shunt = voltage / 10.0f; // إذا كان هناك مكبر gain=10
    float current = voltage_shunt / 0.005f;

    // تعويض الانحراف
    current -= CURRENT_OFFSET;

    // حماية من القراءة السالبة
    if (current < 0.0f) current = 0.0f;

    return current;
}

float getInternalTemperature(void)
{
  float Vsense = (adcValues[3] / 4095.0f) * 3.3f;
  float temperature = ((1.43f - Vsense) / 0.0043f) + 25.0f;
  return temperature;
}

void isCurrentSafe(void)
{
  float current = getCurrentAmps();
  if (current > OVERCURRENT_LIMIT)
  {
    serial.print("Current is not safe: ");
    serial.println(current);
        
    powerOff();
  }    
}

void isBatteryVoltageSafe(void)
{
  float batteryVoltage = getBatteryVoltage();
  if (batteryVoltage < MIN_BATTERY_VOL || batteryVoltage > MAX_BATTERY_VOL)
  {
    serial.print("Battery voltage is not safe: ");
    serial.println(batteryVoltage);
    powerOff();
  }  
}


