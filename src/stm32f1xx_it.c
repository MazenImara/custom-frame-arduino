#include "stm32f1xx_it.h"


extern DMA_HandleTypeDef hdma_adc1;


void DMA1_Channel1_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_adc1);
}