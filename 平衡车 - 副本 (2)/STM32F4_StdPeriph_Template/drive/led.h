#ifndef __led_H
#define __led_H

#include "stm32f4xx.h"

/* ==================== LED 硬件定义 ==================== */
/* LED 接 PC13，推挽输出 */
#define LED_GPIO_PORT     GPIOC
#define LED_GPIO_PIN      GPIO_Pin_13

/* ==================== 函数声明 ==================== */
void    LED_Init(void);   /* 初始化 LED GPIO */
void    LED_On(void);     /* 点亮 LED */
void    LED_Off(void);    /* 熄灭 LED */

#endif
