#include "power.h"

#define LONG_PRESS_TIME 2000

unsigned long pressStartTime = 0;
bool isPressed = false;


void isPowerBtnPressed(void)
{
  bool btnState = digitalRead(POWER_BTN_PIN);

  if (btnState && !isPressed)
  {
    pressStartTime = millis();
    isPressed = true;
  }
    

  if (!btnState && isPressed) {
    // تم إفلات الزر قبل أن يكتمل الوقت
    isPressed = false;
    powerOn();
  }

  if (btnState && isPressed) {
    // الزر لا يزال مضغوطًا
    if (millis() - pressStartTime >= LONG_PRESS_TIME) {
      Serial.println("تم الضغط لمدة 3 ثواني!");
      isPressed = false;  // منع التكرار
      powerOff();
    }
  }
}

void powerOn(void)
{
  digitalWrite(SELF_HOLD_PIN, HIGH);
  digitalWrite(FRONT_LED_PIN, HIGH);
}

void powerOff(void)
{
  digitalWrite(SELF_HOLD_PIN, LOW);
  digitalWrite(FRONT_LED_PIN, LOW);
  delay(1000);
}