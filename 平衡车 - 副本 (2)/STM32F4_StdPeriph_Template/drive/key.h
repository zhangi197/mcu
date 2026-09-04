#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"
#include <stdint.h>

/* ==================== 按键硬件定义 ==================== */
/* 按键接 PA15，上拉输入，按下接地（低电平有效） */
#define KEY_GPIO_PORT     GPIOA
#define KEY_GPIO_PIN      GPIO_Pin_15
uint8_t key_get_state(void);
uint8_t key_get_num(void);
void key_tick(void);
void KEY_Init(void);
uint8_t key_check(uint8_t flag);
#define pressed 1
#define unpressed 0
#define key_hold 0x01
#define key_down 0x02
#define key_up 0x04

#endif
