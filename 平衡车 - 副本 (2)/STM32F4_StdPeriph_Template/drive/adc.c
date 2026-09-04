#include "adc.h"

void adc_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_AHB1PeriphClockCmd(ADC_SAMPLE_GPIO_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(ADC_SAMPLE_RCC_ADC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = ADC_SAMPLE_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_SAMPLE_GPIO_PORT, &GPIO_InitStructure);

    ADC_CommonStructInit(&ADC_CommonInitStructure);
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
    ADC_CommonInit(&ADC_CommonInitStructure);

    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC_SAMPLE_ADC, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC_SAMPLE_ADC, ADC_SAMPLE_CHANNEL, 1,
                             ADC_SampleTime_84Cycles);
    ADC_Cmd(ADC_SAMPLE_ADC, ENABLE);
}

uint16_t adc_Read(void)
{
    uint32_t timeout = ADC_SAMPLE_TIMEOUT;

    ADC_ClearFlag(ADC_SAMPLE_ADC, ADC_FLAG_EOC);
    ADC_SoftwareStartConv(ADC_SAMPLE_ADC);

    while (ADC_GetFlagStatus(ADC_SAMPLE_ADC, ADC_FLAG_EOC) == RESET)
    {
        if (--timeout == 0)
        {
            return 0;
        }
    }

    return ADC_GetConversionValue(ADC_SAMPLE_ADC);
}

uint16_t adc_ReadMillivolts(void)
{
    uint32_t raw = adc_Read();

    return (uint16_t)((raw * ADC_SAMPLE_VREF_MV) / 4095U);
}
