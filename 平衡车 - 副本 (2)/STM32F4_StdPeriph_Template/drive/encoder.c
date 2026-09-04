#include "encoder.h"
#include "stm32f4xx.h"

void encoder_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure1;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure1;
    /* 1. 开启 TIM4、GPIOD 的时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    /*2*/
    GPIO_InitStructure1.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure1.GPIO_Mode  = GPIO_Mode_AF;         /* 复用模式 */
    GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_100MHz;    /* 高速 */
    GPIO_InitStructure1.GPIO_OType = GPIO_OType_PP;        /* 推挽 */
    GPIO_InitStructure1.GPIO_PuPd  = GPIO_PuPd_UP;         /* 上拉 */
    GPIO_Init(GPIOD, &GPIO_InitStructure1);
    /* 3. 将 PD12、PD13 映射到 TIM4（AF2） */
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
    /* 4. 时基初始化
     *    TIM4 是 16 位计数器，Period 设为 0xFFFF
     *    Prescaler 为 0：每个编码器脉冲计数 1 次
     */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure1);
    TIM_TimeBaseStructure1.TIM_Period        = 65535;
    TIM_TimeBaseStructure1.TIM_Prescaler     = 0;
    TIM_TimeBaseStructure1.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure1.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStructure1.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure1);    
    /* 5. 编码器接口配置（4 倍频）
     *    TIM_EncoderMode_TI12：同时用 CH1、CH2
     *    TIM_ICPolarity_BothEdge：A/B 相的上升沿、下降沿都计数
     */
    TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling ,TIM_ICPolarity_Rising);
    TIM_SetCounter(TIM4, 0);
    /* 7. 启动 TIM4 */
    TIM_Cmd(TIM4, ENABLE);

}


/* ===================== TIM4 编码器读取 ===================== */
int32_t encoder_GetValue(void)
{
    return (int32_t)(int16_t)TIM_GetCounter(TIM4);
}

void encoder_ResetValue(void)
{
    TIM_SetCounter(TIM4, 0);
}

int32_t encoder_GetSpeed(void)
{
    static int16_t last_value;
    int16_t current_value = (int16_t)TIM_GetCounter(TIM4);
    int16_t speed = (int16_t)(current_value - last_value);

    last_value = current_value;
    return (int32_t)speed;
}
