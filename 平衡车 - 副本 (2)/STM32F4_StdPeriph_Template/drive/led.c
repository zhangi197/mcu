#include "led.h"

/*"
 * */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 使能 GPIOC 时钟 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = LED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;   /* 输出模式无需上下拉 */
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
    LED_Off();
}

void LED_On(void)
{
    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);        /* 低电平点亮（按需互换） */
}

void LED_Off(void)
{
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
}
