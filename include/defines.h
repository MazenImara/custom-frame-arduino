#define DEFINES_H

#define ADC_CHANNEL_COUNT 4  // عدد القنوات

#define MIN_BATTERY_VOL 30.1
#define MAX_BATTERY_VOL 41.9

#define MAX_TEMPERATURE 64.9

#define PI    3.1415926f
#define VBUS  36.0f  // ✅ مهم: فولت البطارية
#define CURRENT_OFFSET 0.95f  // حسب ملاحظتك في وضع السكون
#define OVERCURRENT_LIMIT  15.0f


#define FRONT_LED_PIN PC13

#define BUZZER_PIN PB1

#define POWER_BTN_PIN PA3

#define SELF_HOLD_PIN PA4

#define CURRENT_PIN GPIO_PIN_7
#define CURRENT_PORT GPIOA
#define CURRENT_CH ADC_CHANNEL_7

#define BATTERY_V_PIN GPIO_PIN_5
#define BATTERY_V_PORT GPIOA
#define BATTERY_V_CH ADC_CHANNEL_5

#define THROTTLE_PIN GPIO_PIN_6
#define THROTTLE_PORT GPIOA
#define THROTTLE_CH ADC_CHANNEL_6
