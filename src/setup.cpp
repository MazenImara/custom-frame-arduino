#include "setup.h"
#define ADC_CHANNEL_COUNT 4

HardwareSerial serial(PB7, PB6);
ADC_HandleTypeDef hadc1;
uint16_t adcValues[ADC_CHANNEL_COUNT];
DMA_HandleTypeDef hdma_adc1;

void setupPins(void)
{
  pinMode(POWER_BTN_PIN, INPUT);
  pinMode(SELF_HOLD_PIN, OUTPUT);
  pinMode(FRONT_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void setupSerial(void) 
{
  serial.begin(57600);
}

void MX_ADC1_Init(void)
{
  __HAL_RCC_ADC1_CLK_ENABLE();

  ADC_ChannelConfTypeDef sConfig = {0};
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;  // مهم: لتفعيل المسح المتعدد
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = ADC_CHANNEL_COUNT;
  HAL_ADC_Init(&hadc1);
  
  // تفعيل مستشعر الحرارة الداخلي
  ADC1->CR2 |= ADC_CR2_TSVREFE;

  // قناة 1: Throttle (PA6 = ADC_CHANNEL_6)
  sConfig.Channel = THROTTLE_CH;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  // قناة 2: Current (مثلاً PA2 = ADC_CHANNEL_2)
  sConfig.Channel = CURRENT_CH;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  // قناة 3: Battery Voltage (مثلاً PA5 = ADC_CHANNEL_5)
  sConfig.Channel = BATTERY_V_CH;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  // قناة 4: Temperature ( ADC_CHANNEL_16)
  sConfig.Channel = ADC_CHANNEL_16;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);

  __HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);

  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adcValues, ADC_CHANNEL_COUNT);
}

void MX_DMA_Init(void)
{
  __HAL_RCC_DMA1_CLK_ENABLE();

  hdma_adc1.Instance = DMA1_Channel1;
  hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
  hdma_adc1.Init.Mode = DMA_CIRCULAR;
  hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;

  HAL_DMA_Init(&hdma_adc1);

  __HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);
    // تفعيل مقاطعة الـ DMA في NVIC
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}
