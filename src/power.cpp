#include "power.h"

#define LONG_PRESS_TIME 3000

unsigned long pressStartTime = 0;
bool isPressed = false;
bool calbirateMode = false;


void isPowerBtnPressed(void)
{
  bool btnState = digitalRead(POWER_BTN_PIN);
  bool selfHold = digitalRead(SELF_HOLD_PIN);

  if (btnState && !selfHold)
  {    
    powerOn();
  }
  if (btnState && selfHold)
  {    
    while (digitalRead(POWER_BTN_PIN)){}
    if (!calbirateMode)
    {
      powerOff();
    }else{
      //triger calpirate
      tone(BUZZER_PIN, 500, 500);
    }   
  }

  if (btnState && !isPressed)
  {
    pressStartTime = millis();
    isPressed = true;
  }   

  if (!btnState && isPressed) {
    // تم إفلات الزر قبل أن يكتمل الوقت
    isPressed = false;
  }

  if (btnState && isPressed) {
    // الزر لا يزال مضغوطًا
    if (millis() - pressStartTime >= LONG_PRESS_TIME) {
      Serial.println("تم الضغط لمدة 3 ثواني!");
      isPressed = false;  // منع التكرار
      calbirateMode = true;
    }
  }
}

void powerOn(void)
{
  digitalWrite(SELF_HOLD_PIN, HIGH);
  digitalWrite(FRONT_LED_PIN, HIGH);
  serial.println("PowerOn \r\n");
  powerOnMelody();
}

void powerOff(void)
{
  serial.println("PowerOff \r\n");
  powerOffMelody();
  digitalWrite(SELF_HOLD_PIN, LOW);
  digitalWrite(FRONT_LED_PIN, LOW);
}

void powerOnMelody(void)
{
  int freq = 1000;
  for (size_t i = 0; i < 3; i++)
  {
    freq += 250;
    tone(BUZZER_PIN, freq);
    delay(300);
    noTone(BUZZER_PIN);
  }  
}

void powerOffMelody(void)
{
  int freq = 1750;
  for (size_t i = 0; i < 3; i++)
  {
    freq -= 250;
    tone(BUZZER_PIN, freq);
    delay(300);
    noTone(BUZZER_PIN);
  }  
}

void readyMelody(void)
{
  tone(BUZZER_PIN, 2000, 300);
}