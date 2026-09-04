#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"
#define ADC_SAMPLE_ADC              ADC1
#define ADC_SAMPLE_RCC_ADC          RCC_APB2Periph_ADC1
#define ADC_SAMPLE_GPIO_PORT        GPIOA
#define ADC_SAMPLE_GPIO_PIN         GPIO_Pin_0
#define ADC_SAMPLE_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define ADC_SAMPLE_CHANNEL          ADC_Channel_0

#define ADC_SAMPLE_VREF_MV          3300U
#define ADC_SAMPLE_TIMEOUT          100000U

void adc_Init(void);
uint16_t adc_Read(void);
uint16_t adc_ReadMillivolts(void);

#endif
