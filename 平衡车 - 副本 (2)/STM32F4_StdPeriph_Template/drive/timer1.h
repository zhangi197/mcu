#ifndef __TIMER1_H
#define __TIMER1_H

#include "stm32f4xx.h"

void timer1_Init(void);
void timer1_IRQHandler(void);
uint32_t timer1_GetTick(void);
void timer1_UserHandler(void);

#endif
